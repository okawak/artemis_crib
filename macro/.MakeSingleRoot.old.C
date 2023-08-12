void MakeSingleRoot(TString RUNNAME, TString RUNNUM){

    const TString ARTEMIS_WORKDIR = "/home/okawa/art_analysis/user/okawa/";
    TString INROOT = ARTEMIS_WORKDIR + "output/artemis/artemis_" + RUNNAME + RUNNUM + ".root";
    TString OUTROOT = ARTEMIS_WORKDIR + "rootfile/single/single_" + RUNNAME + RUNNUM + ".root";

    FileStat_t info;
    if(gSystem->GetPathInfo(INROOT.Data(), info) != 0){
      std::cerr << "ERROR: file: '" << INROOT.Data() << "' does not exist." << std::endl;
      return;
    }

    // input ROOT file setting------------------------------
    TFile *fin  = TFile::Open(INROOT.Data());
    TTree *intree = (TTree*)fin->Get("tree");

    TClonesArray *single      = NULL;
    TClonesArray *coin        = NULL;
    TClonesArray *pileup      = NULL;
    TClonesArray *rf_cal_0    = NULL;
    TClonesArray *f3bppac     = NULL;
    TClonesArray *f3appac     = NULL;

    intree->SetBranchAddress("single",   &single);
    intree->SetBranchAddress("coin",     &coin);
    intree->SetBranchAddress("pileup",   &pileup);
    intree->SetBranchAddress("rf_cal_0", &rf_cal_0);
    intree->SetBranchAddress("f3bppac",  &f3bppac);
    intree->SetBranchAddress("f3appac",  &f3appac);
    // input ROOT file setting end---------------------------

    // output ROOT file setting------------------------------
    TString pwd = gSystem->pwd();
    TString target = gSystem->DirName(OUTROOT);
    if (gSystem->ChangeDirectory(target)) {
      // target directory exists
      gSystem->ChangeDirectory(pwd);
    } else {
      gSystem->mkdir(target,kTRUE);
    }
    TFile *fout = new TFile(OUTROOT.Data(),"recreate");
    TTree *outtree = new TTree("tree","tree");

    Double_t rf0;
    Double_t ppaca_anode;
    Double_t ppaca_x;
    Double_t ppaca_y;
    Double_t ppaca_z;
    Double_t ppacb_anode;
    Double_t ppacb_x;
    Double_t ppacb_y;
    Double_t ppacb_z;

    outtree->Branch("rf_cal_0.fTiming",&rf0,"rf_cal_0.fTiming/D");
    outtree->Branch("f3appac.fTAnode",&ppaca_anode,"f3appac.fTAnode/D");
    outtree->Branch("f3appac.fX",&ppaca_x,"f3appac.fX/D");
    outtree->Branch("f3appac.fY",&ppaca_y,"f3appac.fY/D");
    outtree->Branch("f3appac.fZ",&ppaca_z,"f3appac.fZ/D");
    outtree->Branch("f3bppac.fTAnode",&ppacb_anode,"f3bppac.fTAnode/D");
    outtree->Branch("f3bppac.fX",&ppacb_x,"f3bppac.fX/D");
    outtree->Branch("f3bppac.fY",&ppacb_y,"f3bppac.fY/D");
    outtree->Branch("f3bppac.fZ",&ppacb_z,"f3bppac.fZ/D");
    // output ROOT file setting end---------------------------

    // analysis start-----------------------------------------
    Int_t progress_tmp = 1;
    Bool_t debug = true;
    for(Int_t iEntry=0; iEntry<intree->GetEntriesFast(); ++iEntry){
      if((iEntry+1) % (Int_t)(intree->GetEntriesFast()/100) == 0){
        std::cout << RUNNAME << RUNNUM << " : " << iEntry << " / " << intree->GetEntriesFast() << " : " << progress_tmp << " %" << std::endl;
        progress_tmp++;
      }
      intree->GetEntry(iEntry);

      // event selection start--------------------------------
      // single process
      if(pileup->GetEntriesFast() > 0) continue;
      if(single->GetEntriesFast() == 0) continue;
      if(coin->GetEntriesFast() > 0) continue;

      // trigger (ppac) process
      rf0 = TMath::QuietNaN();
      ppaca_anode = TMath::QuietNaN();
      ppaca_x = TMath::QuietNaN();
      ppaca_y = TMath::QuietNaN();
      ppaca_z = TMath::QuietNaN();
      ppacb_anode = TMath::QuietNaN();
      ppacb_x = TMath::QuietNaN();
      ppacb_y = TMath::QuietNaN();
      ppacb_z = TMath::QuietNaN();

      Int_t ppaca_hit, ppacb_hit;
      Int_t ppaca_itr = 0;
      Int_t ppacb_itr = 0;

      for(Int_t i=0; i<f3appac->GetEntriesFast(); ++i){
        if(atoi(RUNNUM.Data()) < 249){
          if(TMath::Abs(((art::TPPACData*)f3appac->At(i))->GetTAnode() + 33.0) < 5.0){
            ppaca_hit = i;
            ppaca_itr++;
          }
        }else{
          if(TMath::Abs(((art::TPPACData*)f3appac->At(i))->GetTAnode() + 27.0) < 5.0){
            ppaca_hit = i;
            ppaca_itr++;
          }
        }
      }
      if(ppaca_itr == 0) continue;
      if(ppaca_itr > 1) std::cout << "warning: f3appac event is not 1 (Get last event)" << std::endl;
      ppaca_anode = ((art::TPPACData*)f3appac->At(ppaca_hit))->GetTAnode();
      ppaca_x = ((art::TPPACData*)f3appac->At(ppaca_hit))->GetX();
      ppaca_y = ((art::TPPACData*)f3appac->At(ppaca_hit))->GetY();
      ppaca_z = ((art::TPPACData*)f3appac->At(ppaca_hit))->GetZ();

      for(Int_t i=0; i<f3bppac->GetEntriesFast(); ++i){
        if(TMath::Abs(((art::TPPACData*)f3bppac->At(i))->GetTAnode()) < 1.0){
          ppacb_hit = i;
          ppacb_itr++;
        }
      }
      if(ppacb_itr == 0) continue;
      if(ppacb_itr > 1) std::cout << "warning: f3bppac event is not 1 (Get last event)" << std::endl;
      ppacb_anode = ((art::TPPACData*)f3bppac->At(ppacb_hit))->GetTAnode();
      ppacb_x = ((art::TPPACData*)f3bppac->At(ppacb_hit))->GetX();
      ppacb_y = ((art::TPPACData*)f3bppac->At(ppacb_hit))->GetY();
      ppacb_z = ((art::TPPACData*)f3bppac->At(ppacb_hit))->GetZ();

      if(rf_cal_0->GetEntriesFast() == 1){
        rf0 = ((art::TTimingData*)rf_cal_0->At(0))->GetTiming();
      }else{
        std::cout << "warning: rf_cal_0 event num is not 1, continue" << std::endl;
        continue;
      }

      outtree->Fill();
    }
    // analysis end-------------------------------------------

    outtree->Write();
    fout->Close();

    gROOT->ProcessLine(".q");
}
