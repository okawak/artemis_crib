// K.Okawa created <okawa@cns.s.u-tokyo.ac.jp>

#include "TSimTGTIKPrepProcessor.h"

#include "ITiming.h"
#include "ICharge.h"
#include "constant.h"
#include "TDataObject.h"
#include "TTelescopeData.h"
#include "TTrack.h"
#include "TSimBeamData.h"
#include "TPPACData.h"
#include "TTGTIKPrepData.h"

#include <TClonesArray.h>
#include <TRandom.h>
#include <TClass.h>
#include <TVector3.h>

using art::TSimTGTIKPrepProcessor;

ClassImp(art::TSimTGTIKPrepProcessor)

// Default constructor
TSimTGTIKPrepProcessor::TSimTGTIKPrepProcessor()
   : fInData(NULL), fOutData(NULL)
{
   RegisterInputCollection("InputCollection",
			   "PPACs data array of objects inheriting from art::TTrack",
			   fInputColName,TString("ppac"));
   RegisterOutputCollection("OutputCollection","prep data of thick gas target inverse kinematics art::TSimTGTIKPrepProcessor",
			    fOutputColName,TString("prep_data"));

   RegisterProcessorParameter("WindowPosition","z coodinate of the window",
			      fWindowpos,0.0);

}

TSimTGTIKPrepProcessor::~TSimTGTIKPrepProcessor()
{
   delete fOutData;
   fOutData = NULL;
}


void TSimTGTIKPrepProcessor::Init(TEventCollection *col)
{
   Info("Init","%s => %s", fInputColName.Data(), fOutputColName.Data());

   fInData = reinterpret_cast<TClonesArray**>(col->GetObjectRef(fInputColName.Data()));
   if (!fInData) {
      SetStateError(TString::Format("input not found: %s",fInputColName.Data()));
      return;
   }

   fOutData = new TClonesArray("art::TTGTIKPrepData");
   fOutData->SetName(fOutputColName);
   col->Add(fOutputColName,fOutData,fOutputIsTransparent);

   debug_flag = kTRUE;

   gRandom->SetSeed(time(NULL));
}


TVector3 TSimTGTIKPrepProcessor::get_DetPosition(Int_t telID, Int_t XID, Int_t YID, TVector3 win_offset, TVector3 win_dir)
{
   TVector3 vec_raw;
   if(telID == 1) vec_raw = get_rawDetPosition(XID, YID, 999.0, 244.0, -4.0, 0.0, false);
   else if(telID == 2) vec_raw = get_rawDetPosition(XID, YID, 999.0, 154.5, 27.0, 0.0, false);
   else if(telID == 3) vec_raw = get_rawDetPosition(XID, YID, 999.0, 115.0, -48.0, -0.3, false);
   else if(telID == 4) vec_raw = get_rawDetPosition(XID, YID, 949.0, 113.5, 62.0, 0.4, false);
   else if(telID == 5) vec_raw = get_rawDetPosition(XID, YID, 899.0, 112.5, -73.0, 0.0, false);

   vec_raw -= win_offset;
   TVector3 vec = vec_raw;

   TVector3 z_axis(0.0, 0.0, 1.0);
   TVector3 rotate_axis = z_axis.Cross(win_dir);
   vec.Rotate(-win_dir.Theta(), rotate_axis);

   return vec;
}

TVector3 TSimTGTIKPrepProcessor::get_rawDetPosition(Int_t XID, Int_t YID, Double_t orig_rotate_z, Double_t distance, Double_t angle, Double_t offset, Bool_t x_reflection)
{
   Double_t x = (-25.0 + 25.0/16.0 + (Double_t)XID * 25.0/8.0) + gRandom->Uniform(-25.0/16.0, 25.0/16.0);
   Double_t y = (-25.0 + 25.0/16.0 + (Double_t)YID * 25.0/8.0) + gRandom->Uniform(-25.0/16.0, 25.0/16.0);
   Double_t z = distance;
   if(x_reflection) x = -1.0*x;
   x += offset;

   TVector3 vec(x, y, z);
   Double_t angle_rad = angle * TMath::Pi()/180.0;
   vec.RotateY(angle_rad);

   Double_t tmp_z = vec.Z();
   vec.SetZ(tmp_z + orig_rotate_z);

   return vec;
}






void TSimTGTIKPrepProcessor::Process()
{
   fOutData->Clear("C");

   Int_t nData = (*fInData)->GetEntriesFast();

   if(nData != 1){ 
      std::cout << "Warning!" << std::endl;
      return;
   }

   const TTrack *const inData = static_cast<TTrack*>((*fInData)->At(0));
   const TSimBeamData *const Data = dynamic_cast<const TSimBeamData*>(inData);

   Double_t dX = Data->GetX(1.0) - Data->GetX(0.0);
   Double_t dY = Data->GetY(1.0) - Data->GetY(0.0);
   Double_t dZ = 1.0 - 0.0;

   Double_t winX = Data->GetX(fWindowpos);
   Double_t winY = Data->GetY(fWindowpos);
   Double_t winZ = fWindowpos;
   TVector3 win_offset(winX, winY, winZ);
   TVector3 win_dir(dX/dZ, dY/dZ, 1.0);

   TTGTIKPrepData *outData = static_cast<TTGTIKPrepData*>(fOutData->ConstructedAt(0));
   outData->SetWinx(winX);
   outData->SetWiny(winY);
   outData->SetWinz(winZ);


   outData->SetEtotal(gRandom->Uniform(0.0, 25.0));

   const Int_t telID = gRandom->Integer(5) + 1;
   outData->SetID(telID);

   //Int_t XID = gRandom->Integer(16);
   //Int_t YID = gRandom->Integer(16);
   Int_t XID = 8;
   Int_t YID = 8;

   TVector3 det_vec = get_DetPosition(telID, XID, YID, win_offset, win_dir);
   outData->SetDetx(det_vec.X());
   outData->SetDety(det_vec.Y());
   outData->SetDetz(det_vec.Z());

}
