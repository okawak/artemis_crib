// K.Okawa created <okawa@cns.s.u-tokyo.ac.jp>

#include "TBeamContamiCalculation.h"
#include "TEnewzCalculator.h"

#include "constant.h"
#include "TDataObject.h"

#include <TClonesArray.h>
#include <TClass.h>
#include <TCanvas.h>
#include <TGraphErrors.h>
#include <TAxis.h>
#include <TStyle.h>
#include <TF1.h>

using art::TBeamContamiCalculation;

ClassImp(TBeamContamiCalculation)

TBeamContamiCalculation::TBeamContamiCalculation()
{
}

TBeamContamiCalculation::~TBeamContamiCalculation()
{
}

void TBeamContamiCalculation::Init(TEventCollection *col)
{
   std::cout << "==================================================" << std::endl;
	Info("Init", "calculation in Init function (only si26 use)");

   gStyle->SetMarkerStyle(20);
   gStyle->SetMarkerSize(1.5);
   gStyle->SetStatY(0.4);

   Float_t ratio_min = 0.0f; // "ratio" is Ar ratio
   Float_t chi2_min = 1000.0f;
   Float_t tmp = 1.0e+9;
   for(Float_t ratio = 0.5f; ratio<1.0f; ratio+=0.0005f){ // "ratio" is Ar ratio
      Double_t result = ObjFunc(ratio, false);
      if(tmp > result){
         tmp = result;
         ratio_min = ratio;
         chi2_min = result;
      }
   }

   //ObjFunc(1.0f, true);
   ObjFunc(ratio_min, true);
   std::cout << "==================================================" << std::endl;
   std::cout << "RESULT:" << std::endl;
   std::cout << "\tAr ratio: " << ratio_min << " (He ratio: " << 1.0f - ratio_min << ")" << std::endl;

}

void TBeamContamiCalculation::Process()
{
	Info("Process", "no process");
}



Double_t TBeamContamiCalculation::ObjFunc(Float_t ratio, Bool_t debug)
{
   Float_t distance[4] = {562.0f, 562.2f, 562.4f, 562.6f};
   Double_t chi2 = 0.0; 

   for(Int_t i=0; i<4; i++){
      if(i<3) continue;
      Double_t each_ch2 = Getchi2(ratio, distance[i], i, debug);
      chi2 += each_ch2;
   }
   return chi2;
}

