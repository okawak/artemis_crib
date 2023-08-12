// K.Okawa created <okawa@cns.s.u-tokyo.ac.jp>

#include <fstream>
#include <sstream>
#include <string>

#include "TBeamEnergyCalculationSrim.h"
#include "TEnewzCalculator.h"

#include "constant.h"
#include "TDataObject.h"

#include <TClonesArray.h>
#include <TClass.h>
#include <TCanvas.h>
#include <TGraphErrors.h>
#include <TGraph2D.h>
#include <TAxis.h>
#include <TStyle.h>
#include <TF1.h>
#include <TMath.h>
#include <TSpline.h>

using art::TBeamEnergyCalculationSrim;

ClassImp(TBeamEnergyCalculationSrim)

TBeamEnergyCalculationSrim::TBeamEnergyCalculationSrim()
{
}

TBeamEnergyCalculationSrim::~TBeamEnergyCalculationSrim()
{
}

void TBeamEnergyCalculationSrim::Init(TEventCollection *col)
{
   SrimInit();
   std::cout << "==================================================" << std::endl;
	Info("Init", "calculation in Init function (only si26 use)");
   //Info("Init", "enewz test");
   //std::cout << "\tbefore: " << ini_energy << std::endl;
   //std::cout << "\tafter : " << art::enewz::enewz(fIonZCondition[0],fIonMCondition[0],ini_energy,char_mylar,0.0f,300.0f,0.020f) << std::endl;;
   //std::cout << std::endl;

   gStyle->SetMarkerStyle(20);
   gStyle->SetMarkerSize(0.8);
   gStyle->SetStatY(0.4);

   Double_t ppaca_min = 0.0;
   Double_t ppacb_min = 0.0;
   Double_t chi2_min = 1000.0;
   Double_t tmp = 1.0e+9;

   for(Double_t ppaca = 0.0085; ppaca<0.0100; ppaca+=0.0001){
      for(Double_t ppacb = 0.0090; ppacb<0.0135; ppacb+=0.0001){
         std::cout << "PPACa: 0.009 < " << ppaca << " < 0.011, PPACb: 0.009 < " << ppacb << " < 0.011" << std::endl;
         Double_t result = ObjFunc(ppaca, ppacb, false);
         //std::cout << "chi2: " << result << std::endl;
         if(tmp > result){
            tmp = result;
            ppaca_min = ppaca;
            ppacb_min = ppacb;
            chi2_min = result;
         }
      }
   }

   //TGraph2D *chi_dist = new TGraph2D();
   TGraph *chi_dist = new TGraph();
   Int_t chi_dist_count = 0;
   Double_t ppacs_low = 100.0;
   Double_t ppacs_high = 0.0;

   for(Double_t ppaca = 0.0085; ppaca<0.0100; ppaca+=0.0001){
      for(Double_t ppacb = 0.0090; ppacb<0.0135; ppacb+=0.0001){
         Double_t result = ObjFunc(ppaca, ppacb, false);
         if(result - chi2_min < 2.30){
            //chi_dist->SetPoint(chi_dist_count, ppaca, ppacb, -(result - chi2_min));
            chi_dist->SetPoint(chi_dist_count, ppaca, ppacb);
            chi_dist_count++;
            if(ppaca+ppacb < ppacs_low) ppacs_low = ppaca + ppacb;
            if(ppaca+ppacb > ppacs_high) ppacs_high = ppaca + ppacb;
         }
      }
   }
   gROOT->ProcessLine("zone");
   //chi_dist->Draw("colz");
   chi_dist->Draw("ap");
   gROOT->ProcessLine(Form("artcanvas->Print(\"figure/beam/energy/srim_chi2_dist.png\")"));

   Double_t ppac_tmp = ppaca_min + ppacb_min + 0.013;
   Double_t ini_energy = Brho2Energy(brho, si_M, si_Z);
   Double_t ene = SrimEnewz(si14mylar, ini_energy, ppac_tmp);
   //Double_t ene = SrimEnewz(0, ini_energy, ppac_tmp);
   Double_t ene_low = SrimEnewz(si14mylar, ini_energy, ppacs_low+0.013);
   //Double_t ene_low = SrimEnewz(0, ini_energy, ppacs_low+0.013);
   Double_t ene_high = SrimEnewz(si14mylar, ini_energy, ppacs_high+0.013f);
   //Double_t ene_high = SrimEnewz(0, ini_energy, ppacs_high+0.013f);
   std::cout << "==================================================" << std::endl;

   ObjFunc(ppaca_min, ppacb_min, true);
   std::cout << "RESULT:" << std::endl;
   std::cout << "\tppaca thickness: " << ppaca_min << ", ppacb thickness: " << ppacb_min << std::endl;
   std::cout << "\ttotal mylar: " << ppac_tmp << std::endl;
   std::cout << "\tinitial energy: " << ini_energy << std::endl;
   std::cout << "\tenergy after window: " << ene << std::endl;
   std::cout << "\t                      - " << ene - ene_high << std::endl;
   std::cout << "\t                      + " << ene_low - ene << std::endl;
}

