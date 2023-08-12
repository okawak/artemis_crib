// K.Okawa created <okawa@cns.s.u-tokyo.ac.jp>

#include "TEffThicknessCalculation.h"
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
#include <TMath.h>
#include <TSpline.h>

using art::TEffThicknessCalculation;

ClassImp(TEffThicknessCalculation)

TEffThicknessCalculation::TEffThicknessCalculation()
{
   RegisterProcessorParameter("InitialEnergy","initial energy",
			                  fEnergy, 0.0f);
   RegisterProcessorParameter("InputZ","Z of the initial particle",
			                  fZ, 0);
   RegisterProcessorParameter("InputM","M of the initial particle (amu)",
			                  fM, 0.0f);
   RegisterProcessorParameter("InputTargetM","M of the initial particle (amu)",
			                  fTargetM, 0.0f);
   RegisterProcessorParameter("Pressure","Pressure Torr (if solid target, set as 0)",
			                  fPressure, 0.0f);
   RegisterProcessorParameter("Temperature","Temperature K (if solid target, set as 0)",
			                  fTemperature, 0.0f);
   RegisterProcessorParameter("DeltaE","energy range",
			                  fEnergyRange, 0.0f);
   RegisterProcessorParameter("Material","target material",
			                  fMaterial, TString("material"));
   RegisterProcessorParameter("MaterialWeight","g/mol of the material",
			                  fMaterialWeight, 0.0f);
}

TEffThicknessCalculation::~TEffThicknessCalculation()
{
}

void TEffThicknessCalculation::Init(TEventCollection *col)
{
   gStyle->SetOptStat(0);
   gStyle->SetOptFit(0);
   gStyle->SetMarkerStyle(20);
   gStyle->SetMarkerSize(1.2);

   for(Int_t i=0; i<34; i++){
      if(i<(Int_t)fMaterial.Length()) char_material[i] = fMaterial.Data()[i];
      else char_material[i] = '\0';
   }

   std::cout << "enewz test" << std::endl;
   Float_t density = art::enewz::gas_density(fPressure, fTemperature, fMaterialWeight);
   std::cout << density << std::endl;

   Int_t count = 0;
   //TGraph *g_raw = new TGraph();
   for(Float_t d=0.0f; d<100.0f; d+=0.0001f){
      Float_t energy = art::enewz::enewz(fZ, fM, fEnergy, char_material, fPressure, fTemperature, d*10.0);
      //g_raw->SetPoint(count, energy, energy - art::enewz::enewz(fZ, fM, energy, char_material, fPressure, fTemperature, 1.0));
      if(energy < 0.001f) break;
      count++;
   }
   //gROOT->ProcessLine("zone");
   //g_raw->Draw("ap");
   //gROOT->ProcessLine("artcanvas->Print(\"figure/enewz/energy_loss.png\")");

   const Int_t N = (const Int_t)count;
   Float_t energyL[N] = {0.0f};
   Float_t thickness[N] = {0.0f};
   Int_t itr = 0;
   for(Float_t d=0.0f; d<100.0f; d+=0.0001f){
      Float_t energy = art::enewz::enewz(fZ, fM, fEnergy, char_material, fPressure, fTemperature, d*10.0);
      energyL[itr] = energy;
      thickness[itr] = d * density * 1000.0f;
      if(energy < 0.001f) break;
      itr++;
   }

   //for(Int_t i=0; i<N; i++){
   //   //std::cout << i << " " << get_Ecm(energyL[i]) << " " << thickness[i] << std::endl;
   //}


   TGraph *g = new TGraph();
   Int_t tmp = 0;
   for(Float_t energy=1.51f; energy < 7.0f; energy+=0.2f){
      //========================================================
      //Int_t num_low = -1;
      //Int_t num_center = -1;
      //Int_t num_high = -1;
      //for(Int_t i=0; i<N; i++){
      //   if(num_high == -1 && get_Ecm(energyL[i]) < energy - fEnergyRange/2.0f) num_high = i;
      //   if(num_center == -1 && get_Ecm(energyL[i]) < energy) num_center = i;
      //   if(num_low == -1 && get_Ecm(energyL[i]) < energy + fEnergyRange/2.0f) num_low = i;

      //   if(num_low != -1 && num_center != -1 && num_high != -1) break;
      //}
      //g->SetPoint(tmp, get_Ecm(energyL[num_center]), thickness[num_high] - thickness[num_low]);
      //========================================================
      Float_t low  = art::enewz::rangez(fZ, fM, get_Elab(energy - fEnergyRange/2.0f), char_material);
      Float_t high = art::enewz::rangez(fZ, fM, get_Elab(energy + fEnergyRange/2.0f), char_material);
      g->SetPoint(tmp, energy, high-low);
      //========================================================
      ////std::cout << tmp << " " << energy - fEnergyRange/2.0f << " " << energy + fEnergyRange/2.0 << " " << get_Ecm(energyL[num_center]) << " " << thickness[num_high] - thickness[num_low] << std::endl;
      tmp++;
   }

   gROOT->ProcessLine("zone");
   g->SetTitle("enewz;Ecm [MeV];effective thickness [g/cm2]");
   g->Draw("ap");

   //TSpline3 *spline = new TSpline3("spline", g);
   //spline->Draw("same");

   //TF1 *f1 = new TF1("f1","((x > 4.0) ? pol1(0) : pol2(2))",2.5, 10.0);
   //f1->SetParameters(0.1,0.1,0.00001,0.1,0.1);
   //TF1 *f1 = new TF1("f1","pol1",4.0, 8.0);
   //g->Fit(f1,"r");
   //f1->Draw("same");
   //f1->Draw();

   gROOT->ProcessLine("artcanvas->Print(\"figure/enewz/effective_thickness.png\")");

}

void TEffThicknessCalculation::Process()
{
	Info("Process", "no process");
}
