#include <TStyle.h>
#include <TSystem.h>
// #include <TApplication.h>
#include <TCanvas.h>
#include <TPad.h>
#include <TH1.h>
#include <TFrame.h>
#include <TROOT.h>
// #include <TChain.h>
#include <TFile.h>
// #include <TMath.h>
// #include <TCutG.h>
#include <TGraph.h>
#include <TText.h>
#include <TLatex.h>
#include <TString.h>
#include <stdio.h>
// #include <math>
// #include <stdlib>
// #include <TProof.h>
// #include <TVector3.h>
// #include <TLorentzVector.h>
#include <iostream>
// #include <strstream>
#include <fstream>
#include <string>
#include <vector>
// #include <array>
#include <iomanip>
#include <chrono>

using namespace std;

extern "C"
{
    void enewzsub_(int *z1, float *m1, float *e, char matter1[33],
                   int *unit_pressure, float *pressure, float *temperature,
                   int *unit_thick, float *thick1, float *aft_ene);
}

// #include "enewz.h" // parameter file for eoldz

Int_t main()
{

#include "enewz_prm_const.C"
#include "enewz_prm_www.C"

    // Time stamp
    // auto now = chrono::system_clock::now();
    // time_t end_time = chrono::system_clock::to_time_t(now);
    // cout << "Current Time and Date: "
    // cout << ctime(&end_time) << endl;
    TString time_disp = Form("%d/%02d/%02d %02d:%02d:%02d",
                             year + 1900, mon + 1, mday, hour, min, sec);
    TString time_file = Form("%d%02d%02d-%02d%02d%02d",
                             year + 1900, mon + 1, mday, hour, min, sec);

    // output file to save graphs
    // ofstream fout(Form("%s/output/output_%s.txt",path,time_file));
    TFile *fgr = new TFile(Form("%s/output/pid_result_%s.root",
                                path, time_file.Data()),
                           "RECREATE");
    // TApplication theApp("App", NULL, NULL);

    /* Structure for isotope list*/
    struct str1
    {
        Int_t z;
        Int_t a;
        Char_t el[3];
        float m;
    };
    std::vector<str1> isotope;
    str1 dat_mass;

    /* Structure for specified ions*/
    struct str2
    {
        Int_t a;
        Char_t el[3];
        Int_t q;
        Int_t ref;
    };
    std::vector<str2> ion;
    str2 dat_ion;

    // read isotope data
    ifstream fmass(Form("%s/input/mass.dat", path));
    while (!fmass.eof())
    {
        fmass >> dat_mass.z >> dat_mass.a >> dat_mass.el >> dat_mass.m;
        if (fmass.eof())
            break;
        isotope.push_back(dat_mass);
    }
    fmass.close();
    // cout << isotope.size() << endl;

    // include parameter file
    // #include "enewz_prm_he6_2022.C"
    ifstream fions(Form("%s/input/ion_list.txt", path));
    while (!fions.eof())
    {
        fions >> dat_ion.a >> dat_ion.el >> dat_ion.q >> dat_ion.ref;
        if (fions.eof())
            break;
        ion.push_back(dat_ion);
        /* cout << dat_ion.a << " " */
        /*   << dat_ion.el << " " */
        /*   << dat_ion.q << " " */
        /*   << dat_ion.ref << endl; */
    }
    fions.close();
    // cout << ion.size() << endl;

    fgr->cd();

    gStyle->SetOptStat(0);
    gStyle->SetTextFont(62);
    gStyle->SetTextSize(TextSize);
    gStyle->SetLabelFont(62, "XY");
    gStyle->SetLabelSize(TextSize, "XY");
    gStyle->SetTitleFont(62, "XY");
    gStyle->SetTitleSize(TextSize, "XY");
    gStyle->SetTitleFontSize(0.8 * TextSize);

    //--------------------------------------------
    // TCanvas *c1=new TCanvas("c1","c1",0,0,800,800);
    // c1->Divide(2,2);
    TCanvas *c2 = new TCanvas("c2", "c2", 1300, 0, 600, 600);
    TCanvas *c3 = new TCanvas("c3", "c3", 1700, 0, 600, 600);
    TCanvas *c3_2 = new TCanvas("c3_2", "c3_2", 2100, 0, 600, 600);
    TH1F *fr2, *fr3, *fr3_2;
    TLatex *tx2, *tx3, *tx3_2;
    if (!swap_xy)
    {
        c2->cd();
        fr2 = gPad->DrawFrame(Tmin_f2, Emin_f2, Tmax_f2, Emax_f2);
        fr2->GetXaxis()->SetTitle("T_{F2PPAC - RF} (ns)");
        fr2->GetYaxis()->SetTitle("E_{SSD after F2PPAC} (MeV)");
        c3->cd();
        fr3 = gPad->DrawFrame(Tmin_f3, Tppacmin, Tmax_f3, Tppacmax);
        if (ppaca_trig)
            fr3->GetXaxis()->SetTitle("T_{F3PPACa - RF} (ns)");
        else
            fr3->GetXaxis()->SetTitle("T_{F3PPACb - RF} (ns)");
        fr3->GetYaxis()->SetTitle("T_{F3PPACa - F3PPACb} (ns)");
        c3_2->cd();
        fr3_2 = gPad->DrawFrame(Tmin_f3, Emin_f3, Tmax_f3, Emax_f3);
        fr3_2->GetXaxis()->SetTitle("T_{F3PPAC - RF} (ns)");
        fr3_2->GetYaxis()->SetTitle("E_{SSD sfter F3PPAC} (MeV)");
    }
    else
    {
        c2->cd();
        fr2 = gPad->DrawFrame(Emin_f2, Tmin_f2, Emax_f2, Tmax_f2);
        fr2->GetXaxis()->SetTitle("E_{SSD after F2PPAC} (MeV)");
        fr2->GetYaxis()->SetTitle("T_{F2PPAC - RF} (ns)");
        c3->cd();
        fr3 = gPad->DrawFrame(Tppacmin, Tmin_f3, Tppacmax, Tmax_f3);
        fr3->GetXaxis()->SetTitle("T_{F3PPACa - F3PPACb} (ns)");
        if (ppaca_trig)
            fr3->GetYaxis()->SetTitle("T_{F3PPACa - RF} (ns)");
        else
            fr3->GetYaxis()->SetTitle("T_{F3PPACb - RF} (ns)");
        c3_2->cd();
        fr3_2 = gPad->DrawFrame(Emin_f3, Tmin_f3, Emax_f3, Tmax_f3);
        fr3_2->GetXaxis()->SetTitle("E_{SSD sfter F3PPAC} (MeV)");
        fr3_2->GetYaxis()->SetTitle("T_{F3PPAC - RF} (ns)");
    }
    //--------------------------------------------
    c2->cd();
    gPad->SetMargin(lm, rm, bm, tm);
    fr2->Draw();
    fr2->GetXaxis()->CenterTitle();
    fr2->GetXaxis()->SetTitleOffset(ti_xoff);
    fr2->GetYaxis()->CenterTitle();
    fr2->GetYaxis()->SetTitleOffset(ti_yoff);
    // fr2->SetTitle(ctime(&end_time));
    fr2->SetTitle(time_disp);
    gPad->SetGrid(1);
    // tx_t->Draw();
    c2->Update();
    gSystem->ProcessEvents();
    //--------------------------------------------
    c3->cd();
    gPad->SetMargin(lm, rm, bm, tm);
    fr3->Draw();
    fr3->GetXaxis()->CenterTitle();
    fr3->GetXaxis()->SetTitleOffset(ti_xoff);
    fr3->GetYaxis()->CenterTitle();
    fr3->GetYaxis()->SetTitleOffset(ti_yoff);
    // fr3->SetTitle(ctime(&end_time));
    fr3->SetTitle(time_disp);
    gPad->SetGrid(1);
    c3->Update();
    gSystem->ProcessEvents();
    //--------------------------------------------
    if (adv_set)
    {
        c3_2->cd();
        gPad->SetMargin(lm, rm, bm, tm);
        fr3_2->Draw();
        fr3_2->GetXaxis()->CenterTitle();
        fr3_2->GetXaxis()->SetTitleOffset(ti_xoff);
        fr3_2->GetYaxis()->CenterTitle();
        fr3_2->GetYaxis()->SetTitleOffset(ti_yoff);
        // fr3_2->SetTitle(ctime(&end_time));
        fr3_2->SetTitle(time_disp);
        gPad->SetGrid(1);
        c3_2->Update();
        gSystem->ProcessEvents();
    }
    //--------------------------------------------
    TString stmp;
    std::vector<Double_t> Ef2, Tf2, Tppacf3, Tf3, Ef3;
    std::vector<Double_t> Ef2_0, Tf2_0, Tppacf3_0, Tf3_0, Ef3_0;
    std::vector<Double_t> Ef2_1rm, Tf2_1rm, Tppacf3_1rm, Tf3_1rm, Ef3_1rm;
    std::vector<Double_t> Ef2_2nd, Tf2_2nd, Tppacf3_2nd, Tf3_2nd, Ef3_2nd;
    std::vector<Double_t> Ef2_pen, Tf2_pen, Tppacf3_pen, Tf3_pen, Ef3_pen;

    Bool_t penf2flag = false;
    Bool_t penf3flag = false;

    // Int_t a1rm = ion1rm.at(0).a;;:
    // Char_t el1rm[3];
    // strcpy(el1rm,ion1rm.at(0).el);
    // //Int_t q1rm = ion1rm.at(0).q;:L<+
    // Int_t a2nd;
    Char_t el2nd[3];
    // Int_t q2nd;
    Int_t n2nd = 0;

    Int_t krep = 15; // number of RF repeatign
    // Int_t l=0; // sequential number for reference
    // vecotr<Int_t> vlref; // l when refj=1 or 2

    // fout << ctime(&end_time) << "[Result] " << endl;
    fout << time_disp << endl;
    fout << "[Result] " << endl;
    fout << right << std::setw(10) << "Ion name: "
         << right << std::setw(11) << "E_F1 "
         << right << std::setw(11) << "E_F2SSD "
         << right << std::setw(11) << "TOF_F0-F2 "
         << right << std::setw(11) << "TOF_F0-F3 "
         << right << std::setw(11) << "TOF_F3PPACs "
         << right << std::setw(11) << "E_F3SSD  "
         << endl;
    fout << right << std::setw(10) << " "
         << right << std::setw(11) << "(MeV),"
         << right << std::setw(11) << "(MeV),"
         << right << std::setw(11) << "(ns),"
         << right << std::setw(11) << "(ns),"
         << right << std::setw(11) << "(ns),"
         << right << std::setw(11) << "(MeV) "
         << endl;
    for (Int_t j = 0; j < ion.size(); j++)
    { // specified ions in enewz_prm.C
        Int_t aj = ion.at(j).a;
        Char_t elj[3];
        strcpy(elj, ion.at(j).el);
        Int_t qj = ion.at(j).q;
        Int_t refj = ion.at(j).ref;
        if (refj == 2)
        {
            // a2nd = ion.at(j).a;
            strcpy(el2nd, ion.at(j).el);
            // q2nd = ion.at(j).q;
            n2nd++; // to see duplication of ref=2
        }
        for (Int_t i = 0; i < isotope.size(); i++)
        { // all isotopes in the list mass.dat
            Int_t zi = isotope.at(i).z;
            Int_t ai = isotope.at(i).a;
            Char_t eli[3];
            strcpy(eli, isotope.at(i).el);
            float mi = isotope.at(i).m;
            // cout << th_ppac_f3 << endl;
            if (ai == aj && !strcmp(eli, elj))
            {
                // Brho -> E (relativistic)
                Epu0 = mu * (sqrt(pow(brho * qj / mi * c / mu, 2) + 1.) - 1.);
                // Ef2pu = Ef3pu = Epu;
                //  Energy loss in PPAC @F2
                enewzsub_(&zi, &mi, &Epu0,
                          mylar, &unit_pressure, &pressure,
                          &temperature, &unit_mm, &th_ppac_f2, &Ef2pu);
                // Energy deposit in SSD @F2
                Epu = Ef2pu;
                enewzsub_(&zi, &mi, &Epu,
                          si, &unit_pressure, &pressure,
                          &temperature, &unit_mm, &th_ssd_f2, &Ef2pu);
                Eresf2pu = Epu - Ef2pu;
                penf2flag = false;
                if (Ef2pu > 0)
                    penf2flag = true;
                // Energy loss in PPAC a @F3
                enewzsub_(&zi, &mi, &Epu0,
                          mylar, &unit_pressure, &pressure,
                          &temperature, &unit_mm, &th_ppac_f3, &Ef3ppacapu);
                // Energy loss in PPAC b @F3
                Epu = Ef3ppacapu;
                enewzsub_(&zi, &mi, &Epu,
                          mylar, &unit_pressure, &pressure,
                          &temperature, &unit_mm, &th_ppac_f3, &Epu);
                // Energy loss in chamber window @F3
                enewzsub_(&zi, &mi, &Epu,
                          win_f3, &unit_pressure, &pressure,
                          &temperature, &unit_mm, &th_win_f3, &Epu);
                // Energy loss in target gas @F3
                enewzsub_(&zi, &mi, &Epu,
                          gas_f3, &unit_pressure, &p_trg_f3,
                          &temperature, &unit_mm, &l_win_ssd_f3, &Epu);
                // Energy loss in SSD dead layer @F3
                enewzsub_(&zi, &mi, &Epu,
                          al, &unit_pressure, &pressure,
                          &temperature, &unit_mm, &th_ssd_dl_f3, &Epu);
                // Energy deposit in SSD @F3
                // Epu = Ef3pu;
                enewzsub_(&zi, &mi, &Epu,
                          si, &unit_pressure, &pressure,
                          &temperature, &unit_mm, &th_ssd_f3, &Ef3ssdpu);
                Eresf3pu = Epu - Ef3ssdpu;
                penf3flag = false;
                if (Ef3ssdpu > 0)
                    penf3flag = true;
                Double_t v = c / sqrt(1. + mu / 2. / Epu0); // relativistic
                // Double_t vppac = c/sqrt(1. + mu/2./Ef3pu); // relativistic
                Double_t vppac = c / sqrt(1. + mu / 2. / Ef3ppacapu); // relativistic
                stmp.Form("^{%d}%s^{%d+}", aj, elj, qj);
                for (Int_t k = 0; k < krep; k++)
                { // number of RF repeation
                    /* Tf2.push_back( l*1.e3/c*sqrt(mu/2./Epu0) */
                    // Tf2.push_back( - lf2*1.e3/v - Toff_f2 + double(k)*Trf); // (ns)
                    Tf2.push_back(-lf2 * 1.e3 / v + Toff_f2 + double(k) * Trf); // (ns)
                    Ef2.push_back(Eresf2pu * mi);
                    Ef3.push_back(Eresf3pu * mi);
                    // Ef2.push_back( Ef2pu*mi*0.825 );
                    // cout << Toff_f2f3 << " " << Toff_f3ppac << " " << vppac << " " << v << endl;
                    if (ppaca_trig)
                    { // true: PPACa trigger
                        // Tf3.push_back( - lf3*1.e3/v - Toff_f3 + double(k)*Trf); // (ns)
                        // Tf3.push_back( - lf3*1.e3/v - Toff_f2 - Toff_f2f3 - Toff_f3
                        Tf3.push_back(-lf3 * 1.e3 / v + Toff_f2 - Toff_f2f3 + Toff_f3 + double(k) * Trf); // (ns)
                        Tppacf3.push_back(lppac / vppac + Toff_f3ppac);                                   // (ns)
                    }
                    else
                    { // false: PPACb trigger
                        // Tf3.push_back( - lf3*1.e3/v  - lppac/vppac - Toff_f3
                        Tf3.push_back(-lf3 * 1.e3 / v - lppac / vppac
                                      //- Toff_f2 - Toff_f2f3 - Toff_f3
                                      + Toff_f2 - Toff_f2f3 + Toff_f3 + double(k) * Trf); // (ns)
                        // Tppacf3.push_back( - lppac/vppac - Toff_f3ppac ); // (ns)
                        Tppacf3.push_back(lppac / vppac + Toff_f3ppac); // (ns)
                    }
                    // if(aj==a1rm && !strcmp(elj,el1rm)){ // && qj==q1rm){
                    if (refj == 1)
                    {
                        Tf2_1rm.push_back(Tf2.back());
                        Ef2_1rm.push_back(Ef2.back());
                        Tf3_1rm.push_back(Tf3.back());
                        Tppacf3_1rm.push_back(Tppacf3.back());
                        Ef3_1rm.push_back(Ef3.back());
                        //}else if(aj==a2nd && !strcmp(elj,el2nd)){ // && qj==q2nd){
                    }
                    else if (refj == 2)
                    {
                        Tf2_2nd.push_back(Tf2.back());
                        Ef2_2nd.push_back(Ef2.back());
                        Tf3_2nd.push_back(Tf3.back());
                        Tppacf3_2nd.push_back(Tppacf3.back());
                        Ef3_2nd.push_back(Ef3.back());
                    }
                    else
                    {
                        Tf2_0.push_back(Tf2.back());
                        Ef2_0.push_back(Ef2.back());
                        Tf3_0.push_back(Tf3.back());
                        Tppacf3_0.push_back(Tppacf3.back());
                        Ef3_0.push_back(Ef3.back());
                    }
                    if (Tmin_f2 < Tf2.at(j * krep + k) + 3. && Tf2.at(j * krep + k) + 3. < Tmax_f2)
                    {
                        c2->cd();
                        /* TLatex *tx2=new */
                        /*   TLatex(Tf2.at(j*krep+k)+3., Ef2.at(j*krep+k), stmp); */
                        /* //TLatex(Ef2.at(j*krep+k), Tf2.at(j*krep+k)+3., stmp); */
                        if (!swap_xy)
                            tx2 = new TLatex(Tf2.at(j * krep + k) + 3., Ef2.at(j * krep + k), stmp);
                        else
                            tx2 = new TLatex(Ef2.at(j * krep + k), Tf2.at(j * krep + k) + 3., stmp);
                        tx2->SetTextAlign(12);
                        // if(aj==a1rm && !strcmp(elj,el1rm)) // && qj==q1rm)
                        if (refj == 1)
                            tx2->SetTextColor(kBlue); // reference ion
                        // else if(aj==a2nd && !strcmp(elj,el2nd)) // && qj==q2nd)
                        else if (refj == 2)
                            tx2->SetTextColor(kRed); // reference ion
                        else if (penf2flag)
                        {
                            tx2->SetTextColor(kGray + 1);
                            Tf2_pen.push_back(Tf2.back());
                            Ef2_pen.push_back(Ef2.back());
                        }
                        else
                            tx2->SetTextColor(kBlack);
                        tx2->Draw();
                        // tx2->SetName(Form("tx2_%d_%d",i,j));
                        tx2->SetName("tx2");
                        tx2->Write();
                    }
                    if (Tmin_f3 < Tf3.at(j * krep + k) + 3. && Tf3.at(j * krep + k) + 3. < Tmax_f3)
                    {
                        c3->cd();
                        /* TLatex *tx3=new */
                        /*   TLatex(Tf3.at(j*krep+k)+3., Tppacf3.at(j*krep+k), stmp); */
                        /* //TLatex(Tppacf3.at(j*krep+k), Tf3.at(j*krep+k)+3., stmp); */
                        if (!swap_xy)
                            tx3 = new TLatex(Tf3.at(j * krep + k) + 3., Tppacf3.at(j * krep + k), stmp);
                        else
                            tx3 = new TLatex(Tppacf3.at(j * krep + k), Tf3.at(j * krep + k) + 3., stmp);
                        tx3->SetTextAlign(12);
                        // if(aj==a1rm && !strcmp(elj,el1rm)) // && qj==q1rm)
                        if (refj == 1)
                            tx3->SetTextColor(kBlue); // reference ion
                        // else if(aj==a2nd && !strcmp(elj,el2nd)) // && qj==q2nd)
                        else if (refj == 2)
                            tx3->SetTextColor(kRed); // reference ion
                        else
                            tx3->SetTextColor(kBlack);
                        tx3->Draw();
                        tx3->SetName("tx3");
                        tx3->Write();
                        ////
                        // cout << "c3_2" << endl;
                        c3_2->cd();
                        /* TLatex *tx3_2=new */
                        /*   TLatex(Tf3.at(j*krep+k)+3., Ef3.at(j*krep+k), stmp); */
                        /*   //TLatex(Ef3.at(j*krep+k), Tf3.at(j*krep+k)+3., stmp); */
                        if (!swap_xy)
                            tx3_2 = new TLatex(Tf3.at(j * krep + k) + 3., Ef3.at(j * krep + k), stmp);
                        else
                            tx3_2 = new TLatex(Ef3.at(j * krep + k), Tf3.at(j * krep + k) + 3., stmp);
                        tx3_2->SetTextAlign(12);
                        // if(aj==a1rm && !strcmp(elj,el1rm)) // && qj==q1rm)
                        if (refj == 1)
                            tx3_2->SetTextColor(kBlue); // reference ion
                        // else if(aj==a2nd && !strcmp(elj,el2nd)) // && qj==q2nd)
                        else if (refj == 2)
                            tx3_2->SetTextColor(kRed); // reference ion
                        else if (penf3flag)
                        {
                            tx3_2->SetTextColor(kGray + 1);
                            Tf3_pen.push_back(Tf3.back());
                            Tppacf3_pen.push_back(Tppacf3.back());
                            Ef3_pen.push_back(Ef3.back());
                        }
                        else
                            tx3_2->SetTextColor(kBlack);
                        tx3_2->Draw();
                        tx3_2->SetName("tx3_2");
                        tx3_2->Write();
                    }
                    // l++;
                } // for k
                stmp.Form("%d%s%d+ : ", aj, elj, qj);
                fout << right << std::setw(10);
                fout << stmp;
                fout << fixed << setw(10) << setprecision(2) << Epu0 * mi << ","
                     << fixed << setw(10) << setprecision(2) << Ef2.at(j * krep) << ","
                     << fixed << setw(10) << setprecision(2) << -Tf2.at(j * krep) << ","
                     << fixed << setw(10) << setprecision(2) << -Tf3.at(j * krep) << ","
                     << fixed << setw(10) << setprecision(2) << Tppacf3.at(j * krep) << ","
                     << fixed << setw(10) << setprecision(2) << Ef3.at(j * krep)
                     << endl;
                // cout << right << std::setw(10);
                // cout << stmp;
                // cout << fixed << setw(10) << setprecision(2) << Epu0*mi << ","
                //      << fixed << setw(10) << setprecision(2) << Ef2.at(j*krep) << ","
                //      << fixed << setw(10) << setprecision(2) << - Tf2.at(j*krep) << ","
                //      << fixed << setw(10) << setprecision(2) << - Tf3.at(j*krep) << ","
                //      << fixed << setw(10) << setprecision(2) << Tppacf3.at(j*krep) << ","
                //      << fixed << setw(10) << setprecision(2) << Ef3.at(j*krep)
                //      << endl;
                break;
            } // for i
        }     // for j
    }

    // Setup information
    fout << endl;
    fout << "[Condition]" << endl;
    fout << Form("Brho = %7.5f Tm", brho) << endl;
    fout << Form("RF period = %4.1f ns", Trf) << endl;
    // fout << Form("F2: PPAC thickness = %5.1f um (equiv. mylar), "
    //           "SSD thickness = %4.0f um",
    //           th_ppac_f2*1000., th_ssd_f2*1000.) << endl;
    fout << Form("F2: PPAC thickness = %4.1f um (equiv. mylar)", th_ppac_f2 * 1000.) << endl;
    fout << Form("    SSD thickness = %6.1f um", th_ssd_f2 * 1000.) << endl;
    fout << Form("F3: PPAC thickness = %4.1f um (equiv. mylar)", th_ppac_f3 * 1000.) << endl;
    fout << Form("    Distance between PPACs = %6.1f mm", lppac) << endl;
    if (adv_set)
    {
        fout << Form("    Target window material: %s", win_f3) << endl;
        fout << Form("    Target window thickness = %4.1f um", th_win_f3) << endl;
        fout << Form("    Target gas material: %s", gas_f3) << endl;
        fout << Form("    Target length (Window to SSD) = %5.1f mm", l_win_ssd_f3) << endl;
        fout << Form("    Target pressure = %5.1f Torr", p_trg_f3) << endl;
        fout << Form("    SSD dead layer thickness = %3.1f um", th_ssd_dl_f3 * 1000.) << endl;
        fout << Form("    SSD thickness = %6.1f um", th_ssd_f3 * 1000.) << endl;
    }
    if (ppaca_trig)
        fout << "    Trigger: PPACa" << endl;
    else
        fout << "    Trigger: PPACb" << endl;

    // TGraph *gr2, *gr2_1rm, *gr2_2nd;
    // TGraph *gr3, *gr3_1rm, *gr3_2nd;
    // TGraph *gr3_2, *gr3_2_1rm, *gr3_2_2nd;
    // if(!swap_xy){
    //   // All ions
    //   gr2=new TGraph(Tf2.size()-1,&(Tf2.at(0)),&(Ef2.at(0)));
    //   gr3=new TGraph(Tf3.size(),&(Tf3.at(0)),&(Tppacf3.at(0)));
    //   gr3_2=new TGraph(Tf3.size(),&(Tf3.at(0)),&(Ef3.at(0)));
    //   // Primary ion
    //   gr2_1rm=new TGraph(Tf2_1rm.size()-1,&(Tf2_1rm.at(0)),&(Ef2_1rm.at(0)));
    //   gr3_1rm=new TGraph(Tf3_1rm.size(),&(Tf3_1rm.at(0)),&(Tppacf3_1rm.at(0)));
    //   gr3_2_1rm=new TGraph(Tf3_1rm.size(),&(Tf3_1rm.at(0)),&(Ef3_1rm.at(0)));
    //   // Secondary ion of interest
    //   gr2_2nd=new TGraph(Tf2_2nd.size()-1,&(Tf2_2nd.at(0)),&(Ef2_2nd.at(0)));
    //   gr3_2nd=new TGraph(Tf3_2nd.size(),&(Tf3_2nd.at(0)),&(Tppacf3_2nd.at(0)));
    //   gr3_2_2nd=new TGraph(Tf3_2nd.size(),&(Tf3_2nd.at(0)),&(Ef3_2nd.at(0)));
    // }else{
    //   // All ions
    //   gr2=new TGraph(Tf2.size()-1,&(Ef2.at(0)),&(Tf2.at(0)));
    //   gr3=new TGraph(Tf3.size(),&(Tppacf3.at(0)),&(Tf3.at(0)));
    //   gr3_2=new TGraph(Tf3.size(),&(Ef3.at(0)),&(Tf3.at(0)));
    //   // Primary ion
    //   gr2_1rm=new TGraph(Tf2_1rm.size()-1,&(Ef2_1rm.at(0)),&(Tf2_1rm.at(0)));
    //   gr3_1rm=new TGraph(Tf3_1rm.size(),&(Tppacf3_1rm.at(0)),&(Tf3_1rm.at(0)));
    //   gr3_2_1rm=new TGraph(Tf3_1rm.size(),&(Ef3_1rm.at(0)),&(Tf3_1rm.at(0)));
    //   // Secondary ion of interest
    //   gr2_2nd=new TGraph(Tf2_2nd.size()-1,&(Ef2_2nd.at(0)),&(Tf2_2nd.at(0)));
    //   gr3_2nd=new TGraph(Tf3_2nd.size(),&(Tppacf3_2nd.at(0)),&(Tf3_2nd.at(0)));
    //   gr3_2_2nd=new TGraph(Tf3_2nd.size(),&(Ef3_2nd.at(0)),&(Tf3_2nd.at(0)));
    // }
    TGraph *gr2_0, *gr2_1rm, *gr2_2nd;
    TGraph *gr3_0, *gr3_1rm, *gr3_2nd;
    TGraph *gr3_2_0, *gr3_2_1rm, *gr3_2_2nd;

    if (!swap_xy)
    {
        // All ions
        if (!Tf2_0.empty())
            gr2_0 = new TGraph(Tf2_0.size(), &(Tf2_0.at(0)), &(Ef2_0.at(0)));
        if (!Tf3_0.empty())
        {
            gr3_0 = new TGraph(Tf3_0.size(), &(Tf3_0.at(0)), &(Tppacf3_0.at(0)));
            gr3_2_0 = new TGraph(Tf3_0.size(), &(Tf3_0.at(0)), &(Ef3_0.at(0)));
        }
        // Primary ion
        if (!Tf2_1rm.empty())
            gr2_1rm = new TGraph(Tf2_1rm.size(), &(Tf2_1rm.at(0)), &(Ef2_1rm.at(0)));
        if (!Tf3_1rm.empty())
        {
            gr3_1rm = new TGraph(Tf3_1rm.size(), &(Tf3_1rm.at(0)), &(Tppacf3_1rm.at(0)));
            gr3_2_1rm = new TGraph(Tf3_1rm.size(), &(Tf3_1rm.at(0)), &(Ef3_1rm.at(0)));
        }
        // Secondary ion of interest
        if (!Tf2_2nd.empty())
            gr2_2nd = new TGraph(Tf2_2nd.size(), &(Tf2_2nd.at(0)), &(Ef2_2nd.at(0)));
        if (!Tf3_2nd.empty())
        {
            gr3_2nd = new TGraph(Tf3_2nd.size(), &(Tf3_2nd.at(0)), &(Tppacf3_2nd.at(0)));
            gr3_2_2nd = new TGraph(Tf3_2nd.size(), &(Tf3_2nd.at(0)), &(Ef3_2nd.at(0)));
        }
    }
    else
    {
        // All ions
        if (!Tf2_0.empty())
            gr2_0 = new TGraph(Tf2_0.size(), &(Ef2_0.at(0)), &(Tf2_0.at(0)));
        if (!Tf3_0.empty())
        {
            gr3_0 = new TGraph(Tf3_0.size(), &(Tppacf3_0.at(0)), &(Tf3_0.at(0)));
            gr3_2_0 = new TGraph(Tf3_0.size(), &(Ef3_0.at(0)), &(Tf3_0.at(0)));
        }
        // Primary ion
        if (!Tf2_1rm.empty())
            gr2_1rm = new TGraph(Tf2_1rm.size(), &(Ef2_1rm.at(0)), &(Tf2_1rm.at(0)));
        if (!Tf3_1rm.empty())
        {
            gr3_1rm = new TGraph(Tf3_1rm.size(), &(Tppacf3_1rm.at(0)), &(Tf3_1rm.at(0)));
            gr3_2_1rm = new TGraph(Tf3_1rm.size(), &(Ef3_1rm.at(0)), &(Tf3_1rm.at(0)));
        }
        // Secondary ion of interest
        if (!Tf2_2nd.empty())
            gr2_2nd = new TGraph(Tf2_2nd.size(), &(Ef2_2nd.at(0)), &(Tf2_2nd.at(0)));
        if (!Tf3_2nd.empty())
        {
            gr3_2nd = new TGraph(Tf3_2nd.size(), &(Tppacf3_2nd.at(0)), &(Tf3_2nd.at(0)));
            gr3_2_2nd = new TGraph(Tf3_2nd.size(), &(Ef3_2nd.at(0)), &(Tf3_2nd.at(0)));
        }
    }

    // Drawing results
    // F2 E-TOF
    c2->cd();
    fr2->SetName("fr2");
    fr2->Write();

    // if( !Tf2_0.empty() ){
    if (gr2_0 != nullptr)
    {
        gr2_0->SetMarkerStyle(m_stl);
        gr2_0->SetMarkerSize(m_siz);
        gr2_0->Draw("P");
        gr2_0->SetName("gr2_0");
        gr2_0->Write();
    }

    if (gr2_1rm != nullptr)
    {
        gr2_1rm->SetMarkerStyle(m_stl);
        gr2_1rm->SetMarkerSize(m_siz);
        gr2_1rm->SetMarkerColor(kBlue);
        gr2_1rm->Draw("P");
        gr2_1rm->SetName("gr2_1rm");
        gr2_1rm->Write();
    }

    if (gr2_2nd != nullptr)
    {
        gr2_2nd->SetMarkerStyle(m_stl);
        gr2_2nd->SetMarkerSize(m_siz);
        gr2_2nd->SetMarkerColor(kRed);
        gr2_2nd->Draw("P");
        gr2_2nd->SetName("gr2_2nd");
        gr2_2nd->Write();
    }

    // Secondary ion penetrating SSD
    /* TGraph *gr2pen=new TGraph(Tf2_pen.size()-1,&(Tf2_pen.at(0)),&(Ef2_pen.at(0))); */
    /* gr2pen->SetMarkerStyle(m_stl); */
    /* gr2pen->SetMarkerSize(m_siz); */
    /* gr2pen->SetMarkerColor(kGray+1); */
    /* gr2pen->Draw("P"); */

    // F3 TOF-TOF
    c3->cd();
    fr3->SetName("fr3");
    fr3->Write();

    if (gr3_0 != nullptr)
    {
        gr3_0->SetMarkerStyle(m_stl);
        gr3_0->SetMarkerSize(m_siz);
        gr3_0->Draw("P");
        gr3_0->SetName("gr3_0");
        gr3_0->Write();
    }

    if (gr3_1rm != nullptr)
    {
        gr3_1rm->SetMarkerStyle(m_stl);
        gr3_1rm->SetMarkerSize(m_siz);
        gr3_1rm->SetMarkerColor(kBlue);
        gr3_1rm->Draw("P");
        gr3_1rm->SetName("gr3_1rm");
        gr3_1rm->Write();
    }

    if (gr3_2nd != nullptr)
    {
        gr3_2nd->SetMarkerStyle(m_stl);
        gr3_2nd->SetMarkerSize(m_siz);
        gr3_2nd->SetMarkerColor(kRed);
        gr3_2nd->Draw("P");
        gr3_2nd->SetName("gr3_2nd");
        gr3_2nd->Write();
    }

    c2->Update();
    c3->Update();
    gSystem->ProcessEvents();
    c2->Print(Form("%s/output/pi_f2_de-tof.png", path));
    c3->Print(Form("%s/output/pi_f3_tof-tof.png", path));

    // F3 E-TOF
    if (adv_set)
    {
        c3_2->cd();
        fr3_2->SetName("fr3_2");
        fr3_2->Write();

        if (gr3_2_0 != nullptr)
        {
            gr3_2_0->SetMarkerStyle(m_stl);
            gr3_2_0->SetMarkerSize(m_siz);
            gr3_2_0->Draw("P");
            gr3_2_0->SetName("gr3_2_0");
            gr3_2_0->Write();
        }

        if (gr3_2_1rm != nullptr)
        {
            gr3_2_1rm->SetMarkerStyle(m_stl);
            gr3_2_1rm->SetMarkerSize(m_siz);
            gr3_2_1rm->SetMarkerColor(kBlue);
            gr3_2_1rm->Draw("P");
            gr3_2_1rm->SetName("gr3_2_1rm");
            gr3_2_1rm->Write();
        }

        /* TGraph *gr3_2pen=new TGraph(Tf3_pen.size(),&(Tf3_pen.at(0)),&(Ef3_pen.at(0))); */
        /* gr3_2pen->SetMarkerStyle(m_stl); */
        /* gr3_2pen->SetMarkerSize(m_siz); */
        /* gr3_2pen->SetMarkerColor(kGray+1); */
        /* gr3_2pen->Draw("P"); */

        if (gr3_2_2nd != nullptr)
        {
            gr3_2_2nd->SetMarkerStyle(m_stl);
            gr3_2_2nd->SetMarkerSize(m_siz);
            gr3_2_2nd->SetMarkerColor(kRed);
            gr3_2_2nd->Draw("P");
            gr3_2_2nd->SetName("gr3_2_2nd");
            gr3_2_2nd->Write();
        }

        c3_2->Update();
        gSystem->ProcessEvents();
        c3_2->Print(Form("%s/output/pi_f3_de-tof.png", path));
    }

    // fout.close();
    //  c1->cd(1);
    //  c2->DrawClonePad();
    //  c1->cd(2);
    //  c3->DrawClonePad();
    //  c1->cd(3);
    //  c3_2->DrawClonePad();
    //  c1->Write();
    c2->Write();
    c3->Write();
    c3_2->Write();
    fgr->Close();
    /* theApp.Run(); */

    return 0;
}