void TBeamEnergyCalculationSrim::Process()
{
	Info("Process", "no process");
}



Double_t TBeamEnergyCalculationSrim::ObjFunc(Double_t ppaca, Double_t ppacb, Bool_t debug)
{
   Double_t distance[4] = {562.0, 562.2, 562.4, 562.6};
   Double_t chi2 = 0.0; 

   for(Int_t i=0; i<4; i++){
      Double_t each_ch2 = Getchi2(ppaca, ppacb, distance[i], i, debug);
      //std::cout << "chi2 in lowgain" << i << " : " << each_ch2 << std::endl;
      chi2 += each_ch2;
   }
   return chi2;
}

Double_t TBeamEnergyCalculationSrim::Getchi2(Double_t ppaca, Double_t ppacb, Double_t distance, Int_t i, Bool_t debug)
{
   Double_t lowgain[N];
   Double_t lowgain_err[N];
   Double_t lowgain_sigma[N];
   for(Int_t j=0; j<N; j++){
      if(i == 0){
         lowgain[j] = fLowgain1[j];
         lowgain_err[j] = fLowgain1_err[j];
         lowgain_sigma[j] = fLowgain1_sigma[j];
      }else if(i == 1){
         lowgain[j] = fLowgain2[j];
         lowgain_err[j] = fLowgain2_err[j];
         lowgain_sigma[j] = fLowgain2_sigma[j];
      }else if(i == 2){
         lowgain[j] = fLowgain3[j];
         lowgain_err[j] = fLowgain3_err[j];
         lowgain_sigma[j] = fLowgain3_sigma[j];
      }else if(i == 3){
         lowgain[j] = fLowgain4[j];
         lowgain_err[j] = fLowgain4_err[j];
         lowgain_sigma[j] = fLowgain4_sigma[j];
      }
      //std::cout << "lowgain" << i << " : " << lowgain[j] << std::endl; 
   }


   Double_t ene_ref[N] = {};
   for(Int_t j=0; j<N; j++){
      Double_t tmp_z = fIonZCondition[j];
      if(fIonCondition[j] == 3) tmp_z -= 1;
      Double_t ini_energy = Brho2Energy(brho, fIonMCondition[j], tmp_z);
      //std::cout << ini_energy << std::endl;

      // PPAC
      Double_t af_ppac_e = 0.0f;
      Double_t all_ppac = ppaca + ppacb;
      if(fPPACCondition[j] == 0) af_ppac_e = ini_energy;
      if(fPPACCondition[j] == 1){
         if(fIonCondition[j] == 0) af_ppac_e = SrimEnewz(si14mylar, ini_energy, ppaca);
         if(fIonCondition[j] == 1) af_ppac_e = SrimEnewz(al13mylar, ini_energy, ppaca);
         if(fIonCondition[j] == 2) af_ppac_e = SrimEnewz(mg12mylar, ini_energy, ppaca);
         if(fIonCondition[j] == 3) af_ppac_e = SrimEnewz(si13mylar, ini_energy, ppaca);
         //if(fIonCondition[j] == 0) af_ppac_e = SrimEnewz(0, ini_energy, ppaca);
         //if(fIonCondition[j] == 1) af_ppac_e = SrimEnewz(10, ini_energy, ppaca);
         //if(fIonCondition[j] == 2) af_ppac_e = SrimEnewz(15, ini_energy, ppaca);
         //if(fIonCondition[j] == 3) af_ppac_e = SrimEnewz(5, ini_energy, ppaca);
      }
      if(fPPACCondition[j] == 2){
         if(fIonCondition[j] == 0) af_ppac_e = SrimEnewz(si14mylar, ini_energy, ppacb);
         if(fIonCondition[j] == 1) af_ppac_e = SrimEnewz(al13mylar, ini_energy, ppacb);
         if(fIonCondition[j] == 2) af_ppac_e = SrimEnewz(mg12mylar, ini_energy, ppacb);
         if(fIonCondition[j] == 3) af_ppac_e = SrimEnewz(si13mylar, ini_energy, ppacb);
         //if(fIonCondition[j] == 0) af_ppac_e = SrimEnewz(0, ini_energy, ppacb);
         //if(fIonCondition[j] == 1) af_ppac_e = SrimEnewz(10, ini_energy, ppacb);
         //if(fIonCondition[j] == 2) af_ppac_e = SrimEnewz(15, ini_energy, ppacb);
         //if(fIonCondition[j] == 3) af_ppac_e = SrimEnewz(5, ini_energy, ppacb);
      }
      if(fPPACCondition[j] == 3){
         if(fIonCondition[j] == 0) af_ppac_e = SrimEnewz(si14mylar, ini_energy, all_ppac);
         if(fIonCondition[j] == 1) af_ppac_e = SrimEnewz(al13mylar, ini_energy, all_ppac);
         if(fIonCondition[j] == 2) af_ppac_e = SrimEnewz(mg12mylar, ini_energy, all_ppac);
         if(fIonCondition[j] == 3) af_ppac_e = SrimEnewz(si13mylar, ini_energy, all_ppac);
         //if(fIonCondition[j] == 0) af_ppac_e = SrimEnewz(0, ini_energy, all_ppac);
         //if(fIonCondition[j] == 1) af_ppac_e = SrimEnewz(10, ini_energy, all_ppac);
         //if(fIonCondition[j] == 2) af_ppac_e = SrimEnewz(15, ini_energy, all_ppac);
         //if(fIonCondition[j] == 3) af_ppac_e = SrimEnewz(5, ini_energy, all_ppac);
      }

      //std::cout << "lowgain" << i << " : " << af_ppac_e << std::endl; 

      // Window
      Double_t af_win_e = 0.0;
      if(fWindowCondition[j] == 0) af_win_e = af_ppac_e;
      if(fWindowCondition[j] == 1){
         if(fIonCondition[j] == 0) af_win_e = SrimEnewz(si14mylar, af_ppac_e, 0.023);
         if(fIonCondition[j] == 1) af_win_e = SrimEnewz(al13mylar, af_ppac_e, 0.023);
         if(fIonCondition[j] == 2) af_win_e = SrimEnewz(mg12mylar, af_ppac_e, 0.023);
         if(fIonCondition[j] == 3) af_win_e = SrimEnewz(si13mylar, af_ppac_e, 0.023);
         //if(fIonCondition[j] == 0) af_win_e = SrimEnewz(0, af_ppac_e, 0.023);
         //if(fIonCondition[j] == 1) af_win_e = SrimEnewz(10, af_ppac_e, 0.023);
         //if(fIonCondition[j] == 2) af_win_e = SrimEnewz(15, af_ppac_e, 0.023);
         //if(fIonCondition[j] == 3) af_win_e = SrimEnewz(5, af_ppac_e, 0.023);
      }
      if(fWindowCondition[j] == 2){
         if(fIonCondition[j] == 0) af_win_e = SrimEnewz(si14mylar, af_ppac_e, 0.013);
         if(fIonCondition[j] == 1) af_win_e = SrimEnewz(al13mylar, af_ppac_e, 0.013);
         if(fIonCondition[j] == 2) af_win_e = SrimEnewz(mg12mylar, af_ppac_e, 0.013);
         if(fIonCondition[j] == 3) af_win_e = SrimEnewz(si13mylar, af_ppac_e, 0.013);
         //if(fIonCondition[j] == 0) af_win_e = SrimEnewz(0, af_ppac_e, 0.013);
         //if(fIonCondition[j] == 1) af_win_e = SrimEnewz(10, af_ppac_e, 0.013);
         //if(fIonCondition[j] == 2) af_win_e = SrimEnewz(15, af_ppac_e, 0.013);
         //if(fIonCondition[j] == 3) af_win_e = SrimEnewz(5, af_ppac_e, 0.013);
      }

      // gas
      Double_t af_gas_e = 0.0;
      if(fPressure[j] < 25.0){
         af_gas_e = af_win_e;
      }else if(fPressure[j] < 75.0){
         if(fIonCondition[j] == 0) af_gas_e = SrimEnewz(si14he50torr, af_win_e, distance);
         if(fIonCondition[j] == 1) af_gas_e = SrimEnewz(al13he50torr, af_win_e, distance);
         if(fIonCondition[j] == 2) af_gas_e = SrimEnewz(mg12he50torr, af_win_e, distance);
         if(fIonCondition[j] == 3) af_gas_e = SrimEnewz(si13he50torr, af_win_e, distance);
         //if(fIonCondition[j] == 0) af_gas_e = SrimEnewz(1, af_win_e, distance);
         //if(fIonCondition[j] == 1) af_gas_e = SrimEnewz(11, af_win_e, distance);
         //if(fIonCondition[j] == 2) af_gas_e = SrimEnewz(16, af_win_e, distance);
         //if(fIonCondition[j] == 3) af_gas_e = SrimEnewz(6, af_win_e, distance);
      }else if(fPressure[j] < 125.0){
         if(fIonCondition[j] == 0) af_gas_e = SrimEnewz(si14he100torr, af_win_e, distance);
         if(fIonCondition[j] == 1) af_gas_e = SrimEnewz(al13he100torr, af_win_e, distance);
         if(fIonCondition[j] == 2) af_gas_e = SrimEnewz(mg12he100torr, af_win_e, distance);
         if(fIonCondition[j] == 3) af_gas_e = SrimEnewz(si13he100torr, af_win_e, distance);
         //if(fIonCondition[j] == 0) af_gas_e = SrimEnewz(2, af_win_e, distance);
         //if(fIonCondition[j] == 1) af_gas_e = SrimEnewz(12, af_win_e, distance);
         //if(fIonCondition[j] == 2) af_gas_e = SrimEnewz(17, af_win_e, distance);
         //if(fIonCondition[j] == 3) af_gas_e = SrimEnewz(7, af_win_e, distance);
      }else if(fPressure[j] < 175.0){
         if(fIonCondition[j] == 0) af_gas_e = SrimEnewz(si14he150torr, af_win_e, distance);
         if(fIonCondition[j] == 1) af_gas_e = SrimEnewz(al13he150torr, af_win_e, distance);
         if(fIonCondition[j] == 2) af_gas_e = SrimEnewz(mg12he150torr, af_win_e, distance);
         if(fIonCondition[j] == 3) af_gas_e = SrimEnewz(si13he150torr, af_win_e, distance);
         //if(fIonCondition[j] == 0) af_gas_e = SrimEnewz(3, af_win_e, distance);
         //if(fIonCondition[j] == 1) af_gas_e = SrimEnewz(13, af_win_e, distance);
         //if(fIonCondition[j] == 2) af_gas_e = SrimEnewz(18, af_win_e, distance);
         //if(fIonCondition[j] == 3) af_gas_e = SrimEnewz(8, af_win_e, distance);
      }

      // dead
      Double_t af_al_e = 0.0;
      if(fIonCondition[j] == 0) af_al_e = SrimEnewz(si14al, af_gas_e, dead);
      if(fIonCondition[j] == 1) af_al_e = SrimEnewz(al13al, af_gas_e, dead);
      if(fIonCondition[j] == 2) af_al_e = SrimEnewz(mg12al, af_gas_e, dead);
      if(fIonCondition[j] == 3) af_al_e = SrimEnewz(si13al, af_gas_e, dead);
      //if(fIonCondition[j] == 0) af_al_e = SrimEnewz(4, af_gas_e, dead);
      //if(fIonCondition[j] == 1) af_al_e = SrimEnewz(14, af_gas_e, dead);
      //if(fIonCondition[j] == 2) af_al_e = SrimEnewz(19, af_gas_e, dead);
      //if(fIonCondition[j] == 3) af_al_e = SrimEnewz(9, af_gas_e, dead);

      // energy deposit
      Double_t af_si_e = 0.0;
      af_si_e = af_al_e;

      ene_ref[j] = af_si_e;

      //std::cout << "lowgain" << i << " : " << ene_ref[j] << std::endl; 
   }


   gROOT->ProcessLine("zone");
   Int_t count = 0;
   for(Int_t j=0; j<N; ++j){
      //========================================================================
      //if(true){ // all
      if((fRunNumber[j] > 195)){ // run >= 196
      //if((TMath::Abs(fIonMCondition[j] - 26.0f) < 0.3f && fIonZCondition[j] == si_Z ) || (TMath::Abs(fIonMCondition[j] - 25.0f) < 0.3f && fIonZCondition[j] == al_Z ) ){ //26si14+ 25al13+
      //if(fRunNumber[j] > 195 && ((TMath::Abs(fIonMCondition[j] - 26.0f) < 0.3f && fIonZCondition[j] == si_Z ) || (TMath::Abs(fIonMCondition[j] - 25.0f) < 0.3f && fIonZCondition[j] == al_Z )) ){ //26si14+ 25al13+ and run >= 196
      //if((fRunNumber[j] < 203 && fRunNumber[j] > 195) && ((TMath::Abs(fIonMCondition[j] - 26.0f) < 0.3f && fIonZCondition[j] == si_Z ) || (TMath::Abs(fIonMCondition[j] - 25.0f) < 0.3f && fIonZCondition[j] == al_Z )) ){ //26si14+ 25al13+ and 202 >= run >= 196
      //if((fRunNumber[j] < 203 && fRunNumber[j] > 195)){ // 202 >= run >= 196
      //========================================================================
         count++;
      }
   }

   //TGraph *gr = new TGraph(N);
   TGraphErrors *gr = new TGraphErrors(count);
   Int_t tmp_count = 0;
   for (Int_t j=0; j<N; ++j){
      //========================================================================
      //if(true){ // all
      if((fRunNumber[j] > 195)){ // run >= 196
      //if((TMath::Abs(fIonMCondition[j] - 26.0f) < 0.3f && fIonZCondition[j] == si_Z ) || (TMath::Abs(fIonMCondition[j] - 25.0f) < 0.3f && fIonZCondition[j] == al_Z ) ){ //26si14+ 25al13+
      //if(fRunNumber[j] > 195 && ((TMath::Abs(fIonMCondition[j] - 26.0f) < 0.3f && fIonZCondition[j] == si_Z ) || (TMath::Abs(fIonMCondition[j] - 25.0f) < 0.3f && fIonZCondition[j] == al_Z )) ){ //26si14+ 25al13+ and run >= 196
      //if((fRunNumber[j] < 203 && fRunNumber[j] > 195) && ((TMath::Abs(fIonMCondition[j] - 26.0f) < 0.3f && fIonZCondition[j] == si_Z ) || (TMath::Abs(fIonMCondition[j] - 25.0f) < 0.3f && fIonZCondition[j] == al_Z )) ){ //26si14+ 25al13+ and 202 >= run >= 196
      //if((fRunNumber[j] < 203 && fRunNumber[j] > 195)){ // 202 >= run >= 196
      //========================================================================
         gr->SetPoint(tmp_count, lowgain[j], ene_ref[j]);
         //gr->SetPointError(tmp_count, lowgain_err[j], 0.0);
         gr->SetPointError(tmp_count, lowgain_sigma[j], 0.0);
         tmp_count++;
      }
   }
   gr->GetXaxis()->SetLimits(0.,4000.);
   gr->GetYaxis()->SetRangeUser(0.,70.);
   gr->SetTitle(Form("lowgain%d;ch;calculated energy (MeV)",i));
   gr->Draw("ap");

   TF1 *f = new TF1("f","[0]+x*[1]");
   f->SetParameters(0.1,1.0);
   gr->Fit(f,"q");
   f->Draw("same");

   if(debug){
      std::cout << "lowgain" << i << std::endl;
      for(Int_t j=0; j<N; j++){
         //========================================================================
         //if(true){ // all
         if((fRunNumber[j] > 195)){ // run >= 196
         //if((TMath::Abs(fIonMCondition[j] - 26.0f) < 0.3f && fIonZCondition[j] == si_Z ) || (TMath::Abs(fIonMCondition[j] - 25.0f) < 0.3f && fIonZCondition[j] == al_Z ) ){ //26si14+ 25al13+
         //if(fRunNumber[j] > 195 && ((TMath::Abs(fIonMCondition[j] - 26.0f) < 0.3f && fIonZCondition[j] == si_Z ) || (TMath::Abs(fIonMCondition[j] - 25.0f) < 0.3f && fIonZCondition[j] == al_Z )) ){ //26si14+ 25al13+ and run >= 196
         //if((fRunNumber[j] < 203 && fRunNumber[j] > 195) && ((TMath::Abs(fIonMCondition[j] - 26.0f) < 0.3f && fIonZCondition[j] == si_Z ) || (TMath::Abs(fIonMCondition[j] - 25.0f) < 0.3f && fIonZCondition[j] == al_Z )) ){ //26si14+ 25al13+ and 202 >= run >= 196
         //if((fRunNumber[j] < 203 && fRunNumber[j] > 195)){ // 202 >= run >= 196
         //========================================================================
            std::cout << "\tRUN : " << fRunNumber[j] << ", ch : " << lowgain[j] << ", ppac con : " << fPPACCondition[j] << ", window con : " << fWindowCondition[j] << ", Torr : " << fPressure[j] << ", Ion : " << fIonZCondition[j] << " :: energy : " << ene_ref[j] << std::endl;
         }
      }
      std::cout << std::endl;
      gROOT->ProcessLine(Form("artcanvas->Print(\"figure/beam/energy/srim_lowgain%d.png\")", i));
   }

   Double_t chi2 = gr->Chisquare(f);

   return chi2;
}

