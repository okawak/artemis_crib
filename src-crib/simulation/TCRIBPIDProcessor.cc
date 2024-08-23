/**
 * @file    TCRIBPIDProcessor.cc
 * @brief   Beam PID at F2 and F3 of CRIB
 * @author  Kodai Okawa <okawa@cns.s.u-tokyo.ac.jp>
 * @date    2023-12-19 15:30:55
 * @note    last modified: 2024-08-23 21:07:34
 * @details
 */

#include "TCRIBPIDProcessor.h"

#include <Mass.h> // TSrim library
#include <TCanvas.h>
#include <TGraph.h>
#include <TH1.h>
#include <TMultiGraph.h>
#include <TROOT.h>
#include <TStyle.h>
#include <TSystem.h>
#include <TText.h>
#include <yaml-cpp/yaml.h>

using art::crib::TCRIBPIDProcessor;

ClassImp(TCRIBPIDProcessor);

// definition of constant strings for the key of each node
namespace {
const char *kNodeKeyIons = "input_ions";
const char *kNodeKeyF1Param = "f1_parameters";
const char *kNodeKeyF2Param = "f2_parameters";
const char *kNodeKeyF3Param = "f3_parameters";
const char *kNodeKeyBrho = "brho";
const char *kNodeKeyDegMat = "degrader_material";
const char *kNodeKeyDegThickness = "degrader_thickness";
const char *kNodeKeyRfPeriod = "rf_period";
const char *kNodeKeyPPACThickness = "PPAC_thickness";
const char *kNodeKeySSDThickness = "SSD_thickness";
const char *kNodeKeyAThickness = "a_thickness";
const char *kNodeKeyBThickness = "b_thickness";
const char *kNodeKeyDistance = "distance";
const char *kNodeKeyTrigger = "trigger";
const char *kNodeKeyRfOffset = "rf_offset";
const char *kNodeKeyRfRange = "rf_range";
const char *kNodeKeyERange = "energy_range";
const char *kNodeKeyTofOffset = "tof_offset";
const char *kNodeKeyTofRange = "tof_range";
} // namespace

TCRIBPIDProcessor::TCRIBPIDProcessor() {
    RegisterProcessorParameter("FileName", "parameter file of PID", fFileName, TString(""));
    RegisterProcessorParameter("Batch", "Batch mode", fIsBatch, kFALSE);
}

TCRIBPIDProcessor::~TCRIBPIDProcessor() {
    delete srim;
    srim = nullptr;
}

