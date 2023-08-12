// K.Okawa created <okawa@cns.s.u-tokyo.ac.jp>

#include "TSimTrackBeamGenerator.h"
#include "TSimUtil.h"

#include "constant.h"
#include "TDataObject.h"
#include "TPPACData.h"
#include "TSimBeamData.h"

#include <TClonesArray.h>
#include <TClass.h>

using art::TSimTrackBeamGenerator;

ClassImp(TSimTrackBeamGenerator)

TSimTrackBeamGenerator::TSimTrackBeamGenerator()
	 : fInData1(NULL), fInData2(NULL), fOutData(NULL)
{
	RegisterInputCollection("UpstreamInput", "upstream tracking detector collection (PPAC)",
	                        fInputColName1, TString("ppaca"));
	RegisterInputCollection("DownstreamInput", "downstream tracking detector collection (PPAC)",
	                        fInputColName2, TString("ppacb"));
   RegisterOutputCollection("OutputCollection", "simulation result collection",
	                        fOutputColName, TString("result"));

   RegisterProcessorParameter("WindowZPos","window Z position",
			                  fWindowZ, 0.0);

}

TSimTrackBeamGenerator::~TSimTrackBeamGenerator()
{
	delete fOutData;
	fOutData = NULL;
}

void TSimTrackBeamGenerator::Init(TEventCollection *col)
{
	Info("Init", "%s %s => %s", fInputColName1.Data(), fInputColName2.Data(), fOutputColName.Data());
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

   const TClass *const cl1 = (*fInData1)->GetClass();
   const TClass *const cl2 = (*fInData2)->GetClass();
   fInputHasData = (cl1->InheritsFrom(art::TPPACData::Class())) && (cl2->InheritsFrom(art::TPPACData::Class()));
   if(!fInputHasData){
      SetStateError("contents of input array must inherit from art::TPPACData");
      return;
   }

   fOutData = new TClonesArray("art::TSimBeamData");
   fOutData->SetName(fOutputColName);
   col->Add(fOutputColName,fOutData,fOutputIsTransparent);

}

void TSimTrackBeamGenerator::Process()
{
	fOutData->Clear("C");

   Int_t nData1 = (*fInData1)->GetEntriesFast();
   Int_t nData2 = (*fInData2)->GetEntriesFast();

   if(nData1 != 1 || nData2 != 1){
      Info("Process","input entry is not 1");
   }

   const TDataObject *const inData1 = static_cast<TDataObject*>((*fInData1)->At(0));
   const TPPACData *const Data1 = dynamic_cast<const TPPACData*>(inData1);

   const TDataObject *const inData2 = static_cast<TDataObject*>((*fInData2)->At(0));
   const TPPACData *const Data2 = dynamic_cast<const TPPACData*>(inData2);

	TSimBeamData *outData = static_cast<TSimBeamData*>(fOutData->ConstructedAt(0));	

   Double_t dX        = Data2->GetX() - Data1->GetX();
   Double_t dY        = Data2->GetY() - Data1->GetY();
   Double_t dZ        = Data2->GetZ() - Data1->GetZ();
   Double_t to_window = fWindowZ - Data1->GetZ();

   outData->SetX(Data1->GetX() + dX*to_window/dZ);
   outData->SetY(Data1->GetY() + dY*to_window/dZ);
   outData->SetZ(fWindowZ);

   outData->SetXdir(dX/dZ);
   outData->SetYdir(dY/dZ);
   outData->SetZdir(1.0);

   outData->SetTheta(TMath::ACos( 1.0/TMath::Sqrt((dX/dZ)*(dX/dZ) + (dY/dZ)*(dY/dZ) + 1.0)) );

   //if(outData->GetTheta() > 0.5){
   //   std::cout << "ppaca X: " << Data1->GetX() << " Y: " << Data1->GetY() << " Z: " << Data1->GetZ() << std::endl;
   //   std::cout << "ppacb X: " << Data2->GetX() << " Y: " << Data2->GetY() << " Z: " << Data2->GetZ() << std::endl;
   //}
	
}