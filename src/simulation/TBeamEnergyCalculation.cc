// K.Okawa created <okawa@cns.s.u-tokyo.ac.jp>

#include "TBeamEnergyCalculation.h"
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

using art::TBeamEnergyCalculation;

ClassImp(TBeamEnergyCalculation)

TBeamEnergyCalculation::TBeamEnergyCalculation()
{
}

TBeamEnergyCalculation::~TBeamEnergyCalculation()
{
}

void TBeamEnergyCalculation::Init(TEventCollection *col)
{
   std::cout << "==================================================" << std::endl;
	Info("Init", "calculation in Init function (only si26 use)");
   //Info("Init", "enewz test");
   //std::cout << "\tbefore: " << ini_energy << std::endl;
   //std::cout << "\tafter : " << art::enewz::enewz(fIonZCondition[0],fIonMCondition[0],ini_energy,char_mylar,0.0f,300.0f,0.020f) << std::endl;;
   //std::cout << std::endl;

   gStyle->SetMarkerStyle(20);
   gStyle->SetMarkerSize(0.8);
   gStyle->SetStatY(0.4);

   Float_t ppaca_min = 0.0f;
   Float_t ppacb_min = 0.0f;
   Float_t chi2_min = 1000.0f;
   Float_t tmp = 1.0e+9;

   for(Float_t ppaca = 0.0085f; ppaca<0.0100f; ppaca+=0.00001f){
      for(Float_t ppacb = 0.0090f; ppacb<0.0135f; ppacb+=0.00001f){
         //std::cout << "PPACa: 0.009 < " << ppaca << " < 0.011, PPACb: 0.009 < " << ppacb << " < 0.011" << std::endl;
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
   Float_t ppacs_low = 100.0f;
   Float_t ppacs_high = 0.0f;

   for(Float_t ppaca = 0.0085f; ppaca<0.0100f; ppaca+=0.00001f){
      for(Float_t ppacb = 0.0090f; ppacb<0.0135f; ppacb+=0.00001f){
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
   gROOT->ProcessLine(Form("artcanvas->Print(\"figure/beam/energy/chi2_dist.png\")"));

   Float_t ppac_tmp = ppaca_min + ppacb_min + 0.013f;
   Float_t ini_energy = Brho2Energy(brho, si_M, si_Z);
   Float_t ene = art::enewz::enewz(14, 25.992333818f, ini_energy, char_mylar, 0.0f, 300.0f, ppac_tmp);
   Float_t ene_low = art::enewz::enewz(14, 25.992333818f, ini_energy, char_mylar, 0.0f, 300.0f, ppacs_low+0.013f);
   Float_t ene_high = art::enewz::enewz(14, 25.992333818f, ini_energy, char_mylar, 0.0f, 300.0f, ppacs_high+0.013f);
   std::cout << "==================================================" << std::endl;

   ObjFunc(ppaca_min, ppacb_min, true);
   std::cout << "RESULT:" << std::endl;
   std::cout << "\tppaca thickness: " << ppaca_min << ", ppacb thickness: " << ppacb_min << std::endl;
   std::cout << "\ttotal mylar: " << ppac_tmp << std::endl;
   std::cout << "\tenergy after window: " << ene << std::endl;
   std::cout << "\t                      - " << ene - ene_high << std::endl;
   std::cout << "\t                      + " << ene_low - ene << std::endl;
}

void TBeamEnergyCalculation::Process()
{
	Info("Process", "no process");
}



Double_t TBeamEnergyCalculation::ObjFunc(Float_t ppaca, Float_t ppacb, Bool_t debug)
{
   Float_t distance[4] = {562.0f, 562.2f, 562.4f, 562.6f};
   Double_t chi2 = 0.0; 

   for(Int_t i=0; i<4; i++){
      Double_t each_ch2 = Getchi2(ppaca, ppacb, distance[i], i, debug);
      //std::cout << "chi2 in lowgain" << i << " : " << each_ch2 << std::endl;
      chi2 += each_ch2;
   }
   return chi2;
}

Double_t TBeamEnergyCalculation::Getchi2(Float_t ppaca, Float_t ppacb, Float_t distance, Int_t i, Bool_t debug)
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


   Float_t ene_ref[N] = {};
   for(Int_t j=0; j<N; j++){
      Float_t tmp_z = fIonZCondition[j];
      if(fIonCondition[j] == 3) tmp_z -= 1;
      Float_t ini_energy = Brho2Energy(brho, fIonMCondition[j], tmp_z);
      //std::cout << ini_energy << std::endl;

      // PPAC
      Float_t af_ppac_e = 0.0f;
      Float_t all_ppac = ppaca + ppacb;
      if(fPPACCondition[j] == 0) af_ppac_e = ini_energy;
      if(fPPACCondition[j] == 1) af_ppac_e = art::enewz::enewz(fIonZCondition[j], fIonMCondition[j], ini_energy, char_mylar, 0.0f, temparature, ppaca);
      if(fPPACCondition[j] == 2) af_ppac_e = art::enewz::enewz(fIonZCondition[j], fIonMCondition[j], ini_energy, char_mylar, 0.0f, temparature, ppacb);
      if(fPPACCondition[j] == 3) af_ppac_e = art::enewz::enewz(fIonZCondition[j], fIonMCondition[j], ini_energy, char_mylar, 0.0f, temparature, all_ppac);

      //std::cout << "lowgain" << i << " : " << af_ppac_e << std::endl; 

      // Window
      Float_t af_win_e = 0.0f;
      if(fWindowCondition[j] == 0) af_win_e = af_ppac_e;
      if(fWindowCondition[j] == 1) af_win_e = art::enewz::enewz(fIonZCondition[j], fIonMCondition[j], af_ppac_e, char_mylar, 0.0f, temparature, 0.023f);
      if(fWindowCondition[j] == 2) af_win_e = art::enewz::enewz(fIonZCondition[j], fIonMCondition[j], af_ppac_e, char_mylar, 0.0f, temparature, 0.013f);

      // gas
      Float_t af_gas_e = 0.0f;
      if(fGasCondition[j] == 0) af_gas_e = art::enewz::enewz(fIonZCondition[j], fIonMCondition[j], af_win_e, char_he, fPressure[j], temparature, distance);
      if(fGasCondition[j] == 1) af_gas_e = art::enewz::enewz(fIonZCondition[j], fIonMCondition[j], af_win_e, char_ar, fPressure[j], temparature, distance);

      // dead
      Float_t af_al_e = 0.0f;
      af_al_e = art::enewz::enewz(fIonZCondition[j], fIonMCondition[j], af_gas_e, char_al, 0.0f, temparature, dead);

      // energy deposit
      Float_t af_si_e = 0.0f;
      af_si_e = art::enewz::enewz(fIonZCondition[j], fIonMCondition[j], af_al_e, char_si, 0.0f, temparature, 0.02f);

      ene_ref[j] = af_al_e - af_si_e;

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
      gROOT->ProcessLine(Form("artcanvas->Print(\"figure/beam/energy/lowgain%d.png\")", i));
   }

   Double_t chi2 = gr->Chisquare(f);

   return chi2;
}

Float_t TBeamEnergyCalculation::Brho2Energy(Float_t brho, Float_t m, Int_t z)
{
   Float_t mass = m * 931.478f;
   //Float_t brhoqc = brho * z * 1.602176634e-19f * 299792458.0f * 6.242e+12;
   Float_t brhoqc = brho * z * 299.8160602f;
   return TMath::Sqrt(mass * mass + brhoqc * brhoqc) - mass;
}