void TCRIBPIDProcessor::Init(TEventCollection *) {
    Info("Init", "PID parameters are loaded from %s", fFileName.Data());
    LoadPIDyaml();
    SetSRIMObject();

    gStyle->SetMarkerSize(1.5);
    gStyle->SetTextSize(0.03);
    if (fIsBatch) {
        gROOT->SetBatch(kTRUE);
    }

    std::vector<TGraph *> graphs_f2_pid;
    std::vector<TGraph *> graphs_f3_pid;

    for (Size_t i = 0, n = ion_names.size(); i < n; i++) {
        Int_t z = amdc::GetZ(ion_names[i]);
        Int_t a = ion_massnum[i];
        Double_t mass = ion_masses[i];

        // calculate the kinetic energy from Brho
        Double_t Brhoqc = f1_brho * ion_charges[i] * kUnitCharge * kLightSpeed * kJ2MeV;
        Double_t Ekin = mass * (TMath::Sqrt(1.0 + TMath::Power(Brhoqc / mass, 2.0)) - 1.0);
        Double_t E_after_degrader = srim->EnergyNew(z, a, Ekin, degrader_mat, degrader_thick);

        // calculate energy loss
        Double_t E_after_f2ppac = srim->EnergyNew(z, a, E_after_degrader, "mylar", f2_ppac_thickness);
        Double_t E_in_f2ssd = E_after_f2ppac - srim->EnergyNew(z, a, E_after_f2ppac, "si", f2_ssd_thickness);

        Double_t E_after_ppaca = srim->EnergyNew(z, a, E_after_degrader, "mylar", a_thickness);
        // Double_t E_after_ppacb = srim->EnergyNew(z, a, E_after_ppaca, "mylar", b_thickness);

        // calculate tof (ns)
        Double_t tof_f0f2 = 1.0e+9 * kLengthF0F2 / E2m_s(Ekin, mass);
        Double_t tof_f0f3 = 1.0e+9 * kLengthF0F3 / E2m_s(Ekin, mass);
        Double_t tof_ppacs = 1.0e+9 * distance * 1.0e-3 / E2m_s(E_after_ppaca, mass);

        // calculate data points
        // for F2
        TGraph *gr_f2 = new TGraph();
        Int_t itr_f2 = 0;
        Double_t rf_f2 = -tof_f0f2 + f2_rf_offset; // !! this is rf so the sign is minus!
        if (rf_f2 < 0.0) {
            while (rf_f2 < 0.0) {
                rf_f2 += rf_period;
            }
        } else {
            while (rf_f2 > 0.0) {
                rf_f2 -= rf_period;
            }
            rf_f2 += rf_period;
        }
        while (rf_f2 < f2_rf_range[1] - f2_rf_range[0]) {
            gr_f2->SetPoint(itr_f2, rf_f2 - f2_rf_range[0], E_in_f2ssd);
            itr_f2++;
            rf_f2 += rf_period;
        }
        // set TGraph style
        gr_f2->SetName(Form("%s_%d+", ion_names[i].c_str(), ion_charges[i]));
        gr_f2->SetTitle(Form("%s_%d+", ion_names[i].c_str(), ion_charges[i]));
        gr_f2->SetMarkerStyle(20 + i);
        if (ion_colors[i] == 0) {
            gr_f2->SetMarkerColor(kRed);
        } else if (ion_colors[i] == 1) {
            gr_f2->SetMarkerColor(kBlue);
        } else {
            gr_f2->SetMarkerColor(kBlack);
        }
        graphs_f2_pid.emplace_back(gr_f2);

        // for F3
        TGraph *gr_f3 = new TGraph();
        Int_t itr_f3 = 0;
        Double_t rf_f3 = -tof_f0f3 + f3_rf_offset; // !! this is rf so the sign is minus!
        if (trigger == 1) {
            rf_f3 -= tof_ppacs;
        }
        if (rf_f3 < 0.0) {
            while (rf_f3 < 0.0) {
                rf_f3 += rf_period;
            }
        } else {
            while (rf_f3 > 0.0) {
                rf_f3 -= rf_period;
            }
            rf_f3 += rf_period;
        }
        while (rf_f3 < f3_rf_range[1] - f3_rf_range[0]) {
            gr_f3->SetPoint(itr_f3, rf_f3 - f3_rf_range[0], tof_ppacs + tof_offset);
            itr_f3++;
            rf_f3 += rf_period;
        }
        // set TGraph style
        gr_f3->SetName(Form("%s_%d+", ion_names[i].c_str(), ion_charges[i]));
        gr_f3->SetTitle(Form("%s_%d+", ion_names[i].c_str(), ion_charges[i]));
        gr_f3->SetMarkerStyle(20 + i);
        if (ion_colors[i] == 0) {
            gr_f3->SetMarkerColor(kRed);
        } else if (ion_colors[i] == 1) {
            gr_f3->SetMarkerColor(kBlue);
        } else {
            gr_f3->SetMarkerColor(kBlack);
        }
        graphs_f3_pid.emplace_back(gr_f3);
    }

    // Save Object
    TCanvas *c_f2 = new TCanvas("F2_canvas", "F2_canvas", 800, 800);
    c_f2->cd();
    TMultiGraph *mg_f2 = new TMultiGraph();
    mg_f2->SetTitle("F2_PID; F2 RF [ns]; F2 SSD [MeV]");
    mg_f2->GetHistogram()->GetXaxis()->SetLimits(f2_rf_range[0], f2_rf_range[1]);
    mg_f2->GetHistogram()->GetYaxis()->SetRangeUser(energy_range[0], energy_range[1]);
    mg_f2->GetHistogram()->GetYaxis()->SetTitleOffset(1.3);
    mg_f2->GetHistogram()->GetXaxis()->SetTitleOffset(1.3);

    std::vector<TText *> txts_f2;
    for (Size_t i = 0, n = graphs_f2_pid.size(); i < n; i++) {
        mg_f2->Add(graphs_f2_pid[i]);
        for (Int_t j = 0; j < graphs_f2_pid[i]->GetN(); j++) {
            Double_t x, y;
            graphs_f2_pid[i]->GetPoint(j, x, y);
            TText *txt = new TText(x + 3.0, y, Form("%s_%d+", ion_names[i].c_str(), ion_charges[i]));
            txt->SetTextAlign(12);
            if (ion_colors[i] == 0) {
                txt->SetTextColor(kRed);
            } else if (ion_colors[i] == 1) {
                txt->SetTextColor(kBlue);
            } else {
                txt->SetTextColor(kBlack);
            }
            txts_f2.emplace_back(txt);
        }
    }
    mg_f2->Draw("ap");
    for (Size_t i = 0, n = txts_f2.size(); i < n; i++) {
        txts_f2[i]->Draw("same");
    }
    gPad->SetGrid();
    c_f2->Update();

    TCanvas *c_f3 = new TCanvas("F3_canvas", "F3_canvas", 800, 800);
    c_f3->cd();
    TMultiGraph *mg_f3 = new TMultiGraph();
    mg_f3->SetTitle("F3_PID; F3 RF [ns]; PPACs/MWDCs TOF [ns]");
    mg_f3->GetHistogram()->GetXaxis()->SetLimits(f3_rf_range[0], f3_rf_range[1]);
    mg_f3->GetHistogram()->GetYaxis()->SetRangeUser(tof_range[0], tof_range[1]);
    mg_f3->GetHistogram()->GetYaxis()->SetTitleOffset(1.3);
    mg_f3->GetHistogram()->GetXaxis()->SetTitleOffset(1.3);

    std::vector<TText *> txts_f3;
    for (Size_t i = 0, n = graphs_f3_pid.size(); i < n; i++) {
        mg_f3->Add(graphs_f3_pid[i]);
        for (Int_t j = 0; j < graphs_f3_pid[i]->GetN(); j++) {
            Double_t x, y;
            graphs_f3_pid[i]->GetPoint(j, x, y);
            TText *txt = new TText(x + 3.0, y, Form("%s_%d+", ion_names[i].c_str(), ion_charges[i]));
            txt->SetTextAlign(12);
            if (ion_colors[i] == 0) {
                txt->SetTextColor(kRed);
            } else if (ion_colors[i] == 1) {
                txt->SetTextColor(kBlue);
            } else {
                txt->SetTextColor(kBlack);
            }
            txts_f3.emplace_back(txt);
        }
    }
    mg_f3->Draw("ap");
    for (Size_t i = 0, n = txts_f3.size(); i < n; i++) {
        txts_f3[i]->Draw("same");
    }
    gPad->SetGrid();
    c_f3->Update();

    gDirectory->mkdir("pid");
    gDirectory->cd("pid");
    gDirectory->Add(mg_f2);
    gDirectory->Add(mg_f3);
    gDirectory->Add(c_f2);
    gDirectory->Add(c_f3);
    gDirectory->cd("..");

    if (fIsBatch) {
        gROOT->SetBatch(kFALSE);
    }
}

