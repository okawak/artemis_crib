// K.Okawa created <okawa@cns.s.u-tokyo.ac.jp>

#include "TSimYieldProcessor.h"

#include "constant.h"
#include "TDataObject.h"
#include "TTimingChargeData.h"

#include "TEnewzCalculator.h"

#include <TClonesArray.h>
#include <TSystem.h>
#include <TClass.h>
#include <TPad.h>
#include <TGraph.h>
#include <TGraph2D.h>
#include <TRandom.h>
#include <TStyle.h>
#include <TSpline.h>
#include <TAxis.h>
#include <TVector3.h>
#include <TF1.h>
#include <TH1.h>
#include <TMath.h>

using art::TSimYieldProcessor;

ClassImp(TSimYieldProcessor)

TSimYieldProcessor::TSimYieldProcessor()
	 : fOutData(NULL)
{
	RegisterProcessorParameter("Inputtxt", "cross section info",
	                        fInputTxtName, TString("filename"));
   RegisterOutputCollection("OutputCollection", "simulation result collection",
	                        fOutputColName, TString("result"));

   RegisterProcessorParameter("SolidAngle","solid angle ratio",
			                  fSolidAngle, 0.0);
   RegisterProcessorParameter("EventNumber","event number",
			                  fEventNumber, 0L);
   
}

TSimYieldProcessor::~TSimYieldProcessor()
{
	delete fOutData;
	fOutData = NULL;
}

