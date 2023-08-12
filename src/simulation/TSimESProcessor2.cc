// K.Okawa created <okawa@cns.s.u-tokyo.ac.jp>

#include "TSimESProcessor2.h"

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

using art::TSimESProcessor2;

ClassImp(TSimESProcessor2)

TSimESProcessor2::TSimESProcessor2()
	 : fInData(NULL), fOutData(NULL)
{
	RegisterInputCollection("InputCollection", "beam info",
	                        fInputColName, TString("beam"));
   RegisterOutputCollection("OutputCollection", "simulation result collection",
	                        fOutputColName, TString("result"));

   RegisterProcessorParameter("WindowZpos","window position",
			                  fWindowZpos, 0.0f);
   RegisterProcessorParameter("WindowThickness","window thickness",
			                  fWindowThickness, 0.0f);
   
}

TSimESProcessor2::~TSimESProcessor2()
{
	delete fOutData;
	fOutData = NULL;
}

void TSimESProcessor2::Init(TEventCollection *col)
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
//gStyle->SetMarkerStyle(20);
//gStyle->SetMarkerSize(0.5);
//gStyle->SetStatY(0.4);
   gRandom->SetSeed(0);

//gROOT->ProcessLine("zone");
   
   // calculate 1/E^2 function as z (position of the target)
	Info("Init", "calculate 1/E^2 as a function of z");
   const Int_t N = 100;
   Int_t j = 0;
   TGraph *g = new TGraph();
   Float_t thickness = 0.0f;
   //while(j<N){
   while(thickness < fWindowThickness){
      thickness = 0.0001f * (Float_t)j;
      //Float_t z = mylar_thickness - thickness;
      Float_t z = fWindowThickness - thickness;

      //ppac
      //Float_t energy = art::enewz::eoldz(fZa, fMa, fIniEnergy, char_mylar, 0.0f, 300.0f, 0.013f);
      //Float_t bef_energy = art::enewz::eoldz(fZa, fMa, energy, char_mylar, 0.0f, 300.0f, thickness);

      //window
      Float_t bef_energy = art::enewz::eoldz(fZa, fMa, fIniEnergy, char_mylar, 0.0f, 300.0f, thickness);

      Float_t ecm = bef_energy * (fMA/(fMa + fMA));
      g->SetPoint(j, z, 1.0/(ecm*ecm)); // 1/Ecm^2
      j++;
   }
//g->GetXaxis()->SetLimits(-0.001, 0.014);
//g->GetYaxis()->SetRangeUser(0.,0.4);
//g->SetTitle(Form("energy loss check;mylar thickness;calculated energy (MeV)"));
//g->Draw("ap");

   TF1 *f = new TF1("f", "pol2");
   g->Fit(f,"q");
//gROOT->ProcessLine(Form("artcanvas->Print(\"figure/beam/ES/enewz_check.png\")"));

   p0 = f->GetParameter(0);
   p1 = f->GetParameter(1);
   p2 = f->GetParameter(2);

   //norm = 1.0/Integral_energy_inv_square((Double_t)mylar_thickness);
   norm = 1.0/Integral_energy_inv_square((Double_t)fWindowThickness);
	Info("Init", "approximate as p0 + p1*z + p2*z^2");
	Info("Init", "\tp0 = %lf", p0);
	Info("Init", "\tp1 = %lf", p1);
	Info("Init", "\tp2 = %lf", p2);

   // check the reaction position random number
//Info("Init", "check the random number of reaction position");
//TH1F *h1 = new TH1F("h1", "random test", 100,-0.001,0.014);
//for(Int_t i=0; i<100000; i++){
//   h1->Fill(get_ReactionPos());
//}
//h1->Draw();
//gROOT->ProcessLine(Form("artcanvas->Print(\"figure/beam/ES/random_check_target.png\")"));

   // check the angle (theta) random number
	Info("Init", "check the random number of reaction position");

   norm_angle = 1.0/Integral_angle_depend(angle_end);