Double_t TBeamEnergyCalculationSrim::Brho2Energy(Double_t brho, Double_t m, Int_t z)
{
   Double_t mass = m * 931.478;
   //Float_t brhoqc = brho * z * 1.602176634e-19f * 299792458.0f * 6.242e+12;
   Double_t brhoqc = brho * z * 299.8160602;
   return TMath::Sqrt(mass * mass + brhoqc * brhoqc) - mass;
}

void TBeamEnergyCalculationSrim::SrimInit()
{
//   SetElossFuncion(si14mylar,     "prm/srim/26Si14+_in_Mylar.txt");
//   SetElossFuncion(si14he50torr,  "prm/srim/26Si14+_in_He50torr.txt");
//   SetElossFuncion(si14he100torr, "prm/srim/26Si14+_in_He100torr.txt");
//   SetElossFuncion(si14he150torr, "prm/srim/26Si14+_in_He150torr.txt");
//   SetElossFuncion(si14al,        "prm/srim/26Si14+_in_Al.txt");
//
//   SetElossFuncion(si13mylar,     "prm/srim/26Si13+_in_Mylar.txt");
//   SetElossFuncion(si13he50torr,  "prm/srim/26Si13+_in_He50torr.txt");
//   SetElossFuncion(si13he100torr, "prm/srim/26Si13+_in_He100torr.txt");
//   SetElossFuncion(si13he150torr, "prm/srim/26Si13+_in_He150torr.txt");
//   SetElossFuncion(si13al,        "prm/srim/26Si13+_in_Al.txt");
//
//   SetElossFuncion(al13mylar,     "prm/srim/25Al13+_in_Mylar.txt");
//   SetElossFuncion(al13he50torr,  "prm/srim/25Al13+_in_He50torr.txt");
//   SetElossFuncion(al13he100torr, "prm/srim/25Al13+_in_He100torr.txt");
//   SetElossFuncion(al13he150torr, "prm/srim/25Al13+_in_He150torr.txt");
//   SetElossFuncion(al13al,        "prm/srim/25Al13+_in_Al.txt");
//
//   SetElossFuncion(mg12mylar,     "prm/srim/24Mg12+_in_Mylar.txt");
//   SetElossFuncion(mg12he50torr,  "prm/srim/24Mg12+_in_He50torr.txt");
//   SetElossFuncion(mg12he100torr, "prm/srim/24Mg12+_in_He100torr.txt");
//   SetElossFuncion(mg12he150torr, "prm/srim/24Mg12+_in_He150torr.txt");
//   SetElossFuncion(mg12al,        "prm/srim/24Mg12+_in_Al.txt");

   SetElossFuncion(0,  "prm/srim/26Si14+_in_Mylar.txt");
   SetElossFuncion(1,  "prm/srim/26Si14+_in_He50torr.txt");
   SetElossFuncion(2,  "prm/srim/26Si14+_in_He100torr.txt");
   SetElossFuncion(3,  "prm/srim/26Si14+_in_He150torr.txt");
   SetElossFuncion(4,  "prm/srim/26Si14+_in_Al.txt");

   SetElossFuncion(5,  "prm/srim/26Si13+_in_Mylar.txt");
   SetElossFuncion(6,  "prm/srim/26Si13+_in_He50torr.txt");
   SetElossFuncion(7,  "prm/srim/26Si13+_in_He100torr.txt");
   SetElossFuncion(8,  "prm/srim/26Si13+_in_He150torr.txt");
   SetElossFuncion(9,  "prm/srim/26Si13+_in_Al.txt");

   SetElossFuncion(10, "prm/srim/25Al13+_in_Mylar.txt");
   SetElossFuncion(11, "prm/srim/25Al13+_in_He50torr.txt");
   SetElossFuncion(12, "prm/srim/25Al13+_in_He100torr.txt");
   SetElossFuncion(13, "prm/srim/25Al13+_in_He150torr.txt");
   SetElossFuncion(14, "prm/srim/25Al13+_in_Al.txt");

   SetElossFuncion(15, "prm/srim/24Mg12+_in_Mylar.txt");
   SetElossFuncion(16, "prm/srim/24Mg12+_in_He50torr.txt");
   SetElossFuncion(17, "prm/srim/24Mg12+_in_He100torr.txt");
   SetElossFuncion(18, "prm/srim/24Mg12+_in_He150torr.txt");
   SetElossFuncion(19, "prm/srim/24Mg12+_in_Al.txt");
}

