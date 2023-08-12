// K.Okawa created <okawa@cns.s.u-tokyo.ac.jp>

#include "TSimTiming.h"

#include "constant.h"
#include "TDataObject.h"
#include "TSimBeamData.h"
#include "TSimResultData.h"

#include "TEnewzCalculator.h"

#include <TVector3.h>
#include <TSpline.h>
#include <TClonesArray.h>
#include <TClass.h>
#include <TGraph.h>
#include <TRandom.h>
#include <TStyle.h>
#include <TAxis.h>
#include <TF1.h>
#include <TH1.h>
#include <TMath.h>

using art::TSimTiming;

ClassImp(TSimTiming)

TSimTiming::TSimTiming()
	 : fInData(NULL), fOutData(NULL)
{
	RegisterInputCollection("InputCollection", "beam info",
	                        fInputColName, TString("beam"));
   RegisterOutputCollection("OutputCollection", "simulation result collection",
	                        fOutputColName, TString("result"));

   //RegisterProcessorParameter("RotationZpos","origin z position of the rotation",
			//                  fRotZpos, 0.0);
   
}

TSimTiming::~TSimTiming()
{
	delete fOutData;
	fOutData = NULL;
}

void TSimTiming::Init(TEventCollection *col)
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

   // check timing function
//gROOT->ProcessLine("zone");
   TGraph *g_time = new TGraph();
   Int_t g_i = 0;
   Float_t energy_tmp = fIniEnergy;
   Double_t timing_tmp = 0.0;
   for(Float_t dis = 0.1f; dis<450.0f; dis+=0.1f){
      Float_t energy_aft = art::enewz::enewz(fZSi, fMSi, energy_tmp, char_he, 250.0f, 300.0f, 0.1f);
      timing_tmp += 0.1/(C*TMath::Sqrt(2.0*(Double_t)energy_aft/((Double_t)fMSi*amu2MeV)));
      g_time->SetPoint(g_i, dis, timing_tmp);
      energy_tmp = energy_aft;
      g_i++;
   }
   sp_time = new TSpline3("sp_time", g_time);
//g_time->GetXaxis()->SetLimits(-0.001, 0.014);
//g_time->GetYaxis()->SetRangeUser(0.,0.4);
//g_time->SetTitle(Form("timing vs distance from window;distance from window;time (ns)"));
//g_time->Draw("ap");
//sp_time->SetLineWidth(2);
//sp_time->SetLineColor(kRed);
//sp_time->Draw("same");
//
//gROOT->ProcessLine(Form("artcanvas->Print(\"c1.png\")"));






   gRandom->SetSeed(time(NULL));
   count = 0;
   total_count = 0;
}


void TSimTiming::Process()
{

	fOutData->Clear("C");

   if((*fInData)->GetEntriesFast() != 1){
      Info("Process","input entry is not 1");
   }

   const TDataObject *const inData = static_cast<TDataObject*>((*fInData)->At(0));
   const TSimBeamData *const Data = dynamic_cast<const TSimBeamData*>(inData);


   //Float_t broad_energy = (Float_t)(gRandom->Gaus(fIniEnergy, beam_sigma));
   Float_t broad_energy = fIniEnergy;

   Double_t from_window = 500.0 * gRandom->Uniform(0.0, 1.0);
   //Double_t from_window = 0.0;
   Float_t elab = art::enewz::enewz(fZSi, fMSi, broad_energy, char_he, 250.0f, 300.0f, (Float_t)from_window);

   Double_t random_u = gRandom->Uniform(0.0,1.0);
   Double_t random_v = gRandom->Uniform(0.0,1.0);
   Double_t z = -2.0*random_u + 1;
   Double_t x = TMath::Sqrt(1.0-z*z)*TMath::Cos(2.0*TMath::Pi()*random_v);
   Double_t y = TMath::Sqrt(1.0-z*z)*TMath::Sin(2.0*TMath::Pi()*random_v);
   for(Int_t j=0; j<5; j++){
      TVector3 proton_dir(x, y, z);
      Double_t sc_angle = proton_dir.Theta();
      TVector3 proton_pos(0.0, 0.0, from_window);

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

      count++;

      TVector3 proton_l = det_position - proton_pos;
      Double_t gas_thickness = proton_l.Mag();

      TSimResultData *outData = static_cast<TSimResultData*>(fOutData->ConstructedAt(0));
      outData->SetID(j+1);
      // kinematics===================
      Float_t proton_energy = get_Etotal(elab, sc_angle);
      //==============================
      Float_t af_gas_energy = art::enewz::enewz(fZp, fMp, proton_energy, char_he, 250.0f, 300.0f, gas_thickness);
      //outData->SetEtotal(gRandom->Gaus(af_gas_energy, SSD_sigma));
      outData->SetEtotal(af_gas_energy);

      Float_t timing = (gas_thickness / C) * TMath::Sqrt((fMp * amu2MeV)/(2.0 * af_gas_energy));
      //outData->SetTiming(gRandom->Gaus(timing + sp_time->Eval(from_window), TDC_sigma));
      outData->SetTiming(timing + sp_time->Eval(from_window));

      std::cout << "hit " << count << " window " << from_window << " at tel " << j+1 << " energy: " << af_gas_energy << " timing: " << timing + sp_time->Eval(from_window) << std::endl;

      break;

   }
}

Float_t TSimTiming::get_Etotal(Float_t elab, Double_t L_angle)
{
   //std::cout << std::endl;
   //std::cout << elab << " MeV: " << L_angle << " " << L_angle*180.0/TMath::Pi() << std::endl;

   Double_t alpha = ((Double_t)fMrin + (Double_t)fMalpha) * amu2MeV;
   Double_t beta  = ((Double_t)fMSi - (Double_t)fMrin) * amu2MeV * elab - (Double_t)fMrin * amu2MeV * Q_value;
   Double_t gamma = 4.0*(Double_t)fMSi * amu2MeV * (Double_t)fMp * amu2MeV * elab * TMath::Cos(L_angle) * TMath::Cos(L_angle);

   Double_t factor1 = beta/alpha - gamma/(2.0*alpha*alpha);
   Double_t factor2 = ((beta)*(beta))/((alpha)*(alpha));

   //std::cout << -factor1 << " +/- " << TMath::Sqrt(factor1*factor1 - factor2) << std::endl;
   return -factor1 + TMath::Sqrt(factor1*factor1 - factor2);
}

