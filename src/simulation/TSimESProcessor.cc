// K.Okawa created <okawa@cns.s.u-tokyo.ac.jp>

#include "TSimESProcessor.h"

#include "constant.h"
#include "TDataObject.h"
#include "TSimBeamData.h"
#include "TSimResultData.h"

#include "TEnewzCalculator.h"

#include <TVector3.h>
#include <TClonesArray.h>
#include <TClass.h>
#include <TGraph.h>
#include <TRandom.h>
#include <TStyle.h>
#include <TAxis.h>
#include <TF1.h>
#include <TH1.h>
#include <TMath.h>

using art::TSimESProcessor;

ClassImp(TSimESProcessor)

TSimESProcessor::TSimESProcessor()
	 : fInData(NULL), fOutData(NULL)
{
	RegisterInputCollection("InputCollection", "beam info",
	                        fInputColName, TString("beam"));
   RegisterOutputCollection("OutputCollection", "simulation result collection",
	                        fOutputColName, TString("result"));

   //RegisterProcessorParameter("RotationZpos","origin z position of the rotation",
			//                  fRotZpos, 0.0);
   
}

TSimESProcessor::~TSimESProcessor()
{
	delete fOutData;
	fOutData = NULL;
}

void TSimESProcessor::Init(TEventCollection *col)
{
	Info("Init", "%s => %s", fInputColName.Data(), fOutputColName.Data());
	fInData = reinterpret_cast<TClonesArray**>(col->GetObjectRef(fInputColName.Data()));
   if (!fInData) {
      SetStateError(TString::Format("input not found: %s",fInputColName.Data()));
      return;
   }

   const TClass *const cl = (*fInData)->GetClass();
   fInputHasData = cl->InheritsFrom(art::TSimBeamData::Class());
   if(!fInputHasData){
      SetStateError("contents of input array must inherit from art::TSimBeamData");
      return;
   }

   fOutData = new TClonesArray("art::TSimResultData");
   fOutData->SetName(fOutputColName);
   col->Add(fOutputColName,fOutData,fOutputIsTransparent);

   //====================ENEWZ CHECK===============================
   gStyle->SetMarkerStyle(20);
   gStyle->SetMarkerSize(0.5);
   //gStyle->SetStatY(0.4);
   gRandom->SetSeed(0);

   gROOT->ProcessLine("zone");
   const Int_t N = 100;
   Int_t j = 0;
   TGraph *g = new TGraph(N);
   while(j<N){
      Float_t thickness = 0.0001f * (Float_t)j;
      Float_t z = 0.0100f - thickness;
      Float_t bef_energy = art::enewz::eoldz(14, 25.992333818f, fIniEnergy, char_mylar, 0.0f, 300.0f, thickness);
      Float_t ecm = bef_energy * (1.0/27.0);
      //g->SetPoint(j, z, ecm); // Ecm
      g->SetPoint(j, z, 1.0/(ecm*ecm)); // 1/Ecm^2
      j++;
   }
   g->GetXaxis()->SetLimits(-0.001, 0.011);
   g->GetYaxis()->SetRangeUser(0.,0.3);
   g->SetTitle(Form("energy loss check;mylar thickness;calculated energy (MeV)"));
   g->Draw("ap");

   TF1 *f = new TF1("f", "pol2");
   g->Fit(f,"q");
   gROOT->ProcessLine(Form("artcanvas->Print(\"figure/beam/ES/enewz_check.png\")"));

   p0 = f->GetParameter(0);
   p1 = f->GetParameter(1);
   p2 = f->GetParameter(2);

   norm = 1.0/(p0 * 0.01 + p1*0.01*0.01*1.0/2.0 + p2*0.01*0.01*0.01/3.0);

   TH1F *h1 = new TH1F("h1", "random test", 100,-0.001,0.011);
   for(Int_t i=0; i<100000; i++){
      h1->Fill(get_ReactionPos());
   }
   h1->Draw();
   gROOT->ProcessLine(Form("artcanvas->Print(\"figure/beam/ES/random_check.png\")"));
//
//   //==================== MAIN ======================================
//   TH1F *h_tel1 = new TH1F("h_tel1", "tel1 window elastic scattering", 1000,0.0,20.0);
//   for(Int_t i=0; i<10000; i++){
//      Double_t thickness = get_ReactionPos();
//      Double_t thickness_from_window = 0.01f - thickness;
//      Double_t ave_angle = 1.7  * TMath::Pi()/180.0; // tel1
//
//      Float_t ini_energy = art::enewz::eoldz(14, 25.992333818f, fIniEnergy, char_mylar, 0.0f, 300.0f, (Float_t)thickness_from_window);
//      Float_t e2 = (ini_energy * 4.0 * 25.99233 * 1.007825 * TMath::Cos(ave_angle) * TMath::Cos(ave_angle))/((25.992333 + 1.007825)*(25.992333 + 1.007825));
//
//      Float_t af_my = art::enewz::enewz(1, 1.007825031898f, e2, char_mylar, 0.0f, 300.0f, (Float_t)thickness_from_window);
//      Float_t af_gas = art::enewz::enewz(1, 1.007825031898f, af_my, char_he, 250.0f, 300.0f, 540.0f);
//
//      h_tel1->Fill(gRandom->Gaus(af_gas, 1.0));
//   }
//   h_tel1->Draw();
//   gROOT->ProcessLine(Form("artcanvas->Print(\"figure/beam/ES/tel1_rough.png\")"));
//   //==================== END ======================================
//   //==================== MAIN ======================================
//   TH1F *h_tel2 = new TH1F("h_tel2", "tel2 window elastic scattering", 1000,0.0,20.0);
//   for(Int_t i=0; i<10000; i++){
//      Double_t thickness = get_ReactionPos();
//      Double_t thickness_from_window = 0.01f - thickness;
//      Double_t ave_angle = 8.5  * TMath::Pi()/180.0; // tel2
//
//      Float_t ini_energy = art::enewz::eoldz(14, 25.992333818f, fIniEnergy, char_mylar, 0.0f, 300.0f, (Float_t)thickness_from_window);
//      Float_t e2 = (ini_energy * 4.0 * 25.99233 * 1.007825 * TMath::Cos(ave_angle) * TMath::Cos(ave_angle))/((25.992333 + 1.007825)*(25.992333 + 1.007825));
//
//      Float_t af_my = art::enewz::enewz(1, 1.007825031898f, e2, char_mylar, 0.0f, 300.0f, (Float_t)thickness_from_window);
//      Float_t af_gas = art::enewz::enewz(1, 1.007825031898f, af_my, char_he, 250.0f, 300.0f, 540.0f);
//
//      h_tel2->Fill(gRandom->Gaus(af_gas, 1.0));
//   }
//   h_tel2->Draw();
//   gROOT->ProcessLine(Form("artcanvas->Print(\"figure/beam/ES/tel2_rough.png\")"));
//   //==================== END ======================================
//   //==================== MAIN ======================================
//   TH1F *h_tel3 = new TH1F("h_tel3", "tel3 window elastic scattering", 1000,0.0,20.0);
//   for(Int_t i=0; i<10000; i++){
//      Double_t thickness = get_ReactionPos();
//      Double_t thickness_from_window = 0.01f - thickness;
//      Double_t ave_angle = 11.7 * TMath::Pi()/180.0; // tel3
//
//      Float_t ini_energy = art::enewz::eoldz(14, 25.992333818f, fIniEnergy, char_mylar, 0.0f, 300.0f, (Float_t)thickness_from_window);
//      Float_t e2 = (ini_energy * 4.0 * 25.99233 * 1.007825 * TMath::Cos(ave_angle) * TMath::Cos(ave_angle))/((25.992333 + 1.007825)*(25.992333 + 1.007825));
//
//      Float_t af_my = art::enewz::enewz(1, 1.007825031898f, e2, char_mylar, 0.0f, 300.0f, (Float_t)thickness_from_window);
//      Float_t af_gas = art::enewz::enewz(1, 1.007825031898f, af_my, char_he, 250.0f, 300.0f, 540.0f);
//
//      h_tel3->Fill(gRandom->Gaus(af_gas, 1.0));
//   }
//   h_tel3->Draw();
//   gROOT->ProcessLine(Form("artcanvas->Print(\"figure/beam/ES/tel3_rough.png\")"));
//   //==================== END ======================================
//   //==================== MAIN ======================================
//   TH1F *h_tel4 = new TH1F("h_tel4", "tel4 window elastic scattering", 1000,0.0,20.0);
//   for(Int_t i=0; i<10000; i++){
//      Double_t thickness = get_ReactionPos();
//      Double_t thickness_from_window = 0.01f - thickness;
//      Double_t ave_angle = 17.1 * TMath::Pi()/180.0; // tel4
//
//      Float_t ini_energy = art::enewz::eoldz(14, 25.992333818f, fIniEnergy, char_mylar, 0.0f, 300.0f, (Float_t)thickness_from_window);
//      Float_t e2 = (ini_energy * 4.0 * 25.99233 * 1.007825 * TMath::Cos(ave_angle) * TMath::Cos(ave_angle))/((25.992333 + 1.007825)*(25.992333 + 1.007825));
//
//      Float_t af_my = art::enewz::enewz(1, 1.007825031898f, e2, char_mylar, 0.0f, 300.0f, (Float_t)thickness_from_window);
//      Float_t af_gas = art::enewz::enewz(1, 1.007825031898f, af_my, char_he, 250.0f, 300.0f, 540.0f);
//
//      h_tel4->Fill(gRandom->Gaus(af_gas, 1.0));
//   }
//   h_tel4->Draw();
//   gROOT->ProcessLine(Form("artcanvas->Print(\"figure/beam/ES/tel4_rough.png\")"));
//   //==================== END ======================================
//   //==================== MAIN ======================================
//   TH1F *h_tel5 = new TH1F("h_tel5", "tel5 window elastic scattering", 1000,0.0,20.0);
//   for(Int_t i=0; i<10000; i++){
//      Double_t thickness = get_ReactionPos();
//      Double_t thickness_from_window = 0.01f - thickness;
//      Double_t ave_angle = 22.9 * TMath::Pi()/180.0; // tel5
//
//      Float_t ini_energy = art::enewz::eoldz(14, 25.992333818f, fIniEnergy, char_mylar, 0.0f, 300.0f, (Float_t)thickness_from_window);
//      Float_t e2 = (ini_energy * 4.0 * 25.99233 * 1.007825 * TMath::Cos(ave_angle) * TMath::Cos(ave_angle))/((25.992333 + 1.007825)*(25.992333 + 1.007825));
//
//      Float_t af_my = art::enewz::enewz(1, 1.007825031898f, e2, char_mylar, 0.0f, 300.0f, (Float_t)thickness_from_window);
//      Float_t af_gas = art::enewz::enewz(1, 1.007825031898f, af_my, char_he, 250.0f, 300.0f, 540.0f);
//
//      h_tel5->Fill(gRandom->Gaus(af_gas, 1.0));
//   }
//   h_tel5->Draw();
//   gROOT->ProcessLine(Form("artcanvas->Print(\"figure/beam/ES/tel5_rough.png\")"));
//   //==================== END ======================================
//   //==================== END ======================================
}

