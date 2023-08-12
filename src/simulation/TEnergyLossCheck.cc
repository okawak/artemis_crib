// K.Okawa created <okawa@cns.s.u-tokyo.ac.jp>

#include "TEnergyLossCheck.h"
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

using art::TEnergyLossCheck;

ClassImp(TEnergyLossCheck)

TEnergyLossCheck::TEnergyLossCheck()
{
}

TEnergyLossCheck::~TEnergyLossCheck()
{
}

void TEnergyLossCheck::Init(TEventCollection *col)
{
   std::cout << "==================================================" << std::endl;
	Info("Init", "calculation in Init function (only si26 use)");

   gStyle->SetOptStat(0);
   gStyle->SetOptFit(0);
   gStyle->SetMarkerStyle(20);
   //gStyle->SetMarkerSize(1.5);

   TGraphErrors *g1 = new TGraphErrors(N);
   TGraphErrors *g2 = new TGraphErrors(N);
   g1->SetMarkerSize(1.5);
   g2->SetMarkerSize(1.5);
   for(Int_t j=0; j<N; ++j){
      g1->SetPoint(j, he_pressure[j], he_adc[j]);
      //g1->SetPointError(j, 0.0, he_adc_err[j]);
      g1->SetPointError(j, 0.0, he_adc_sigma[j]);

      g2->SetPoint(j, ar_pressure[j], ar_adc[j]);
      //g2->SetPointError(j, 0.0, ar_adc_err[j]);
      g2->SetPointError(j, 0.0, ar_adc_sigma[j]);
   }

   TGraph *ghe = new TGraph();
   TGraph *gar = new TGraph();
   TGraph *gtest = new TGraph();
   ghe->SetMarkerSize(0.3);
   gar->SetMarkerSize(0.3);
   gtest->SetMarkerSize(0.3);
   Int_t count = 0;
   Bool_t print_he = true;
   Bool_t print_ar = true;
   for(Float_t pressure=0.0f; pressure<250.0f; pressure+=0.1f){
      Float_t he_ene = ini_energy;
      Float_t ar_ene = ini_energy;

      Float_t he_af_gas_ene = art::enewz::enewz(si_Z, si_M, he_ene, char_he, pressure, temparature, distance);
      Float_t ar_af_gas_ene = art::enewz::enewz(si_Z, si_M, ar_ene, char_ar, pressure/factor, temparature, distance);

      Float_t he_af_al_ene = art::enewz::enewz(si_Z, si_M, he_af_gas_ene, char_al, 0.0f, temparature, dead);
      Float_t ar_af_al_ene = art::enewz::enewz(si_Z, si_M, ar_af_gas_ene, char_al, 0.0f, temparature, dead);

      Float_t he_af_si_ene = art::enewz::enewz(si_Z, si_M, he_af_al_ene, char_si, 0.0f, temparature, 0.02f);
      Float_t ar_af_si_ene = art::enewz::enewz(si_Z, si_M, ar_af_al_ene, char_si, 0.0f, temparature, 0.02f);

      Float_t he_adc_cal = (he_af_al_ene - he_af_si_ene - he_offset)/he_gain;
      Float_t ar_adc_cal = (ar_af_al_ene - ar_af_si_ene - ar_offset)/ar_gain;

      ghe->SetPoint(count, pressure,he_adc_cal);
      gar->SetPoint(count, pressure,ar_adc_cal);
      if(print_he && he_adc_cal < 0.0f){
         std::cout << "offset of he = " << pressure << " torr" << std::endl;
         print_he = false;
      }
      if(print_ar && ar_adc_cal < 0.0f){
         std::cout << "offset of ar = " << pressure << " torr" << std::endl;
         print_ar = false;
      }
      gtest->SetPoint(count, pressure*4.74,ar_adc_cal);

      count++;
   }

   gROOT->ProcessLine("zone");

   g1->GetXaxis()->SetLimits(0.,250.);
   g1->GetYaxis()->SetRangeUser(0.,2700.);
   g1->SetTitle(Form("thickness check;pressure [Torr];ADC channel [ch]"));

   g1->SetMarkerColor(kBlue);
   g2->SetMarkerColor(kRed);
   ghe->SetMarkerColor(kBlue);
   gar->SetMarkerColor(kRed);
   gtest->SetMarkerColor(kBlack);

   g1->Draw("ap");
   g2->Draw("p");
   ghe->Draw("p");
   gar->Draw("p");
   //gtest->Draw("p");

   gROOT->ProcessLine("artcanvas->Print(\"figure/beam/contami/energyloss.png\")");


   TGraph *ghe2 = new TGraph();
   TGraph *gar2 = new TGraph();
   ghe2->SetMarkerSize(0.3);
   gar2->SetMarkerSize(0.3);
   Int_t count2 = 0;
   Bool_t print_he2 = true;
   Bool_t print_ar2 = true;
   for(Float_t dis=0.0f; dis<600.0f; dis+=0.1f){
      Float_t he_ene = ini_energy;
      Float_t ar_ene = ini_energy;

      Float_t he_af_gas_ene = art::enewz::enewz(si_Z, si_M, he_ene, char_he, 250.0f, temparature, dis);
      Float_t ar_af_gas_ene = art::enewz::enewz(si_Z, si_M, ar_ene, char_ar, 55.0f/factor, temparature, dis);

      ghe2->SetPoint(count2, dis, he_af_gas_ene);
      gar2->SetPoint(count2, dis, ar_af_gas_ene);
      //if(print_he && he_adc_cal < 0.0f){
      //   std::cout << "offset of he = " << pressure << " torr" << std::endl;
      //   print_he = false;
      //}
      //if(print_ar && ar_adc_cal < 0.0f){
      //   std::cout << "offset of ar = " << pressure << " torr" << std::endl;
      //   print_ar = false;
      //}

      count2++;
   }

   gROOT->ProcessLine("zone");

   ghe2->GetXaxis()->SetLimits(0.,600.);
   ghe2->GetYaxis()->SetRangeUser(0.,60.);
   ghe2->SetTitle(Form("thickness check;distance [mm];energy [MeV]"));

   ghe2->SetMarkerColor(kBlue);
   gar2->SetMarkerColor(kRed);

   ghe2->Draw("ap");
   gar2->Draw("p");

   gROOT->ProcessLine("artcanvas->Print(\"figure/beam/contami/energyloss2.png\")");



}

void TEnergyLossCheck::Process()
{
	Info("Process", "no process");
}