void TSimYieldProcessor::Init(TEventCollection *col)
{
	Info("Init", "%s => %s", fInputTxtName.Data(), fOutputColName.Data());

   FileStat_t info;
   if(gSystem->GetPathInfo(fInputTxtName.Data(), info) != 0){
      SetStateError(TString::Format("input not found: %s",fInputTxtName.Data()));
      return;
   }

   TGraph *g = new TGraph(fInputTxtName.Data(), "%lg %lg");
   cs = new TSpline3("nonsmoker", g);

   //gROOT->ProcessLine("zone");
   //gPad->SetLogx(1);
   //gPad->SetLogy(1);
   //g->SetMarkerStyle(20);
   //g->SetMarkerColor(kRed);
   //g->SetMarkerSize(1);
   //g->GetXaxis()->SetLimits(0.0, 25.0);
   //g->Draw("ap");
   //cs->SetLineWidth(2);
   //cs->Draw("same");
   //gROOT->ProcessLine("artcanvas->Print(\"c1.png\")");

   //=========================================================
   gRandom->SetSeed(time(NULL));
   TGraph *yield = new TGraph();
   Long_t total_event = 3100000000;
   Int_t count = 0;
   for(Float_t energy=1.0f; energy<9.0f; energy+=0.01f){
      Float_t high = art::enewz::rangez(14, 25.992333818f, get_Elab(energy + 0.1f), char_he);
      Float_t low  = art::enewz::rangez(14, 25.992333818f, get_Elab(energy - 0.1f), char_he);
      Double_t eff_thickness = (Double_t)(high - low) * 1.0e-3;

      Float_t tmp_distance = 0.0f;
      while(get_Elab(energy) < art::enewz::enewz(14, 25.992333818f, 55.5f, char_he, 250.0f, 300.0f, tmp_distance)){
         tmp_distance += 0.1f;
      }

      Double_t distance1 = (Double_t)tmp_distance;

//      if(tmp_distance < 0.01f){
//         while(get_Elab(energy) > art::enewz::eoldz(14, 25.992333818f, 55.5f, char_he, 250.0f, 300.0f, tmp_distance)){
//            tmp_distance += 0.1f;
//         }
//         distance1 = -tmp_distance;
//      }

      //std::cout << "\tdistance " << distance1 << std::endl;

      if(tmp_distance < 0.01f){
         //std::cout << "energy " << energy << ", solid angle " << 0.0 << std::endl;

         yield->SetPoint(count, energy, 0.0);
         //yield->SetPoint(count, energy+9.343, 0.0);

         //std::cout << energy << " " << 0.0 << std::endl;
         count++;
         continue;
      }


      Long_t num = 0;
      for(Long_t i=0; i<fEventNumber; i++){
         Double_t random_u = gRandom->Uniform(0.0,1.0);
         Double_t random_v = gRandom->Uniform(0.0,1.0);
         Double_t z = -2.0*random_u + 1;
         Double_t x = TMath::Sqrt(1.0-z*z)*TMath::Cos(2.0*TMath::Pi()*random_v);
         Double_t y = TMath::Sqrt(1.0-z*z)*TMath::Sin(2.0*TMath::Pi()*random_v);
         for(Int_t j=0; j<5; j++){
            TVector3 proton_dir(x, y, z);
            TVector3 proton_pos(0.0, 0.0, distance1);

            Double_t center = 0.0;
            Double_t angle = 0.0;
            Double_t distance = 0.0;
            if(j == 0){
               center = 322.0;
               angle  = -4.0 * (TMath::Pi()/180.0);
               distance = 252.5;
            }else if(j == 1){
               center = 322.0;
               angle  = 27.0 * (TMath::Pi()/180.0);
               distance = 161.5;
            }else if(j == 2){
               center = 322.0;
               angle  = -48.0 * (TMath::Pi()/180.0);
               distance = 122.0;
            }else if(j == 3){
               center = 272.0;
               angle  = 62.0 * (TMath::Pi()/180.0);
               distance = 117.5;
            }else if(j == 4){
               center = 222.0;
               angle  = -73.0 * (TMath::Pi()/180.0);
               distance = 115.5;
            }

            TVector3 offset(0.0, 0.0, center);
            proton_pos -= offset;

            proton_pos.RotateY(-angle);
            proton_dir.RotateY(-angle);

            if(proton_dir.Z() < 0.0) continue;

            Double_t tmp_factor = (distance-proton_pos.Z())/(proton_dir.Z());
            TVector3 det_position(proton_pos.X() + (proton_dir.X())*tmp_factor, proton_pos.Y() + (proton_dir.Y())*tmp_factor, proton_pos.Z() + (proton_dir.Z())*tmp_factor);

            if(TMath::Abs(det_position.X()) > 25.0 || TMath::Abs(det_position.Y()) > 25.0) continue;

            num++;
         }
      }

      Double_t solid_ag = ((Double_t)num/(Double_t)fEventNumber);
      std::cout << "" << energy << " " << solid_ag << " " << eff_thickness*(Na/he_A) << std::endl;

      yield->SetPoint(count, energy, eff_thickness*(Na/he_A)*total_event*cs->Eval(energy)*solid_ag*1.0e-24);
      //yield->SetPoint(count, energy+9.343, eff_thickness*(Na/he_A)*fEventNumber*cs->Eval(energy)*fSolidAngle*1.0e-24);

      //std::cout << energy << " " << eff_thickness*(Na/he_A)*total_event*cs->Eval(energy)*solid_ag*1.0e-24 << std::endl;
      count++;
   }

   gROOT->ProcessLine("zone");
   //gPad->SetLogx(1);
   //gPad->SetLogy(1);
   yield->SetMarkerStyle(20);
   yield->SetMarkerColor(kRed);
   yield->SetMarkerSize(1);
   yield->SetLineColor(kRed);
   yield->SetLineWidth(2);
   //yield->GetXaxis()->SetLimits(0.0, 25.0);
   yield->Draw("al");
   gROOT->ProcessLine("artcanvas->Print(\"figure/simulation/3_1e9_0_2mev_yield.png\")");

   //TSpline3 *yd = new TSpline3("yd", yield);
   //gROOT->ProcessLine("zone");
   ////gPad->SetLogx(1);
   ////gPad->SetLogy(1);
   //yd->SetMarkerStyle(20);
   //yd->SetMarkerColor(kRed);
   //yd->SetMarkerSize(1);
   //yd->SetLineColor(kRed);
   //yd->SetLineWidth(3);
   ////yield->GetXaxis()->SetLimits(0.0, 25.0);
   //yd->Draw("al");
   //gROOT->ProcessLine("artcanvas->Print(\"c1.png\")");


   //=========================================================

   fOutData = new TClonesArray("art::TTimingChargeData");
   fOutData->SetName(fOutputColName);
   col->Add(fOutputColName,fOutData,fOutputIsTransparent);

}

void TSimYieldProcessor::Process()
{
	fOutData->Clear("C");
}