//void TBeamEnergyCalculationSrim::SetElossFuncion(TSpline3 *sp, TString name)
void TBeamEnergyCalculationSrim::SetElossFuncion(Int_t ID, TString name)
{
   std::ifstream fin(name.Data());
   if(!fin){
      std::cout << name.Data() << " cannot open" << std::endl;
      return;
   }

   TGraph *gr = new TGraph();

   std::string buf;
   Bool_t data = false;
   Int_t point = 0;
   while(std::getline(fin, buf)){
      if(buf[0]==' ' && buf[1]==' ' && buf[2]=='-'){
         data = true;
         continue; 
      }
      if(!data) continue;
      if(buf[0]=='-' && buf[1]=='-') break;

      std::stringstream ss{buf};
      std::string val;
      Int_t col = 0;
      Double_t energy = 0.0;
      Double_t eloss  = 0.0;
      while(getline(ss, val, ' ')){
         if(val == "") continue;
         if(col == 0) energy = std::stod(val);
         if(col == 1 && val[0]=='k') energy *= 0.001;
         if(col == 2) eloss += std::stod(val);
         if(col == 3) eloss += std::stod(val);
         col++;
         if(col > 4) break;
      }
      gr->SetPoint(point, energy, eloss*1.0e-4); // MeV / 100nm
      point++;
   }

   //sp = new TSpline3("spline", gr);

   if(ID==0) si14mylar     = new TSpline3("si14mylar", gr);
   if(ID==1) si14he50torr  = new TSpline3("si14he50torr", gr);
   if(ID==2) si14he100torr = new TSpline3("si14he100torr", gr);
   if(ID==3) si14he150torr = new TSpline3("si14he150torr", gr);
   if(ID==4) si14al        = new TSpline3("si14al", gr);

   if(ID==5) si13mylar     = new TSpline3("si13mylar", gr);
   if(ID==6) si13he50torr  = new TSpline3("si13he50torr", gr);
   if(ID==7) si13he100torr = new TSpline3("si13he100torr", gr);
   if(ID==8) si13he150torr = new TSpline3("si13he150torr", gr);
   if(ID==9) si13al        = new TSpline3("si13al", gr);

   if(ID==10) al13mylar     = new TSpline3("al13mylar", gr);
   if(ID==11) al13he50torr  = new TSpline3("al13he50torr", gr);
   if(ID==12) al13he100torr = new TSpline3("al13he100torr", gr);
   if(ID==13) al13he150torr = new TSpline3("al13he150torr", gr);
   if(ID==14) al13al        = new TSpline3("al13al", gr);

   if(ID==15) mg12mylar     = new TSpline3("mg12mylar", gr);
   if(ID==16) mg12he50torr  = new TSpline3("mg12he50torr", gr);
   if(ID==17) mg12he100torr = new TSpline3("mg12he100torr", gr);
   if(ID==18) mg12he150torr = new TSpline3("mg12he150torr", gr);
   if(ID==19) mg12al        = new TSpline3("mg12al", gr);


   //gROOT->ProcessLine("zone");
   //sp->Draw();
   //gROOT->ProcessLine(Form("artcanvas->Print(\"figure/test/srim_%s.png\")", name.Data()));
}