Double_t TBeamContamiCalculation::Getchi2(Float_t ratio, Float_t distance, Int_t i, Bool_t debug)
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
   }


   Float_t ene_ref[N] = {};
   for(Int_t j=0; j<N; j++){
      Float_t tmp_z = fIonZCondition[j];
      if(fIonCondition[j] == 3) tmp_z -= 1;
      Float_t ini_energy = Brho2Energy(brho, fIonMCondition[j], tmp_z);
      //std::cout << ini_energy << std::endl;

      // PPAC
      Float_t all_ppac = ppaca_thick + ppacb_thick;
      Float_t af_ppac_e = art::enewz::enewz(fIonZCondition[j], fIonMCondition[j], ini_energy, char_mylar, 0.0f, temparature, all_ppac);

      // Window
      Float_t af_win_e = art::enewz::enewz(fIonZCondition[j], fIonMCondition[j], af_ppac_e, char_mylar, 0.0f, temparature, 0.010f);

      // gas
      Float_t ar_pressure = fPressure[j] * ratio;
      Float_t he_pressure = fPressure[j] * (1.0f - ratio);
      Float_t af_ar_gas_e = art::enewz::enewz(fIonZCondition[j], fIonMCondition[j], af_win_e, char_ar, ar_pressure, temparature, distance);
      Float_t af_he_gas_e = art::enewz::enewz(fIonZCondition[j], fIonMCondition[j], af_ar_gas_e, char_he, he_pressure, temparature, distance);

      // dead
      Float_t af_al_e = art::enewz::enewz(fIonZCondition[j], fIonMCondition[j], af_he_gas_e, char_al, 0.0f, temparature, dead);

      // energy deposit
      Float_t af_si_e = art::enewz::enewz(fIonZCondition[j], fIonMCondition[j], af_al_e, char_si, 0.0f, temparature, 0.02f);

      ene_ref[j] = af_al_e - af_si_e;
   }


   gROOT->ProcessLine("zone");
   Int_t count = 0;
   for(Int_t j=0; j<N; ++j){
      //========================================================================
      if(true){ // all
      //if((TMath::Abs(fIonMCondition[j] - 26.0f) < 0.3f && fIonZCondition[j] == si_Z ) || (TMath::Abs(fIonMCondition[j] - 25.0f) < 0.3f && fIonZCondition[j] == al_Z ) ){ //26si14+ 25al13+
      //========================================================================
         count++;
      }
   }

   //TGraph *gr = new TGraph(N);
   TGraphErrors *gr = new TGraphErrors(count);
   Int_t tmp_count = 0;
   for (Int_t j=0; j<N; ++j){
      //========================================================================
      if(true){ // all
      //if((TMath::Abs(fIonMCondition[j] - 26.0f) < 0.3f && fIonZCondition[j] == si_Z ) || (TMath::Abs(fIonMCondition[j] - 25.0f) < 0.3f && fIonZCondition[j] == al_Z ) ){ //26si14+ 25al13+
      //========================================================================
         gr->SetPoint(tmp_count, lowgain[j], ene_ref[j]);
         gr->SetPointError(tmp_count, lowgain_err[j], 0.0);
         //gr->SetPointError(tmp_count, lowgain_sigma[j], 0.0);
         tmp_count++;
      }
   }
   gr->GetXaxis()->SetLimits(0.,4000.);
   gr->GetYaxis()->SetRangeUser(0.,70.);
   gr->SetTitle(Form("lowgain%d;ch;calculated energy (MeV)",i));
   gr->Draw("ap");

   TF1 *f = new TF1("f","[0]+x*[1]", 0., 4000.);
   f->SetParameters(offset[i], gain[i]);
   f->Draw("same");

   if(debug){
      std::cout << "lowgain" << i << std::endl;
      for(Int_t j=0; j<N; j++){
         //========================================================================
         if(true){ // all
         //if((TMath::Abs(fIonMCondition[j] - 26.0f) < 0.3f && fIonZCondition[j] == si_Z ) || (TMath::Abs(fIonMCondition[j] - 25.0f) < 0.3f && fIonZCondition[j] == al_Z ) ){ //26si14+ 25al13+
         //========================================================================
            std::cout << "\tRUN : " << fRunNumber[j] << ", ch : " << lowgain[j] << ", Ar Torr : " << fPressure[j] * ratio << ", (He Torr : " << fPressure[j] * (1.0f - ratio) << "), Ion : " << fIonZCondition[j] << " :: energy : " << ene_ref[j] << std::endl;
         }
      }
      std::cout << std::endl;
      gROOT->ProcessLine(Form("artcanvas->Print(\"figure/beam/contami/lowgain%d.png\")", i));
   }

   Double_t chi2 = 0.0;
   for(Int_t j=0; j<N; j++){
      //========================================================================
      if(true){ // all
      //if((TMath::Abs(fIonMCondition[j] - 26.0f) < 0.3f && fIonZCondition[j] == si_Z ) || (TMath::Abs(fIonMCondition[j] - 25.0f) < 0.3f && fIonZCondition[j] == al_Z ) ){ //26si14+ 25al13+
      //========================================================================
         chi2 += ( (ene_ref[j] - f->Eval(lowgain[j]))/(lowgain_err[j] * gain[i]) ) * ( (ene_ref[j] - f->Eval(lowgain[j]))/(lowgain_err[j] * gain[i]) );
      }
   }

   return chi2;
}


Float_t TBeamContamiCalculation::Brho2Energy(Float_t brho, Float_t m, Int_t z)
{
   Float_t mass = m * 931.478f;
   //Float_t brhoqc = brho * z * 1.602176634e-19f * 299792458.0f * 6.242e+12;
   Float_t brhoqc = brho * z * 299.8160602f;
   return TMath::Sqrt(mass * mass + brhoqc * brhoqc) - mass;
}