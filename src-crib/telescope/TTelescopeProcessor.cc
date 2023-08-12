// K.Okawa created <okawa@cns.s.u-tokyo.ac.jp>
// treat the largest value of each layor

#include "TTelescopeProcessor.h"

#include "ITiming.h"
#include "ICharge.h"
#include "constant.h"
#include "TDataObject.h"
#include "TTimingChargeData.h"
#include "TTelescopeData.h"
#include "TTelescopeParameter.h"

#include <TClonesArray.h>
#include <TClass.h>

using art::TTelescopeProcessor;

ClassImp(art::TTelescopeProcessor)

// Default constructor
TTelescopeProcessor::TTelescopeProcessor()
   : fInData1(NULL), fInData2(NULL), fInData3(NULL), fOutData(NULL)
{
   RegisterInputCollection("InputCollection1",
			   "array of objects inheriting from art::TTimingChargeData",
			   fInputColName1,TString("dEX"));
   RegisterInputCollection("InputCollection2",
			   "array of objects inheriting from art::TTimingChargeData",
			   fInputColName2,TString("dEY"));
   RegisterInputCollection("InputCollection3",
			   "array of objects inheriting from art::TTimingChargeData",
			   fInputColName3,TString("E"));
   RegisterOutputCollection("OutputCollection","output class will be art::TTelescopeData",
			   fOutputColName,TString("telescope"));

   RegisterOptionalInputInfo("TelescopeParameter","name of telescope parameter",fParameterName,
            TString("prm:telescope"),&fParameterSet,"TClonesArray","art::TTelescopeParameter");

}

TTelescopeProcessor::~TTelescopeProcessor()
{
   delete fOutData;
   fOutData = NULL;
}



void TTelescopeProcessor::Init(TEventCollection *col)
{
   Info("Init","%s %s %s => %s",fInputColName1.Data(),fInputColName2.Data(),fInputColName3.Data(),fOutputColName.Data());
   fInData1 = reinterpret_cast<TClonesArray**>(col->GetObjectRef(fInputColName1.Data()));
   if (!fInData1) {
      SetStateError(TString::Format("input not found: %s",fInputColName1.Data()));
      return;
   }

   fInData2 = reinterpret_cast<TClonesArray**>(col->GetObjectRef(fInputColName2.Data()));
   if (!fInData2) {
      SetStateError(TString::Format("input not found: %s",fInputColName2.Data()));
      return;
   }

   fInData3 = reinterpret_cast<TClonesArray**>(col->GetObjectRef(fInputColName3.Data()));
   if (!fInData3) {
      SetStateError(TString::Format("input not found: %s",fInputColName3.Data()));
      return;
   }

   TTelescopeParameter *prm = dynamic_cast<TTelescopeParameter*>((*fParameterSet)->FindObject(fParameterName));
   if (!prm) {
      SetStateError(TString::Format("No such parameter '%s' is found", fParameterName.Data()));
      return;
   }

   //if(prm->GetdE_dE_TimeRange(0) > prm->GetdE_dE_TimeRange(1)) {
   //   SetStateError("dE_dE timerange : min > max");
   //   return;
   //}

   //if(prm->GetdE_E_TimeRange(0) > prm->GetdE_E_TimeRange(1)) {
   //   SetStateError("dE_E timerange : min > max");
   //   return;
   //}

   fTelescopeParameter = prm;


   const TClass *const cl1 = (*fInData1)->GetClass();
   const TClass *const cl2 = (*fInData2)->GetClass();
   const TClass *const cl3 = (*fInData3)->GetClass();
   fInputHasData = (cl1->InheritsFrom(art::TTimingChargeData::Class())) && (cl2->InheritsFrom(art::TTimingChargeData::Class())) && (cl3->InheritsFrom(art::TTimingChargeData::Class()));

   if(!fInputHasData){
      SetStateError("contents of input array must inherit from art::TTimingChargeData");
      return;
   }

   fOutData = new TClonesArray("art::TTelescopeData");
   fOutData->SetName(fOutputColName);
   col->Add(fOutputColName,fOutData,fOutputIsTransparent);

   debug_flag = kTRUE;
}