Double_t TBeamEnergyCalculationSrim::SrimEnewz(TSpline3 *sp, Double_t energy, Double_t length)
//Double_t TBeamEnergyCalculationSrim::SrimEnewz(Int_t ID, Double_t energy, Double_t length)
{
   Double_t distance = 0.0;
   Double_t energy_remain = energy;
   while(distance < length){
      energy_remain -= sp->Eval(energy_remain);
      //if(ID==0) energy_remain -= si14mylar->Eval(energy_remain);
      //if(ID==1) energy_remain -= si14he50torr->Eval(energy_remain);
      //if(ID==2) energy_remain -= si14he100torr->Eval(energy_remain);
      //if(ID==3) energy_remain -= si14he150torr->Eval(energy_remain);
      //if(ID==4) energy_remain -= si14al->Eval(energy_remain);

      //if(ID==5) energy_remain -= si13mylar->Eval(energy_remain);
      //if(ID==6) energy_remain -= si13he50torr->Eval(energy_remain);
      //if(ID==7) energy_remain -= si13he100torr->Eval(energy_remain);
      //if(ID==8) energy_remain -= si13he150torr->Eval(energy_remain);
      //if(ID==9) energy_remain -= si13al->Eval(energy_remain);

      //if(ID==10) energy_remain -= al13mylar->Eval(energy_remain);
      //if(ID==11) energy_remain -= al13he50torr->Eval(energy_remain);
      //if(ID==12) energy_remain -= al13he100torr->Eval(energy_remain);
      //if(ID==13) energy_remain -= al13he150torr->Eval(energy_remain);
      //if(ID==14) energy_remain -= al13al->Eval(energy_remain);

      //if(ID==15) energy_remain -= mg12mylar->Eval(energy_remain);
      //if(ID==16) energy_remain -= mg12he50torr->Eval(energy_remain);
      //if(ID==17) energy_remain -= mg12he100torr->Eval(energy_remain);
      //if(ID==18) energy_remain -= mg12he150torr->Eval(energy_remain);
      //if(ID==19) energy_remain -= mg12al->Eval(energy_remain);

      distance += 1.0e-4; // mm
      if(energy_remain < 0.0){
         energy_remain = 0.0;
         break;
      }
   }
   return energy_remain;
}