Double_t TSimESProcessor::get_ReactionPos()
{
   Double_t random = gRandom->Uniform(0.0, 1.0);
   Double_t position = -1.0;
   for(Double_t pos = 0.0; pos<0.01; pos+=0.00001){
      Double_t obj = norm*(p0*pos + p1*pos*pos/2.0 + p2*pos*pos*pos/3.0);
      if(TMath::Abs(obj - random) < 0.001){
         position = pos;
         break;
      }
   }

   if(position < 0){
      std::cout << "warning" << std::endl;
   }
   return position;
}

Double_t TSimESProcessor::get_ReactionAngle() // cm_angle rad
{
   Double_t angle_cm = 0.0;

   Double_t norm_angle = 0.0;
   Double_t d_angle = TMath::Pi()/1800.0;
   for(Double_t angle=TMath::Pi()/180.0; angle<TMath::Pi(); angle+=d_angle){
      norm_angle += (TMath::Sin(angle)/TMath::Power(TMath::Sin(angle/2.0), 4.0)) * (d_angle);
   }

   Double_t uni = gRandom->Uniform(0.0, 1.0);
   Double_t tmp = 0.0;
   for(Double_t angle=TMath::Pi()/180.0; angle<TMath::Pi(); angle+=d_angle){
      tmp += (TMath::Sin(angle)/TMath::Power(TMath::Sin(angle/2.0), 4.0)) * (d_angle) / norm_angle;
      if(tmp > uni){
         angle_cm = angle + (gRandom->Uniform(0.0, 1.0) - 0.5) * d_angle;
         break;
      }
   }


   return angle_cm;
}

Double_t TSimESProcessor::cm2lab_angle(Double_t angle)
{
   Double_t angle_l = 0.0;

   Double_t gamma = 25.992333818/1.007825031898; // si26/proton 
   Double_t cos = (gamma + TMath::Cos(angle))/(TMath::Sqrt(1.0 + gamma*gamma + 2.0*gamma*TMath::Cos(angle)));

   angle_l = TMath::ACos(cos);

   std::cout << angle*180.0/TMath::Pi() << " " << angle_l*180.0/TMath::Pi() << std::endl;
   return angle_l;
}


void TSimESProcessor::Process()
{
	fOutData->Clear("C");

   if((*fInData)->GetEntriesFast() != 1){
      Info("Process","input entry is not 1");
   }

}