//TH1F *h2 = new TH1F("h2", "random test", 100,0.,180.);
//for(Int_t i=0; i<100000; i++){
//   h2->Fill(get_ReactionAngle() * 180.0/TMath::Pi());
//}
//h2->Draw();
//gROOT->ProcessLine(Form("artcanvas->Print(\"figure/beam/ES/random_check_theta.png\")"));


   // calculate all reaction cross section (probability of the reaction)
   //prob = (8.0*mylar_rho*NA/mylar_A) * ((Double_t)fZa*(Double_t)fZA*esquare/4.0)*((Double_t)fZa*(Double_t)fZA*esquare/4.0) * (2.0*TMath::Pi()) * (1.0/norm) * (1.0/norm_angle);
   prob = 1.0;


	Info("Init", "Integral check norm_position => %lf, norm_angle => %lf", norm, norm_angle);
	Info("Init", "reaction probability => %lf", prob);

   count = 0;
   total_count = 0;
}

Double_t TSimESProcessor2::Integral_angle_depend(Double_t a_stop)
{
   Double_t integral = 0.0;
   for(Double_t angle = angle_start; angle<a_stop; angle+=d_angle){
      integral += (d_angle * TMath::Sin(angle)/( TMath::Power(TMath::Sin(angle/2.0), 4.0)) );
   }
   return integral;
}


Double_t TSimESProcessor2::get_ReactionPos()
{
   Double_t random = gRandom->Uniform(0.0, 1.0);
   Double_t position = -1.0;
   //for(Double_t pos = 0.0; pos<(Double_t)mylar_thickness; pos+=0.00001){
   for(Double_t pos = 0.0; pos<(Double_t)fWindowThickness; pos+=0.000005){
      Double_t obj = norm*Integral_energy_inv_square(pos);
      if(TMath::Abs(obj - random) < 0.001){
         position = pos;
         break;
      }
   }

   if(position < 0){
      std::cout << "warning " << random << " " << norm*Integral_energy_inv_square(0.001) << std::endl;
   }
   return position;
}


Double_t TSimESProcessor2::get_ReactionAngle() // cm_angle rad
{
   Double_t angle_cm = 0.0;
   Double_t uni = gRandom->Uniform(0.0, 1.0);
   Double_t tmp = 0.0;
   for(Double_t angle=angle_start; angle<angle_end; angle+=d_angle){
      tmp += (norm_angle * d_angle * TMath::Sin(angle)/( TMath::Power(TMath::Sin(angle/2.0), 4.0)) );
      if(tmp > uni){
         angle_cm = angle + (gRandom->Uniform(0.0, 1.0) - 0.5) * d_angle;
         break;
      }
   }
   return angle_cm;
}

