/**
 * @file   TNormalTreeProjectionProcessor.cc
 * @brief  tree projection
 *
 * @date   Created       : 2014-03-05 22:30:06 JST
 *         Last Modified : 2023-01-28 22:41:41 JST (ota)
 * @author Shinsuke OTA <ota@cns.s.u-tokyo.ac.jp>
 *
 *    (C) 2014 Shinsuke OTA
 */

#include "TNormalTreeProjectionProcessor.h"
#include "TNormalTreeProjection.h"
#include "TTree.h"
#include "TFolder.h"
#include "TROOT.h"
#include "TCatCmdHstore.h"
#include "TDirectory.h"
#include "TAnalysisInfo.h"
#include "TArtemisUtil.h"
#include "TMacroReplacer.h"
#include <fstream>
#include <sstream>
#include "yaml-cpp/yaml.h"


#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifdef HAVE_MPI_H
#include <mpi.h>
#endif


using art::TNormalTreeProjectionProcessor;

ClassImp(TNormalTreeProjectionProcessor)

TNormalTreeProjectionProcessor::TNormalTreeProjectionProcessor()
: fTree(NULL),fTreeProj(NULL)
{
   RegisterProcessorParameter("OutputFilename","output filename",fOutputFilename,
                              TString(""));
   RegisterProcessorParameter("Replace","Replacement of macro",fReplacement,TString(""));
   
}

TNormalTreeProjectionProcessor::~TNormalTreeProjectionProcessor()
{
}

TNormalTreeProjectionProcessor::TNormalTreeProjectionProcessor(const TNormalTreeProjectionProcessor& rhs)
{
}

TNormalTreeProjectionProcessor& TNormalTreeProjectionProcessor::operator=(const TNormalTreeProjectionProcessor& rhs)
{
   if (this != &rhs) {

   }
   return *this;
}


void TNormalTreeProjectionProcessor::Init(TEventCollection *col)
{
   fDirectory = gDirectory;

   // initialization of tree projection class
   fTypeName = art::TNormalTreeProjection::Class_Name();
   fParameter = static_cast<TParameterObject*> (TClass::GetClass(fTypeName)->New());
   fParameter->SetName(fParameterName);

   ifstream fin(fFileName);
   if (!fin) {
      SetStateError(Form("No such file '%s'",fFileName.Data()));
      return;
   }
   std::stringstream ss;
   ss << fin.rdbuf();
   std::string input(ss.str());


   Info("Init","do it");
   
   TMacroReplacer replacer;
   if (!fReplacement.IsNull()) {
      YAML::Node doc = YAML::Load(fReplacement.Data());
      replacer.Add(doc);
      input = replacer.Replace(input);
   }
   std::vector<std::string> remains = replacer.Parse(input);
   if (remains.size()) {
      std::ostringstream os;
      std::copy(remains.begin(),remains.end(),std::ostream_iterator<std::string>(os,","));
      std::string emess = os.str();
      emess.erase(emess.size() - std::char_traits<char>::length(","));
      SetStateError(Form("macro remains %s",emess.c_str()));
      return;
   }

   YAML::Node doc = YAML::Load(input);
   if (!fParameter->LoadYAMLNode(doc)) {
      SetStateError("Error while loading histogram definitions.");
      return;
   }

   Info("Init","Treeprojetion is prepared");
   

   if (IsError()) return;
   fTreeProj = static_cast<art::TNormalTreeProjection*>(fParameter);
   
   TAnalysisInfo::AddTo(fDirectory);

   // prepare tree
   fTree = new TTree("tmptree","tree for variables");
   fTree->SetDirectory(NULL);
   TIter *iter = col->GetIter();
   TEventObject *obj;
   while ((obj = (TEventObject*)iter->Next())) {
      if (obj->IsObject()) {
         fTree->Branch(obj->GetName(),obj->GetClass()->GetName(),obj->GetObjectRef(),3200000,0);
      } else {
         TString leaflist = obj->GetName();
         if (obj->GetLength() != "") {
            leaflist.Append(TString::Format("[%s]",obj->GetLength().Data()));
         }
         leaflist.Append(TString::Format("/%s",obj->GetType()));
         fTree->Branch(obj->GetName(),*obj->GetObjectRef(),leaflist.Data());
      }
   }
   fTree->SetCircular(1);

   // sync with tree
   fTreeProj->Sync(fTree);

   TFolder *folder = (TFolder*) gROOT->FindObject("/artemis/loops/loop0");
   if (folder) {
      folder->Add(fTreeProj);
   }

   

      
}

void TNormalTreeProjectionProcessor::Process()
{
   fTree->GetEntry(1);
   fTreeProj->Project();
}

void TNormalTreeProjectionProcessor::PostLoop()
{
   if (fOutputFilename.IsNull()) return;
   TString filename = fOutputFilename;
#ifdef USE_MPI
   int myrank, npe,useMPI;
   MPI_Initialized(&useMPI);
   if (useMPI) {
      MPI_Comm_size(MPI_COMM_WORLD, &npe);
      MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
      filename = Form("%s%d",fOutputFilename.Data(),myrank);
   }
#endif

   
   TDirectory *saved = gDirectory;
   fDirectory->cd();
   TCatCmdHstore hstore;
   hstore.Run(filename,"recreate");
#ifdef USE_MPI
   if (useMPI && npe > 1) {
      Info("PostLoop","Waiting for all the process to be finished (myrank = %d)",myrank);
      MPI_Barrier(MPI_COMM_WORLD);   
      Info("PostLoop","done %d",myrank);
   }
#endif
   saved->cd();
#ifdef USE_MPI
   Info("PostLoop","MPI merge files");
   if (npe > 1) Util::MPIFileMerger(fOutputFilename.Data());
#endif
   
}
