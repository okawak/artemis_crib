/**
 * @file    TTreePeriodicEventStore.cc
 * @brief
 * @author  Kodai Okawa<okawa@cns.s.u-tokyo.ac.jp>
 * @date    2023-08-01 22:36:36
 * @note    last modified: 2024-08-17 14:09:39
 * @details just modify the process() from TTreeEventStore to return 0
 */

#include "TTreePeriodicEventStore.h"
#include "TChain.h"
#include "TObjString.h"
#include "TSystem.h"
#include <TClonesArray.h>
#include <TConditionBit.h>
#include <TEventHeader.h>
#include <TFile.h>
#include <TLeaf.h>
#include <TList.h>
#include <TLoop.h>
#include <TProcessor.h>
#include <TROOT.h>
#include <TTree.h>

ClassImp(art::TTreePeriodicEventStore);

////////////////////////////////////////////////////////////////////////////////
/// default constructor.

art::TTreePeriodicEventStore::TTreePeriodicEventStore()
    : fFile(nullptr), fTree(nullptr), fEventHeader(nullptr) {
    RegisterProcessorParameter("FileName", "The name of input file", fFileName, TString("temp.root"));
    RegisterProcessorParameter("TreeName", "The name of input tree", fTreeName, TString("tree"));
    RegisterProcessorParameter("MaxEventNum", "The maximum event number to be analyzed. Analyze all the data if this is set to be 0", fMaxEventNum, 0L);
    fObjects = new TList;
}
art::TTreePeriodicEventStore::~TTreePeriodicEventStore() {
    if (fFile)
        fFile->Close();
    fTree = nullptr;
}

