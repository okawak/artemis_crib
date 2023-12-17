/*
   @File name     : TCRIBPIDProcessor.cc
   @description   :
   @Author        : Kodai Okawa<okawa@cns.s.u-tokyo.ac.jp>
   @Created date  : 2023-08-01 11:03:25
   @Last modified : 2023-12-17 16:11:19
*/

#include "TCRIBPIDProcessor.h"
#include "../geo/TDetectorParameter.h"
#include "TParticleInfo.h"

#include "../telescope/TTelescopeData.h"

#include <TDataObject.h>
#include <constant.h>
#include <TArtAtomicMassTable.h>

#include <TClonesArray.h>
#include <TClass.h>
#include <TLorentzVector.h>
#include <TGeoManager.h>
#include <TRandom.h>

using art::TCRIBPIDProcessor;

ClassImp(TCRIBPIDProcessor);

TCRIBPIDProcessor::TCRIBPIDProcessor()
{
   //   RegisterInputCollection("InputCollection", "input branch (collection) name", fInputColName, TString("input"));
   //   RegisterOutputCollection("OutputCollection", "output branch (collection) name", fOutputColName,
   //                            TString("reaction_particles"));
   //
   //   StringVec_t init_s_vec;
   //   DoubleVec_t init_d_vec;
   //   RegisterProcessorParameter("ReactionParticleName", "reaction particle names", fReacPartName, init_s_vec);
   //   RegisterProcessorParameter("EnergyResolution", "energy resolution \% unit", fResolution, init_d_vec);
   //   RegisterProcessorParameter("TargetisGas", "Bool, target is targer or not", fTargetisGas, false);
   //   RegisterProcessorParameter("TargetName", "gas target name", fTargetName, TString(""));
   //   RegisterProcessorParameter("GetOnlyLightParticle", "detect (treat) only light particle", fDoOnlyLightPart, false);
   //
   //   RegisterOptionalInputInfo("DetectorParameter", "name of telescope parameter", fParameterName,
   //                             TString("prm:detector"), &fDetectorPrm, "TClonesArray", "art::TDetectorParameter");
}

TCRIBPIDProcessor::~TCRIBPIDProcessor()
{
   //   delete fOutData;
   //   fOutData = NULL;
   //   delete fElossTable;
   //   fElossTable = NULL;
}

void TCRIBPIDProcessor::Init(TEventCollection *col)
{
   //   fInGeom = reinterpret_cast<TGeoManager **>(col->GetObjectRef("geom"));
   //   if (!fInGeom)
   //   {
   //      SetStateError("gate array not found. Run TUserGeoInitializer before this.");
   //      return;
   //   }
   //
   //   Info("Init", "%s => %s", fInputColName.Data(), fOutputColName.Data());
   //
   //   fInData = reinterpret_cast<TClonesArray **>(col->GetObjectRef(fInputColName.Data()));
   //   if (!fInData)
   //   {
   //      SetStateError(TString::Format("input not found: %s", fInputColName.Data()));
   //      return;
   //   }
   //   const TClass *const cl = (*fInData)->GetClass();
   //   if (!cl->InheritsFrom(art::TParticleInfo::Class()))
   //   {
   //      SetStateError("contents of input array must inherit from art::TParticleInfo");
   //   }
   //
   //   if (!fDetectorPrm)
   //   {
   //      SetStateError("input parameter name is wrong");
   //   }
   //
   //   if (fResolution.size() == 1)
   //   {
   //      for (Int_t iDet = 0; iDet < (*fDetectorPrm)->GetEntriesFast() - 1; iDet++)
   //      {
   //         fResolution.emplace_back(fResolution[0]);
   //      }
   //   }
   //   else if (fResolution.size() == 0)
   //   {
   //      for (Int_t iDet = 0; iDet < (*fDetectorPrm)->GetEntriesFast(); iDet++)
   //      {
   //         fResolution.emplace_back(0.0);
   //      }
   //   }
   //   else if (fResolution.size() != (*fDetectorPrm)->GetEntriesFast())
   //   {
   //      SetStateError("Resolution parameter in yaml file is wrong");
   //      return;
   //   }
   //
   //   // setting for SRIMlib
   //   fElossTable = new SRIMData();
   //   Bool_t isFirst = true;
   //   for (Int_t iPart = 0; iPart < fReacPartName.size(); iPart++)
   //   {
   //      std::vector<std::vector<SRIMtable *>> srim_vv;
   //      for (Int_t iDet = 0; iDet < (*fDetectorPrm)->GetEntriesFast(); iDet++)
   //      {
   //         std::vector<SRIMtable *> srim_v;
   //         TParameterObject *inPrm = static_cast<TParameterObject *>((*fDetectorPrm)->At(iDet));
   //         TDetectorParameter *Prm = dynamic_cast<TDetectorParameter *>(inPrm);
   //         StringVec_t material_vec = Prm->GetMaterial();
   //         if (isFirst)
   //         {
   //            fMaxRadius = Prm->GetMaxRadius();
   //            isFirst = false;
   //         }
   //         for (Int_t iMat = 0; iMat < material_vec.size(); iMat++)
   //         {
   //            srim_v.emplace_back(fElossTable->GetTable(fReacPartName[iPart], material_vec[iMat]));
   //         }
   //         srim_vv.emplace_back(srim_v);
   //         srim_v.clear();
   //      }
   //      fEloss_vvvec.emplace_back(srim_vv);
   //      srim_vv.clear();
   //   }
   //
   //   if (fTargetisGas)
   //   {
   //      for (Int_t iPart = 0; iPart < fReacPartName.size(); iPart++)
   //      {
   //         fTargetEloss_vec.emplace_back(fElossTable->GetTable(fReacPartName[iPart], fTargetName));
   //      }
   //   }
   //
   //   fOutData = new TClonesArray("art::TTelescopeData");
   //   Info("Init", "output branch used art::TTelescopeData");
   //   fOutData->SetName(fOutputColName);
   //   col->Add(fOutputColName, fOutData, fOutputIsTransparent);
   //
   //   gRandom->SetSeed(time(NULL));
}

void TCRIBPIDProcessor::Process()
{
}
