// K.Okawa created <okawa@cns.s.u-tokyo.ac.jp>

#include "TSimBeamPosProcessor.h"
#include "TSimUtil.h"
#include "TSimGeometry.h"

#include "constant.h"
#include "TDataObject.h"
#include "TSimBeamData.h"
#include "TSimBeamPosData.h"

#include <TVector3.h>
#include <TClonesArray.h>
#include <TClass.h>

using art::TSimBeamPosProcessor;

ClassImp(TSimBeamPosProcessor)

TSimBeamPosProcessor::TSimBeamPosProcessor()
	 : fInData(NULL), fOutData(NULL)
{
	RegisterInputCollection("InputCollection", "beam info",
	                        fInputColName, TString("beam"));
   RegisterOutputCollection("OutputCollection", "simulation result collection",
	                        fOutputColName, TString("result"));

   RegisterProcessorParameter("LayerNumber","number of si layer",
			                  fLayerNum, 1);
   RegisterProcessorParameter("RotationZpos","origin z position of the rotation",
			                  fRotZpos, 0.0);
   
}

TSimBeamPosProcessor::~TSimBeamPosProcessor()
{
	delete fOutData;
	fOutData = NULL;
}

void TSimBeamPosProcessor::Init(TEventCollection *col)
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

   fOutData = new TClonesArray("art::TSimBeamPosData");
   fOutData->SetName(fOutputColName);
   col->Add(fOutputColName,fOutData,fOutputIsTransparent);

   Geo = new TSimGeometry();
   Geo->GeometrySet(fLayerNum, true);

}

void TSimBeamPosProcessor::Process()
{
	fOutData->Clear("C");

   if((*fInData)->GetEntriesFast() != 1){
      Info("Process","input entry is not 1");
   }

   //ProcessUseGeoManager();
   ProcessManual();
}

void TSimBeamPosProcessor::ProcessUseGeoManager()
{
	const TDataObject *const inData = static_cast<TDataObject*>((*fInData)->At(0));
	const TSimBeamData *const Data = dynamic_cast<const TSimBeamData*>(inData);

   //================================================
   gGeoManager->SetCurrentPoint(Data->GetX(), Data->GetY(), Data->GetZ());
   gGeoManager->SetCurrentDirection(Data->GetXdir(), Data->GetYdir(), Data->GetZdir());

   TGeoNode *current2 = gGeoManager->GetCurrentNode();
   gGeoManager->FindNode();
   gGeoManager->FindNextBoundary(Geo->Getltar());

   Double_t snext2 = gGeoManager->GetStep();
   std::cout << "snext2 : " << snext2 << std::endl;

   TGeoNode *newNode2 = gGeoManager->Step();

   Bool_t istate2 = gGeoManager->IsStepEntering();
   std::cout << "istate2 : " << istate2 << std::endl;

   Int_t idnode2 = gGeoManager->GetCurrentNodeId();
   std::cout << "idnode2 : " << idnode2 << std::endl;

   Double_t safety2 = gGeoManager->GetSafeDistance();
   std::cout << "safety2 : " << safety2 << std::endl;

   const Char_t *path2 = gGeoManager->GetPath(); // /TOP_1/PSD_3 etc.
   std::cout << "path2 : " << path2 << std::endl;
   //================================================

	
	TSimBeamPosData *data = static_cast<TSimBeamPosData*>(fOutData->ConstructedAt(0));	


	Double_t input_data = Data->GetX();
	data->SetDistance(input_data);

}

void TSimBeamPosProcessor::ProcessManual()
{
	const TDataObject *const inData = static_cast<TDataObject*>((*fInData)->At(0));
	const TSimBeamData *const Data = dynamic_cast<const TSimBeamData*>(inData);

   TVector3 pos(Data->GetX(), Data->GetY(), Data->GetZ() - fRotZpos);
   TVector3 dir(Data->GetXdir(), Data->GetYdir(), Data->GetZdir());
	
   pos.RotateY(4.0 * art::Sim::deg_to_rad);
   dir.RotateY(4.0 * art::Sim::deg_to_rad);
   
   Double_t det_posx = pos.X() + (239.5 - pos.Z()) * dir.X()/dir.Z();
   Double_t det_posy = pos.Y() + (239.5 - pos.Z()) * dir.Y()/dir.Z();

   if(TMath::Abs(det_posx) < 25.0 && TMath::Abs(det_posy) < 25.0){
   	TSimBeamPosData *data = static_cast<TSimBeamPosData*>(fOutData->ConstructedAt(0));	
      for(Int_t i=0; i<16; i++){
         if(TMath::Abs(det_posx - (-25.0 + 25./16. + (Double_t)i * 25./8.)) < 25./16.){
	         data->SetXID(i);
         }
      }

      if(data->GetXID() < 0){ std::cout << "MISS!" << std::endl; }

      TVector3 to_det(det_posx - pos.X(), det_posy - pos.Y(), 239.5 - pos.Z());
      Double_t dis = to_det.Mag();
	   data->SetDistance(dis);
   }

}