void TSimESProcessor2::Process()
{
   total_count++;
	fOutData->Clear("C");

   if((*fInData)->GetEntriesFast() != 1){
      Info("Process","input entry is not 1");
   }

   // judge the elastic scattering occur or not
   if(gRandom->Uniform(0.0, 1.0) > prob) return;


   const TDataObject *const inData = static_cast<TDataObject*>((*fInData)->At(0));
   const TSimBeamData *const Data = dynamic_cast<const TSimBeamData*>(inData);

   //Float_t broad_energy = (Float_t)(gRandom->Gaus(fIniEnergy, beam_sigma));
   Float_t broad_energy = fIniEnergy;
   Float_t thickness = fWindowThickness - (Float_t)get_ReactionPos();

   //window
   Float_t ini_energy = art::enewz::eoldz(fZa, fMa, broad_energy, char_mylar, 0.0f, 300.0f, thickness);

   //ppac
   //Float_t energy = art::enewz::eoldz(fZa, fMa, broad_energy, char_mylar, 0.0f, 300.0f, 0.013f);
   //Float_t ini_energy = art::enewz::eoldz(fZa, fMa, energy, char_mylar, 0.0f, 300.0f, thickness);

   Double_t theta_cm = get_ReactionAngle();
   Double_t theta_lab = cm2lab_angle(TMath::Pi() - theta_cm);
   Float_t proton_energy = (ini_energy * 4.0 * fMa * fMA * TMath::Cos(theta_lab) * TMath::Cos(theta_lab))/((fMa + fMA)*(fMa + fMA));
   Double_t phi_lab = gRandom->Uniform(0.0, 2.0*TMath::Pi());

   for(Int_t i=0; i<5; i++){
      TVector3 proton_dir = get_proton_direction(Data->GetX(1.0)-Data->GetX(), Data->GetY(1.0)-Data->GetY(), 1.0, theta_lab, phi_lab);

      TVector3 proton_offset(Data->GetX(fWindowZpos), Data->GetY(fWindowZpos), 0.0);
      TVector3 proton_dirpos(proton_dir.X() + Data->GetX(fWindowZpos), proton_dir.Y() + Data->GetY(fWindowZpos), proton_dir.Z());

      Double_t center = 0.0;
      Double_t angle = 0.0;
      Double_t distance = 0.0;
      if(i == 0){
         center = 322.0;
         angle  = -4.0 * (TMath::Pi()/180.0);
         distance = 252.5;
      }else if(i == 1){
         center = 322.0;
         angle  = 27.0 * (TMath::Pi()/180.0);
         distance = 161.5;
      }else if(i == 2){
         center = 322.0;
         angle  = -48.0 * (TMath::Pi()/180.0);
         distance = 122.0;
      }else if(i == 3){
         center = 272.0;
         angle  = 62.0 * (TMath::Pi()/180.0);
         distance = 117.5;
      }else if(i == 4){
         center = 222.0;
         angle  = -73.0 * (TMath::Pi()/180.0);
         distance = 115.5;
      }

      TVector3 offset(0.0, 0.0, center);
      proton_offset -= offset;
      proton_dirpos -= offset;

      proton_offset.RotateY(-angle);
      proton_dirpos.RotateY(-angle);

      if(proton_dirpos.Z()-proton_offset.Z() < 0.0) continue;

      Double_t tmp_factor = (distance-proton_offset.Z())/(proton_dirpos.Z() - proton_offset.Z());
      TVector3 det_position(proton_offset.X() + (proton_dirpos.X() - proton_offset.X()) * tmp_factor, proton_offset.Y() + (proton_dirpos.Y() - proton_offset.Y()) * tmp_factor, proton_offset.Z() + (proton_dirpos.Z() - proton_offset.Z()) * tmp_factor);

      if(TMath::Abs(det_position.X()) > 25.0 || TMath::Abs(det_position.Y()) > 25.0) continue;

      count++;
      std::cout << "hit " << count << " at tel " << i+1 << " (theta_lab = " << theta_lab * (180.0/TMath::Pi()) << ", theta_cm = " << theta_cm * (180.0/TMath::Pi()) << ")" << std::endl;

      TVector3 proton_l = det_position - proton_offset;
      Double_t gas_thickness = proton_l.Mag();

      det_position.RotateY(angle);
      det_position += offset;

      TSimResultData *outData = static_cast<TSimResultData*>(fOutData->ConstructedAt(0));
      outData->SetID(i+1);
      outData->SetX(det_position.X());
      outData->SetY(det_position.Y());
      outData->SetZ(det_position.Z());

      Float_t af_gas_energy = art::enewz::enewz(fZA, fMA, proton_energy, char_he, 250.0f, 300.0f, gas_thickness);
      //outData->SetEtotal(gRandom->Gaus(af_gas_energy, SSD_sigma));
      outData->SetEtotal(af_gas_energy);

      Float_t timing = (gas_thickness / C) * TMath::Sqrt((fMA * amu2MeV)/(2.0 * af_gas_energy));
      //outData->SetTiming(gRandom->Gaus(timing, TDC_sigma));
      outData->SetTiming(timing);
      outData->SetTheta(theta_lab);

      break;

   }

}



Double_t TSimESProcessor2::cm2lab_angle(Double_t angle)
{
   Double_t angle_l = 0.0;

   //Double_t gamma = fMa/fMA; // si26/proton 
   Double_t gamma = 1.0;
   Double_t cos = (gamma + TMath::Cos(angle))/(TMath::Sqrt(1.0 + gamma*gamma + 2.0*gamma*TMath::Cos(angle)));

   angle_l = TMath::ACos(cos);

   return angle_l;
}

TVector3 TSimESProcessor2::get_proton_direction(Double_t beam_xdir, Double_t beam_ydir, Double_t beam_zdir, Double_t theta, Double_t phi)
{
   TVector3 beam(beam_xdir, beam_ydir, beam_zdir);
   TVector3 z(0.0, 0.0, 1.0);

   TVector3 rotate_axis = z.Cross(beam);
   Double_t rotate_angle = beam.Theta();
   beam.Rotate(-rotate_angle, rotate_axis);

   beam.SetTheta(theta);
   beam.SetPhi(phi);

   beam.Rotate(rotate_angle, rotate_axis);

   return beam;
}