void TTelescopeProcessor::Process()
{
   fOutData->Clear("C");

   Int_t nData1 = (*fInData1)->GetEntriesFast();
   Int_t nData2 = (*fInData2)->GetEntriesFast();
   Int_t nData3 = (*fInData3)->GetEntriesFast();

   if(nData1 == 0 && nData2 == 0 && nData3 == 0){ return; }

   TTelescopeParameter *prm = (TTelescopeParameter*) fTelescopeParameter; 
   Int_t numE = prm->GetEdetNum();
   if(nData3 > numE){
      SetStateError(TString::Format("entry of E detector %d is over %d", nData3, numE));
      return;
   }

   Int_t itr = 0;
   TTelescopeData *outData = static_cast<TTelescopeData*>(fOutData->ConstructedAt(itr));
   itr++;
   outData->Init(numE);
   outData->SetID(prm->GetTelescopeID());

   Double_t dE = 0.0;
   Double_t dEX = 0.0;
   Double_t dEY = 0.0;
   Double_t E = 0.0;
   Double_t Etotal = 0.0;

   // dEX process
   Int_t dEXID = -1;
   Double_t dEX_tmp=-500.0;
   for(Int_t iData1 = 0; iData1 < nData1; ++iData1){
      const TDataObject *const inData1 = static_cast<TDataObject*>((*fInData1)->At(iData1));
      const TTimingChargeData *const Data1 = dynamic_cast<const TTimingChargeData*>(inData1);
      if(dEX_tmp < Data1->GetCharge() && Data1->GetCharge() < 50.0){
         dEXID = iData1;
         dEX_tmp = Data1->GetCharge();
      }
   }

   if(nData1 != 0 && dEXID != -1){
      const TDataObject *const inData1 = static_cast<TDataObject*>((*fInData1)->At(dEXID));
      const TTimingChargeData *const Data1 = dynamic_cast<const TTimingChargeData*>(inData1);
      Double_t energydEX = Data1->GetCharge();
      if(energydEX > prm->GetdEXEnergyThreshold()){
         outData->SetXID( Data1->GetDetID() );
         outData->SetdEX( energydEX );
         outData->SetdEXTiming( Data1->GetTiming() );
         dEX = energydEX;
         dE += energydEX;
         Etotal += energydEX;
      }
   }

   // dEY process
   Int_t dEYID = -1;
   Double_t dEY_tmp=-500.0;
   for(Int_t iData2 = 0; iData2 < nData2; ++iData2){
      const TDataObject *const inData2 = static_cast<TDataObject*>((*fInData2)->At(iData2));
      const TTimingChargeData *const Data2 = dynamic_cast<const TTimingChargeData*>(inData2);
      if(dEY_tmp < Data2->GetCharge() && Data2->GetCharge() < 50.0){
         dEYID = iData2;
         dEY_tmp = Data2->GetCharge();
      }
   }

   if(nData2 != 0 && dEYID != -1){
      const TDataObject *const inData2 = static_cast<TDataObject*>((*fInData2)->At(dEYID));
      const TTimingChargeData *const Data2 = dynamic_cast<const TTimingChargeData*>(inData2);
      Double_t energydEY = Data2->GetCharge();
      if(energydEY > prm->GetdEYEnergyThreshold()){
         outData->SetYID( Data2->GetDetID() );
         outData->SetdEY( energydEY );
         outData->SetdEYTiming( Data2->GetTiming() );
         dEY = energydEY;
         dE += energydEY;
         Etotal += energydEY;
      }
   }
   
   //if(prm->GetdEIsDSSD() && TMath::Abs(outData->GetdEX() - outData->GetdEY()) > 3.0){
   //   return;
   //}

   if(prm->GetdEIsDSSD()){
      // assume Y position is not separated clearly
      dE = dEX;
      Etotal = dEX;
      //===========end=============

      //dE /= 2.0;
      //Etotal /= 2.0;
   }



   // E1, E2, E3 process
   for(Int_t iData3 = 0; iData3 < nData3; ++iData3){
      const TDataObject *const inData3 = static_cast<TDataObject*>((*fInData3)->At(iData3));
      const TTimingChargeData *const Data3 = dynamic_cast<const TTimingChargeData*>(inData3);

      for(Int_t inE = 0; inE < numE; ++inE){
         if(Data3->GetDetID() == inE){
            outData->SetEvec(inE, Data3->GetCharge());
            outData->SetETimingvec(inE, Data3->GetTiming());
            E += Data3->GetCharge();
            Etotal += Data3->GetCharge();
         }
      }
   }

   outData->SetdE(dE);
   outData->SetE(E);
   outData->SetEtotal(Etotal);

}


//      //set geometry: start****************************
//      Double_t z_ref, dis, angle, tmp;
//      if(fTelescopeID == 1){
//         z_ref = 999.0;
//         dis   = 239.5;
//         angle = -4.0 * TMath::Pi()/180.0;
//      }else if(fTelescopeID == 2){
//         z_ref = 999.0;
//         dis   = 149.5;
//         angle = 27.0 * TMath::Pi()/180.0;
//      }else if(fTelescopeID == 3){
//         z_ref = 999.0;
//         dis   = 110.0;
//         angle = -48.0 * TMath::Pi()/180.0;
//      }else if(fTelescopeID == 4){
//         z_ref = 949.0;
//         dis   = 113.5;
//         angle = 62.0 * TMath::Pi()/180.0;
//      }else if(fTelescopeID == 5){
//         z_ref = 899.0;
//         dis   = 112.5;
//         angle = -73 * TMath::Pi()/180.0;
//      }else{
//         return;
//      } 
//      tmp = 50.0/16.0/2.0 + (Double_t)(Data1->GetDetID() - 8)*50.0/16.0;

//      outData->SetX(dis * TMath::Sin(angle) + tmp * TMath::Cos(angle));
//      outData->SetY(50.0/16.0/2.0 + (Double_t)(Data2->GetDetID() - 8)*50.0/16.0);
//      outData->SetZ(z_ref + dis * TMath::Cos(angle) - tmp * TMath::Sin(angle));
//      //set geometry: end******************************