void art::TTreePeriodicEventStore::Init(TEventCollection *col) {
    // extract files to be analyzed by this process
    std::vector<TString> files;
    TString filelist = gSystem->GetFromPipe(Form("ls -tr %s", fFileName.Data()));
    TObjArray *allfiles = (filelist.Tokenize("\n"));
    if (!allfiles) {
        Error("Init", "No such files %s", fFileName.Data());
        SetStateError("Init");
        return;
    }

    if (fMaxEventNum == 0L) {
        SetStateError("Set MaxEventNum");
        return;
    }
#if USE_MPI
    int useMPI;
    MPI_Initialized(&useMPI);
    if (useMPI) {
        MPI_Comm_size(MPI_COMM_WORLD, &fNPE);
        MPI_Comm_rank(MPI_COMM_WORLD, &fRankID);
        TChain *chain = new TChain(fTreeName);
        for (Int_t i = fRankID, n = allfiles->GetEntriesFast(); i < n; i += fNPE) {
            Info("Init", "Add '%s' to Rank %03d", static_cast<TObjString *>(allfiles->At(i))->GetName(), fRankID);
            chain->Add(static_cast<TObjString *>(allfiles->At(i))->GetName());
        }
        fTree = chain;
    }
#endif
    if (!fTree) {
        TChain *chain = new TChain(fTreeName);
        for (Int_t i = 0, n = allfiles->GetEntriesFast(); i < n; ++i) {
            Info("Init", "Add '%s'", static_cast<TObjString *>(allfiles->At(i))->GetName());
            chain->Add(static_cast<TObjString *>(allfiles->At(i))->GetName());
        }
        fTree = chain;
    }

    // TTreeが使える状況であるかのチェックをして、使えなければこのプロセスはストップするということにする。
    // 万が一プロセス数がファイルの数を超えるような場合でも問題はない。ということは 144 以上のプロセスでくんでもよい。
    // その場合は、Tree projection のマージで引っかからないように気をつけなければならない。か
    fEventNum = 0;
    fCurrentNum = 0;
    fCondition = (TConditionBit **)(col->Get(TLoop::kConditionName)->GetObjectRef());
    // TDirectory *saved = gDirectory;
    //   fFile = TFile::Open(fFileNam);
    //   saved->cd();
    //   if (!fFile) {
    //      (*fCondition)->Set(TLoop::kStopLoop);
    //      return ;
    //   }
    //   Info("Init","Input tree = %s",fTreeName.Data());
    std::vector<TBranch *> useBranch;
    //   fTree = (TTree*)fFile->Get(fTreeName);
    if (!fTree) {
        Error("Init", "Input tree '%s' does not exist in '%s'", fTreeName.Data(),
              fFileName.Data());
        (*fCondition)->Set(TLoop::kStopLoop);
        return;
    }
    TIter next(fTree->GetListOfBranches());
    TBranch *br = nullptr;
    while ((br = (TBranch *)next())) {
        TClass *cls = nullptr;
        EDataType type;
        ;
        if (br->GetExpectedType(cls, type)) {
            Warning("Init", "Unresolved type for branch '%s'", br->GetName());
            continue;
        } else if (!cls) {
            // primitive types
            void *input = nullptr;
            Int_t counter = 0;
            // get dimension
            TLeaf *leaf = br->GetLeaf(br->GetName())->GetLeafCounter(counter);
            if (leaf)
                counter = leaf->GetMaximum();
            switch (type) {
            case kInt_t:
                input = (void *)new Int_t[counter];
                break;
            case kFloat_t:
                input = (void *)new Float_t[counter];
                break;
            case kDouble_t:
                input = (void *)new Double_t[counter];
                break;
            case kULong64_t:
                //            input = (void*) new ULong64_t[counter];
                break;
            default:
                break;
            }
            if (!input) {
                //            SetStateError(TString::Format("branch: %s is unsupported type %s",br->GetName(),TDataType::GetTypeName(type)));
                //            return;
            } else {
                useBranch.push_back(br);
                col->Add(new TEventObject(br->GetName(), input, TString(TDataType::GetTypeName(type)), nullptr));
                fTree->SetBranchAddress(br->GetName(), *col->Get(br->GetName())->GetObjectRef());
                printf("branch : %s (%s) %p\n", br->GetName(), TDataType::GetTypeName(type), *col->Get(br->GetName())->GetObjectRef());
            }
        } else {
#if 1
            if (cls == TClonesArray::Class()) {
                TClonesArray *arr = nullptr;
                fTree->SetBranchStatus("*", 0);
                fTree->SetBranchStatus(br->GetName());
                fTree->SetBranchAddress(br->GetName(), &arr);
                fTree->GetEntry(0);
                TClass *realcls = arr->GetClass();
                if (!realcls->GetNew()) {
                    cls = 0;
                }
                br->ResetAddress();
            }
#endif
            if (cls) {
                useBranch.push_back(br);
                // object known by ROOT
                col->Add(br->GetName(), (TObject *)cls->New(), kTRUE);
                fTree->SetBranchAddress(br->GetName(), (TObject **)col->Get(br->GetName())->GetObjectRef());
                printf("branch : %s\n", br->GetName());
            }
            if (cls == TEventHeader::Class()) {
                fEventHeader = reinterpret_cast<TEventHeader **>(col->GetObjectRef(br->GetName()));
            }
        }
    }
    TIter nextinfo(fTree->GetUserInfo());
    TObject *obj = nullptr;
    while ((obj = nextinfo()) != nullptr) {
        col->AddInfo(obj->GetName(), obj, kTRUE);
    }
    fTree->SetBranchStatus("*", 0);
    for (Int_t i = 0, n = useBranch.size(); i < n; ++i) {
        fTree->SetBranchStatus(useBranch[i]->GetName());
    }
    fTree->LoadTree(0);
    fTree->GetEntry(0);
    fTreeEventNum = fTree->GetEntries();
}
void art::TTreePeriodicEventStore::Process() {
    fTree->GetEntry(fCurrentNum);
    fCurrentNum++;
    fEventNum++;
    if (fEventNum == fTreeEventNum) {
        fCurrentNum = 0;
    }
    if (fMaxEventNum == fEventNum) {
        SetStopLoop();
        SetEndOfRun();
    }
}

Int_t art::TTreePeriodicEventStore::GetRunNumber() const {
    if (nullptr == fEventHeader)
        return 0;
    return (*fEventHeader)->GetRunNumber();
}

const char *art::TTreePeriodicEventStore::GetRunName() const {
    return "";
}

std::string art::TTreePeriodicEventStore::GetStrRunName() const {
    if (nullptr == fEventHeader)
        return "";
    return std::string((*fEventHeader)->GetRunName());
}
