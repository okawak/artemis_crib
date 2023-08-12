// K.Okawa created <okawa@cns.s.u-tokyo.ac.jp>

#include "TSimTreeRandomBeamGenerator.h"

#include "constant.h"
#include "TDataObject.h"
#include "TTrack.h"
#include "TSimpleData.h"
#include "TSimBeamData.h"

#include <TClonesArray.h>
#include <TClass.h>
#include <TFile.h>
#include <TTree.h>
#include <TVector3.h>

using art::TSimTreeRandomBeamGenerator;

ClassImp(TSimTreeRandomBeamGenerator)

TSimTreeRandomBeamGenerator::TSimTreeRandomBeamGenerator()
	 : fBeamData(NULL),fOutData(NULL)
{
   RegisterOutputCollection("OutputCollection", "generated beam information",
	                        fOutputColName, TString("beam"));

   RegisterProcessorParameter("FileName","The name of output file",fFileName,TString("temp.root"));
   RegisterProcessorParameter("TreeName","The name of output tree",fTreeName,TString("tree"));
   RegisterProcessorParameter("BeamBranchName","The name of beam branch",fBeamBranchName,TString("beam"));

}

TSimTreeRandomBeamGenerator::~TSimTreeRandomBeamGenerator()
{
	delete fOutData;
	fOutData = NULL;
}

void TSimTreeRandomBeamGenerator::Init(TEventCollection *col)
{
   Info("Init","Input file = %s",fFileName.Data());
   fFile = TFile::Open(fFileName);
   Info("Init","Input tree = %s",fTreeName.Data());
   fTree = (TTree*)fFile->Get(fTreeName);
   if (!fTree) {
      Error("Init","Input tree '%s' does not exist in '%s'",fTreeName.Data(),
            fFileName.Data());
      return;
   }

   iEntry = 0;
   fTree->SetBranchAddress(fBeamBranchName.Data(), &fBeamData);

   nEntry = fTree->GetEntriesFast();
   Info("Init","entry = %ld", nEntry);

   fOutData = new TClonesArray("art::TSimBeamData");
   fOutData->SetName(fOutputColName);
   col->Add(fOutputColName,fOutData,fOutputIsTransparent);

}

void TSimTreeRandomBeamGenerator::Process()
{
	fOutData->Clear("C");

   TSimBeamData *outData = static_cast<TSimBeamData*>(fOutData->ConstructedAt(0));
   fTree->GetEntry(iEntry);

   TTrack *Data = (TTrack*)fBeamData->At(0);
   outData->SetTrack(Data->GetX(), Data->GetY(), Data->GetZ(), Data->GetA(), Data->GetB());

   TVector3 dir(Data->GetX(100.0) - Data->GetX(), Data->GetY(100.0) - Data->GetY(), 100.0);
   outData->SetTheta(dir.Theta());
   outData->SetPhi(dir.Phi());

   iEntry++;
   if(iEntry == nEntry) iEntry = 0;

}