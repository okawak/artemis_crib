/**
 * @file    TSolidAngleProcessor.cc
 * @brief
 * @author  Kodai Okawa<okawa@cns.s.u-tokyo.ac.jp>
 * @date    2024-01-18 22:37:37
 * @note
 */

#include "TSolidAngleProcessor.h"
#include "../reconst/TReactionInfo.h"
#include "../telescope/TTelescopeData.h"

#include <TArtemisUtil.h>
#include <TDataObject.h>
#include <constant.h>

#include <TClass.h>
#include <TClonesArray.h>
#include <TFile.h>
#include <TMath.h>

using art::TSolidAngleProcessor;

ClassImp(TSolidAngleProcessor);

TSolidAngleProcessor::TSolidAngleProcessor() : fInData_cm(NULL), fInData_det(NULL) {
    RegisterInputCollection("InputCollection_cm", "input branch (collection) name", fInputColName_cm, TString("input1"));
    RegisterInputCollection("InputCollection_det", "input branch (collection) name", fInputColName_det,
                            TString("input2"));

    DoubleVec_t init_d_vec;
    RegisterProcessorParameter("Nbin_angle", "Nbin of the angle histogram", fNbin_angle, 0);
    RegisterProcessorParameter("range_angle", "range of the angle histogram", fRange_angle, init_d_vec);
    RegisterProcessorParameter("Nbin_energy", "Nbin of the energy histogram", fNbin_energy, 0);
    RegisterProcessorParameter("range_energy", "range of the energy histogram", fRange_energy, init_d_vec);
    RegisterProcessorParameter("IsInverseKinematics", "inverse kinematics true/false", fIsIK, false);

    RegisterProcessorParameter("HistFile", "name of output histogram rootfile", fFileName, TString(""));
}

TSolidAngleProcessor::~TSolidAngleProcessor() {
    delete h1;
    delete h1_all;
    delete h2;
    h1 = NULL;
    h1_all = NULL;
    h2 = NULL;
}

void TSolidAngleProcessor::Init(TEventCollection *col) {
    Info("Init", "make solid angle histogram X: Ecm, Y: Thetacm");
    if (fRange_angle.size() != 2 || fRange_energy.size() != 2) {
        SetStateError("input yaml format is wrong");
        return;
    }
    Info("Init", "\t h(%d, %.1lf, %.1lf, %d, %.1lf, %.1lf)", fNbin_energy, fRange_energy[0], fRange_energy[1],
         fNbin_angle, fRange_angle[0], fRange_angle[1]);
    Info("Init", "making %s", fFileName.Data());

    fInData_cm = reinterpret_cast<TClonesArray **>(col->GetObjectRef(fInputColName_cm.Data()));
    if (!fInData_cm) {
        SetStateError(TString::Format("input not found: %s", fInputColName_cm.Data()));
        return;
    }
    const TClass *const cl_cm = (*fInData_cm)->GetClass();
    if (!cl_cm->InheritsFrom(art::TReactionInfo::Class())) {
        SetStateError("contents of input array must inherit from art::TReactionInfo");
    }

    fInData_det = reinterpret_cast<TClonesArray **>(col->GetObjectRef(fInputColName_det.Data()));
    if (!fInData_det) {
        SetStateError(TString::Format("input not found: %s", fInputColName_det.Data()));
        return;
    }
    const TClass *const cl_det = (*fInData_det)->GetClass();
    if (!cl_det->InheritsFrom(art::TTelescopeData::Class())) {
        SetStateError("contents of input array must inherit from art::TTelescopeData");
    }

    h1_all = new TH1D("normalize_1D", "normalize_1D", fNbin_energy, fRange_energy[0], fRange_energy[1]);
    h2_all = new TH2D("normalize_2D", "normalize_2D", fNbin_energy, fRange_energy[0], fRange_energy[1], fNbin_angle,
                      fRange_angle[0], fRange_angle[1]);
    h1 = new TH1D("SolidAngle_1D", "SolidAngle_1D", fNbin_energy, fRange_energy[0], fRange_energy[1]);
    h2 = new TH2D("SolidAngle_2D", "SolidAngle_2D", fNbin_energy, fRange_energy[0], fRange_energy[1], fNbin_angle,
                  fRange_angle[0], fRange_angle[1]);
}

void TSolidAngleProcessor::Process() {
    if ((*fInData_cm)->GetEntriesFast() != 1) {
        SetStateError("input reaction data branch entry is not 1");
        return;
    }

    const TDataObject *const inData = static_cast<TDataObject *>((*fInData_cm)->At(0));
    const TReactionInfo *const Data = dynamic_cast<const TReactionInfo *>(inData);
    h1_all->Fill(Data->GetEnergy());
    for (Int_t i = 0; i < fNbin_angle; i++) {
        Double_t angle_center = fRange_angle[0] + (fRange_angle[1] - fRange_angle[0]) / (2.0 * fNbin_angle) +
                                (Double_t)i * (fRange_angle[1] - fRange_angle[0]) / fNbin_angle;
        h2_all->Fill(Data->GetEnergy(), angle_center);
    }

    if ((*fInData_det)->GetEntriesFast() > 0) {
        if ((*fInData_det)->GetEntriesFast() > 1) {
            std::cerr << "not single particle detected" << std::endl;
            return;
        }

        h1->Fill(Data->GetEnergy());
        if (fIsIK) {
            h2->Fill(Data->GetEnergy(), 180.0 - Data->GetTheta()); // assume inverse kinematics
        } else {
            h2->Fill(Data->GetEnergy(), Data->GetTheta());
        }
    }
}

void TSolidAngleProcessor::PostLoop() {
    Util::PrepareDirectoryFor(fFileName);
    TFile *file = new TFile(fFileName, "recreate");
    if (!file) {
        std::cerr << "ERROR : cannot open " << fFileName << std::endl;
        return;
    }

    h1->Divide(h1_all);
    h2->Divide(h2_all);

    h1->Scale(4.0 * TMath::Pi());
    h2->Scale(4.0 * TMath::Pi());

    h1->Write("SolidAngle_1D");
    h2->Write("SolidAngle_2D");

    file->Close();
}
