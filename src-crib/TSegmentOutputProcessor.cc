/**
 * @file    TSegmentOutputProcessor.cc
 * @brief   from seg conf, output raw data TTree object
 * @author  Kodai Okawa<okawa@cns.s.u-tokyo.ac.jp>
 * @date    2023-12-25 11:41:51
 * @note    the outputted root file can be opened by normal ROOT
 *          (using std::vector)
 */

#include "TSegmentOutputProcessor.h"
#include <TAnalysisInfo.h>
#include <TArtemisUtil.h>
#include <TClass.h>
#include <TClonesArray.h>
#include <TDirectory.h>
#include <TEventObject.h>
#include <TH2F.h>
#include <TModuleInfo.h>
#include <TModuleType.h>
#include <TROOT.h>
#include <TRawDataObject.h>
#include <TSegmentInfo.h>
#include <TSegmentedData.h>
#include <TSystem.h>
#include <TTree.h>
#include <algorithm>

using art::TSegmentOutputProcessor;

ClassImp(TSegmentOutputProcessor);

TSegmentOutputProcessor::TSegmentOutputProcessor()
    : fFile(NULL), fTree(NULL), fSegmentList(NULL), fModuleList(NULL),
      fSegmentedData(NULL) {
    RegisterProcessorParameter("FileName", "The name of output file", fFileName, TString("tmp.root"));
    RegisterProcessorParameter("TreeName", "The name of output tree", fTreeName, TString("tree"));

    StringVec_t defaultignore;
    defaultignore.push_back("");
    RegisterInputCollection("SegmentedDataName", "name of the segmented data",
                            fSegmentedDataName, TString("segdata"),
                            &fSegmentedData, "art::TSegmentedData");

    RegisterInputInfo("SegmentList", "name of the segment list",
                      fSegmentListName, TString("seglist"), &fSegmentList, "TClonesArray", "art::TSegmentInfo");
    RegisterInputInfo("ModuleList", "name of the module list",
                      fModuleListName, TString("modlist"), &fModuleList, "TClonesArray", "art::TModuleType");
    RegisterProcessorParameter("Ignore", "ignore segment list", fIgnore, defaultignore);

    fObjects = new TList;
}

TSegmentOutputProcessor::~TSegmentOutputProcessor() {
    if (gROOT->GetListOfFiles()->FindObject(fFile)) {
        if (fTree)
            fTree->GetUserInfo()->Clear();
        fFile->Close();
    }
    delete fObjects;

    // input processors are deleted elsewhere
    fSegmentedData = NULL;
    fSegmentList = NULL;
    fModuleList = NULL;
}

TSegmentOutputProcessor::TSegmentOutputProcessor(const TSegmentOutputProcessor &rhs) {}

TSegmentOutputProcessor &TSegmentOutputProcessor::operator=(const TSegmentOutputProcessor &rhs) {
    if (this != &rhs) {
    }
    return *this;
}

void TSegmentOutputProcessor::Init(TEventCollection *col) {
    Util::PrepareDirectoryFor(fFileName);
    TDirectory *savedir = gDirectory;
    fFile = TFile::Open(fFileName, "RECREATE");
    if (!fFile) {
        SetStateError(TString::Format("Cannot create file: %s", fFileName.Data()));
        return;
    }
    TAnalysisInfo::AddTo(fFile);
    fTree = new TTree(fTreeName, fTreeName);

    Int_t nSeg = (*fSegmentList)->GetEntriesFast();
    for (Int_t iSeg = 0; iSeg != nSeg; iSeg++) {
        TSegmentInfo *seg = (TSegmentInfo *)(*fSegmentList)->At(iSeg);
        Int_t nMod = seg->GetNumModules();

        // skip if no module registered
        if (!nMod)
            continue;
        if (fIgnore.end() != std::find(fIgnore.begin(), fIgnore.end(), seg->GetName()))
            continue;

        std::pair<int, std::pair<int, std::vector<TModuleInfo *>>> segment;
        segment.first = seg->GetSegID();
        std::pair<int, std::vector<TModuleInfo *>> &module_pairs = fSegments.insert(segment).first->second;

        for (Int_t iMod = 0; iMod != nMod; iMod++) {
            TModuleInfo *mod = seg->GetModule(iMod);
            Int_t id = mod->GetID();
            if (module_pairs.second.size() < (unsigned int)id + 1)
                module_pairs.second.resize(id + 1);
            module_pairs.second.at(id) = mod;
            TModuleType *type = (TModuleType *)(*fModuleList)->FindObject(seg->GetModuleType());
            Int_t nCh = type->GetNch();
            module_pairs.first = nCh;

            // prepare branch (id == 24 or 25 -> multihit TDC)
            if (id == 24 || id == 25) {
                std::cout << "test" << std::endl;
            } else {
            }
        }
    }

    for (std::vector<TString>::iterator it = fIgnore.begin(); it != fIgnore.end(); it++) {
        if ((*it) == "") {
            continue;
        }
        printf("%s will be ignored\n", (*it).Data());
    }
}

void TSegmentOutputProcessor::Process() {
    //    std::map<int, std::vector<TModuleInfo *>>::iterator it;
    //    for (it = fSegments.begin(); it != fSegments.end(); it++) {
    //        Int_t segid = it->first;
    //        TObjArray *arr = (*fSegmentedData)->FindSegmentByID(segid);
    //        if (!arr) {
    //            Warning("Process", "No segment having segid = %d", segid);
    //            Warning("Process", " Add this segid to Ignore if this semgment is not valid temporarily");
    //            SetStopLoop();
    //            return;
    //        }
    //        Int_t nHit = arr->GetEntriesFast();
    //        //      printf("segid = %d, nHit = %d\n",segid,nHit);
    //        std::vector<TModuleInfo *> &modules = it->second;
    //        //      printf("size = %u\n",modules.size());
    //        for (Int_t iHit = 0; iHit != nHit; iHit++) {
    //            TRawDataObject *data = (TRawDataObject *)arr->UncheckedAt(iHit);
    //            Int_t geo = data->GetGeo();
    //            Int_t ch = data->GetCh();
    //            Int_t nVal = data->GetNumValues();
    //            //         printf("Data = %s geo = %d ch = %d nVal = %d\n",data->IsA()->GetName(),geo,ch,nVal);
    //            for (Int_t iVal = 0; iVal != nVal; iVal++) {
    //                if (modules.size() > geo && modules[geo] != NULL) {
    //                    TH2F *hist = (TH2F *)modules[geo]->GetHist(iVal);
    //                    // printf("ival = %d %p\n",iVal,hist);
    //                    if (!hist) {
    //                        Warning("Process", "No hist of iVal#% 3d of %3d for module %s", iVal, nVal, modules[geo]->GetModuleType().Data());
    //                        gSystem->Sleep(10);
    //                    } else {
    //                        hist->Fill(ch, data->GetValue(iVal));
    //                    }
    //                }
    //            }
    //        }
    //    }
}