void TCRIBPIDProcessor::Process() {}

void TCRIBPIDProcessor::LoadPIDyaml() {
    Info("Init", "Loading yaml file...");
    FileStat_t info;
    if (gSystem->GetPathInfo(fFileName.Data(), info) != 0) {
        SetStateError(Form("File %s does not exist.", fFileName.Data()));
        return;
    }

    YAML::Node yaml_all = YAML::LoadFile(fFileName.Data());

#if 0 // for debug
    YAML::Emitter emitter;
    emitter << yaml_all;
    std::cout << emitter.c_str() << std::endl;
    std::cout << yaml_all.size() << std::endl;
#endif

    // set ions
    YAML::Node yaml_ions = yaml_all[kNodeKeyIons].as<YAML::Node>();
    for (Size_t i = 0, n = yaml_ions.size(); i < n; i++) {
        IntVec_t ion_config = yaml_ions[i].as<std::vector<int>>();
        if (ion_config.size() != 4) {
            std::cerr << "input yaml file: ion array size is not 4!" << std::endl;
            return;
        }

        ion_names.emplace_back(amdc::GetEl(ion_config[0]));
        ion_massnum.emplace_back(ion_config[1]);
        ion_charges.emplace_back(ion_config[2]);
        ion_masses.emplace_back(amdc::Mass(ion_config[0], ion_config[1]) * amdc::amu);
        ion_colors.emplace_back(ion_config[3]);
    }

    // set BLD parameters
    YAML::Node yaml_f1 = yaml_all[kNodeKeyF1Param].as<YAML::Node>();
    f1_brho = yaml_f1[kNodeKeyBrho].as<double>();
    degrader_mat = yaml_f1[kNodeKeyDegMat].as<std::string>();
    degrader_thick = 1.0e-3 * yaml_f1[kNodeKeyDegThickness].as<double>();
    rf_period = yaml_f1[kNodeKeyRfPeriod].as<double>();

    YAML::Node yaml_f2 = yaml_all[kNodeKeyF2Param].as<YAML::Node>();
    f2_ppac_thickness = 1.0e-3 * yaml_f2[kNodeKeyPPACThickness].as<double>();
    f2_ssd_thickness = 1.0e-3 * yaml_f2[kNodeKeySSDThickness].as<double>();
    f2_rf_offset = yaml_f2[kNodeKeyRfOffset].as<double>();
    f2_rf_range = yaml_f2[kNodeKeyRfRange].as<std::vector<double>>();
    energy_range = yaml_f2[kNodeKeyERange].as<std::vector<double>>();

    YAML::Node yaml_f3 = yaml_all[kNodeKeyF3Param].as<YAML::Node>();
    a_thickness = 1.0e-3 * yaml_f3[kNodeKeyAThickness].as<double>();
    b_thickness = 1.0e-3 * yaml_f3[kNodeKeyBThickness].as<double>();
    distance = yaml_f3[kNodeKeyDistance].as<double>();
    trigger = yaml_f3[kNodeKeyTrigger].as<ushort>();
    f3_rf_offset = yaml_f3[kNodeKeyRfOffset].as<double>();
    tof_offset = yaml_f3[kNodeKeyTofOffset].as<double>();
    f3_rf_range = yaml_f3[kNodeKeyRfRange].as<std::vector<double>>();
    tof_range = yaml_f3[kNodeKeyTofRange].as<std::vector<double>>();
}

void TCRIBPIDProcessor::SetSRIMObject() {
    Info("Init", "Setting TSrim object...");
    Info("Init", "\t(Z, A) is same but Q is different, warning message will appear...");
    const char *tsrim_path = std::getenv("TSRIM_DATA_HOME");
    if (!tsrim_path) {
        SetStateError("TSRIM_DATA_HOME environment variable is not defined");
        return;
    }
    srim = new TSrim();
    for (Size_t iPart = 0, n = ion_names.size(); iPart < n; iPart++) {
        Int_t z = amdc::GetZ(ion_names[iPart]);
        Int_t a = ion_massnum[iPart];
        srim->AddElement("srim", 16,
                         Form("%s/%s/range_fit_pol16_%s.txt", tsrim_path, degrader_mat.c_str(), degrader_mat.c_str()),
                         z, a);

        srim->AddElement("srim", 16,
                         Form("%s/si/range_fit_pol16_si.txt", tsrim_path),
                         z, a);

        if (degrader_mat != "mylar") {
            srim->AddElement("srim", 16,
                             Form("%s/mylar/range_fit_pol16_mylar.txt", tsrim_path),
                             z, a);
        }
    }
}
