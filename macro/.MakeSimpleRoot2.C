void MakeSimpleRoot2(TString input){ //input is like high/0271/artemis_high0271.root (not output/)

    const TString ARTEMIS_WORKDIR = "/home/okawa/art_analysis/user/okawa/";
    TString INROOT = ARTEMIS_WORKDIR + "output/" + input;
    TString OUTROOT1 = ARTEMIS_WORKDIR + "rootfile/tel1/" + input;
    TString OUTROOT2 = ARTEMIS_WORKDIR + "rootfile/tel2/" + input;
    TString OUTROOT3 = ARTEMIS_WORKDIR + "rootfile/tel3/" + input;
    TString OUTROOT4 = ARTEMIS_WORKDIR + "rootfile/tel4/" + input;
    TString OUTROOT5 = ARTEMIS_WORKDIR + "rootfile/tel5/" + input;

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
    TClonesArray *tel1        = NULL;
    TClonesArray *tel2        = NULL;
    TClonesArray *tel3        = NULL;
    TClonesArray *tel4        = NULL;
    TClonesArray *tel5        = NULL;
    TClonesArray *lowgain_cal = NULL;

    intree->SetBranchAddress("single",   &single);
    intree->SetBranchAddress("coin",     &coin);
    intree->SetBranchAddress("pileup",   &pileup);
    intree->SetBranchAddress("rf_cal_0", &rf_cal_0);
    intree->SetBranchAddress("f3bppac",  &f3bppac);
    intree->SetBranchAddress("f3appac",  &f3appac);
    intree->SetBranchAddress("tel1", &tel1);
    intree->SetBranchAddress("tel2", &tel2);
    intree->SetBranchAddress("tel3", &tel3);
    intree->SetBranchAddress("tel4", &tel4);
    intree->SetBranchAddress("tel5", &tel5);
    intree->SetBranchAddress("lowgain_cal",&lowgain_cal);
    // input ROOT file setting end---------------------------

    // output ROOT file setting------------------------------
    TString pwd = gSystem->pwd();
    TString target1 = gSystem->DirName(OUTROOT1);
    if (gSystem->ChangeDirectory(target1)) {
      gSystem->ChangeDirectory(pwd);
    } else {
      gSystem->mkdir(target1,kTRUE);
    }
    TFile *fout1 = new TFile(OUTROOT1.Data(),"recreate");
    TTree *outtree1 = new TTree("tree","tree");

    TString target2 = gSystem->DirName(OUTROOT2);
    if (gSystem->ChangeDirectory(target2)) {
      gSystem->ChangeDirectory(pwd);
    } else {
      gSystem->mkdir(target2,kTRUE);
    }
    TFile *fout2 = new TFile(OUTROOT2.Data(),"recreate");
    TTree *outtree2 = new TTree("tree","tree");

    TString target3 = gSystem->DirName(OUTROOT3);
    if (gSystem->ChangeDirectory(target3)) {
      gSystem->ChangeDirectory(pwd);
    } else {
      gSystem->mkdir(target3,kTRUE);
    }
    TFile *fout3 = new TFile(OUTROOT3.Data(),"recreate");
    TTree *outtree3 = new TTree("tree","tree");

    TString target4 = gSystem->DirName(OUTROOT4);
    if (gSystem->ChangeDirectory(target4)) {
      gSystem->ChangeDirectory(pwd);
    } else {
      gSystem->mkdir(target4,kTRUE);
    }
    TFile *fout4 = new TFile(OUTROOT4.Data(),"recreate");
    TTree *outtree4 = new TTree("tree","tree");

    TString target5 = gSystem->DirName(OUTROOT5);
    if (gSystem->ChangeDirectory(target5)) {
      gSystem->ChangeDirectory(pwd);
    } else {
      gSystem->mkdir(target5,kTRUE);
    }
    TFile *fout5 = new TFile(OUTROOT5.Data(),"recreate");
    TTree *outtree5 = new TTree("tree","tree");

    Double_t rf0;
    Double_t ppaca_anode;
    Double_t ppaca_x;
    Double_t ppaca_y;
    Double_t ppaca_z;
    Double_t ppacb_anode;
    Double_t ppacb_x;
    Double_t ppacb_y;
    Double_t ppacb_z;

    Int_t strip_x;
    Int_t strip_y;
    Double_t dEX;
    Double_t dEY;
    Double_t E1;
    Double_t E2;
    Double_t dEX_T;
    Double_t dEY_T;
    Double_t E1_T;
    Double_t E2_T;
    Int_t telID;

    outtree1->Branch("rf0",&rf0,"rf0/D");
    outtree1->Branch("ppaca_anode",&ppaca_anode,"ppaca_anode/D");
    outtree1->Branch("ppaca_x",&ppaca_x,"ppaca_x/D");
    outtree1->Branch("ppaca_y",&ppaca_y,"ppaca_y/D");
    outtree1->Branch("ppaca_z",&ppaca_z,"ppaca_z/D");
    outtree1->Branch("ppacb_anode",&ppacb_anode,"ppacb_anode/D");
    outtree1->Branch("ppacb_x",&ppacb_x,"ppacb_x/D");
    outtree1->Branch("ppacb_y",&ppacb_y,"ppacb_y/D");
    outtree1->Branch("ppacb_z",&ppacb_z,"ppacb_z/D");

    outtree1->Branch("XID",&strip_x,"XID/I");
    outtree1->Branch("YID",&strip_y,"YID/I");
    outtree1->Branch("dEX",&dEX,"dEX/D");
    outtree1->Branch("dEY",&dEY,"fdEY/D");
    outtree1->Branch("E1",&E1,"E1/D");
    outtree1->Branch("E2",&E2,"E2/D");
    outtree1->Branch("dEX_T",&dEX_T,"dEX_T/D");
    outtree1->Branch("dEY_T",&dEY_T,"dEY_T/D");
    outtree1->Branch("E1_T",&E1_T,"E1_T/D");
    outtree1->Branch("E2_T",&E2_T,"E2_T/D");
    outtree1->Branch("telID",&telID,"telID/I");


    outtree2->Branch("rf0",&rf0,"rf0/D");
    outtree2->Branch("ppaca_anode",&ppaca_anode,"ppaca_anode/D");
    outtree2->Branch("ppaca_x",&ppaca_x,"ppaca_x/D");
    outtree2->Branch("ppaca_y",&ppaca_y,"ppaca_y/D");
    outtree2->Branch("ppaca_z",&ppaca_z,"ppaca_z/D");
    outtree2->Branch("ppacb_anode",&ppacb_anode,"ppacb_anode/D");
    outtree2->Branch("ppacb_x",&ppacb_x,"ppacb_x/D");
    outtree2->Branch("ppacb_y",&ppacb_y,"ppacb_y/D");
    outtree2->Branch("ppacb_z",&ppacb_z,"ppacb_z/D");

    outtree2->Branch("XID",&strip_x,"XID/I");
    outtree2->Branch("YID",&strip_y,"YID/I");
    outtree2->Branch("dEX",&dEX,"dEX/D");
    outtree2->Branch("dEY",&dEY,"fdEY/D");
    outtree2->Branch("E1",&E1,"E1/D");
    outtree2->Branch("E2",&E2,"E2/D");
    outtree2->Branch("dEX_T",&dEX_T,"dEX_T/D");
    outtree2->Branch("dEY_T",&dEY_T,"dEY_T/D");
    outtree2->Branch("E1_T",&E1_T,"E1_T/D");
    outtree2->Branch("E2_T",&E2_T,"E2_T/D");
    outtree2->Branch("telID",&telID,"telID/I");


    outtree3->Branch("rf0",&rf0,"rf0/D");
    outtree3->Branch("ppaca_anode",&ppaca_anode,"ppaca_anode/D");
    outtree3->Branch("ppaca_x",&ppaca_x,"ppaca_x/D");
    outtree3->Branch("ppaca_y",&ppaca_y,"ppaca_y/D");
    outtree3->Branch("ppaca_z",&ppaca_z,"ppaca_z/D");
    outtree3->Branch("ppacb_anode",&ppacb_anode,"ppacb_anode/D");
    outtree3->Branch("ppacb_x",&ppacb_x,"ppacb_x/D");
    outtree3->Branch("ppacb_y",&ppacb_y,"ppacb_y/D");
    outtree3->Branch("ppacb_z",&ppacb_z,"ppacb_z/D");

    outtree3->Branch("XID",&strip_x,"XID/I");
    outtree3->Branch("YID",&strip_y,"YID/I");
    outtree3->Branch("dEX",&dEX,"dEX/D");
    outtree3->Branch("dEY",&dEY,"fdEY/D");
    outtree3->Branch("E1",&E1,"E1/D");
    outtree3->Branch("E2",&E2,"E2/D");
    outtree3->Branch("dEX_T",&dEX_T,"dEX_T/D");
    outtree3->Branch("dEY_T",&dEY_T,"dEY_T/D");
    outtree3->Branch("E1_T",&E1_T,"E1_T/D");
    outtree3->Branch("E2_T",&E2_T,"E2_T/D");
    outtree3->Branch("telID",&telID,"telID/I");


    outtree4->Branch("rf0",&rf0,"rf0/D");
    outtree4->Branch("ppaca_anode",&ppaca_anode,"ppaca_anode/D");
    outtree4->Branch("ppaca_x",&ppaca_x,"ppaca_x/D");
    outtree4->Branch("ppaca_y",&ppaca_y,"ppaca_y/D");
    outtree4->Branch("ppaca_z",&ppaca_z,"ppaca_z/D");
    outtree4->Branch("ppacb_anode",&ppacb_anode,"ppacb_anode/D");
    outtree4->Branch("ppacb_x",&ppacb_x,"ppacb_x/D");
    outtree4->Branch("ppacb_y",&ppacb_y,"ppacb_y/D");
    outtree4->Branch("ppacb_z",&ppacb_z,"ppacb_z/D");

    outtree4->Branch("XID",&strip_x,"XID/I");
    outtree4->Branch("YID",&strip_y,"YID/I");
    outtree4->Branch("dEX",&dEX,"dEX/D");
    outtree4->Branch("dEY",&dEY,"fdEY/D");
    outtree4->Branch("E1",&E1,"E1/D");
    outtree4->Branch("E2",&E2,"E2/D");
    outtree4->Branch("dEX_T",&dEX_T,"dEX_T/D");
    outtree4->Branch("dEY_T",&dEY_T,"dEY_T/D");
    outtree4->Branch("E1_T",&E1_T,"E1_T/D");
    outtree4->Branch("E2_T",&E2_T,"E2_T/D");
    outtree4->Branch("telID",&telID,"telID/I");


    outtree5->Branch("rf0",&rf0,"rf0/D");
    outtree5->Branch("ppaca_anode",&ppaca_anode,"ppaca_anode/D");
    outtree5->Branch("ppaca_x",&ppaca_x,"ppaca_x/D");
    outtree5->Branch("ppaca_y",&ppaca_y,"ppaca_y/D");
    outtree5->Branch("ppaca_z",&ppaca_z,"ppaca_z/D");
    outtree5->Branch("ppacb_anode",&ppacb_anode,"ppacb_anode/D");
    outtree5->Branch("ppacb_x",&ppacb_x,"ppacb_x/D");
    outtree5->Branch("ppacb_y",&ppacb_y,"ppacb_y/D");
    outtree5->Branch("ppacb_z",&ppacb_z,"ppacb_z/D");

    outtree5->Branch("XID",&strip_x,"XID/I");
    outtree5->Branch("YID",&strip_y,"YID/I");
    outtree5->Branch("dEX",&dEX,"dEX/D");
    outtree5->Branch("dEY",&dEY,"fdEY/D");
    outtree5->Branch("E1",&E1,"E1/D");
    outtree5->Branch("E2",&E2,"E2/D");
    outtree5->Branch("dEX_T",&dEX_T,"dEX_T/D");
    outtree5->Branch("dEY_T",&dEY_T,"dEY_T/D");
    outtree5->Branch("E1_T",&E1_T,"E1_T/D");
    outtree5->Branch("E2_T",&E2_T,"E2_T/D");
    outtree5->Branch("telID",&telID,"telID/I");

    // output ROOT file setting end---------------------------

    // analysis start-----------------------------------------
    Int_t progress_tmp = 1;
    Bool_t prog = true;
    Int_t tmp_itr = 0;
    for(Int_t iEntry=0; iEntry<intree->GetEntriesFast(); ++iEntry){
      if(prog && (iEntry+1) % (Int_t)(intree->GetEntriesFast()/100) == 0){
        std::cout << iEntry << " / " << intree->GetEntriesFast() << " : " << progress_tmp << " %" << std::endl;
        progress_tmp++;
      }
      intree->GetEntry(iEntry);

      // coin process
      if(pileup->GetEntriesFast() > 0) continue;
      if(coin->GetEntriesFast() == 0) continue;

      // trigger (ppac) process
      rf0 = TMath::QuietNaN();
      ppaca_anode = TMath::QuietNaN();
      ppacb_anode = TMath::QuietNaN();

      Int_t ppaca_hit, ppacb_hit;
      Int_t ppaca_itr = 0;
      Int_t ppacb_itr = 0;

      for(Int_t i=0; i<f3appac->GetEntriesFast(); ++i){
        if(TMath::Abs(((art::TPPACData*)f3appac->At(i))->GetTAnode() - 839.0) < 19.0){
          ppaca_hit = i;
          ppaca_itr++;
        }
      }
      if(ppaca_itr == 0) continue;
      if(ppaca_itr > 1) std::cout << "warning: f3appac event is not 1 (Get last event)" << std::endl;
      ppaca_anode = ((art::TPPACData*)f3appac->At(ppaca_hit))->GetTAnode();
      ppaca_x     = ((art::TPPACData*)f3appac->At(ppaca_hit))->GetX();
      ppaca_y     = ((art::TPPACData*)f3appac->At(ppaca_hit))->GetY();
      ppaca_z     = ((art::TPPACData*)f3appac->At(ppaca_hit))->GetZ();

      for(Int_t i=0; i<f3bppac->GetEntriesFast(); ++i){
        if(TMath::Abs(((art::TPPACData*)f3bppac->At(i))->GetTAnode() - 868.0) < 16.0){
          ppacb_hit = i;
          ppacb_itr++;
        }
      }
      if(ppacb_itr == 0) continue;
      if(ppacb_itr > 1) std::cout << "warning: f3bppac event is not 1 (Get last event)" << std::endl;
      ppacb_anode = ((art::TPPACData*)f3bppac->At(ppacb_hit))->GetTAnode();
      ppacb_x     = ((art::TPPACData*)f3bppac->At(ppacb_hit))->GetX();
      ppacb_y     = ((art::TPPACData*)f3bppac->At(ppacb_hit))->GetY();
      ppacb_z     = ((art::TPPACData*)f3bppac->At(ppacb_hit))->GetZ();


      // rf0 process
      if(rf_cal_0->GetEntriesFast() == 1){
        rf0 = ((art::TTimingData*)rf_cal_0->At(0))->GetTiming();
      }else{
        std::cout << "warning: rf_cal_0 event num is not 1, continue" << std::endl;
        continue;
      }

      //==============MAIN==================
      strip_x = -1;
      strip_y = -1;
      dEX = TMath::QuietNaN();
      dEY = TMath::QuietNaN();
      E1 = TMath::QuietNaN();
      E2 = TMath::QuietNaN();
      dEX_T = TMath::QuietNaN();
      dEY_T = TMath::QuietNaN();
      E1_T = TMath::QuietNaN();
      E2_T = TMath::QuietNaN();
      telID = 0;


      if(tel1->GetEntriesFast() == 1){
        // si26a selection
        if(TMath::Abs(rf0 - 24.5) > 5. && TMath::Abs(rf0 - 76.25) > 4.75) continue;
        if(TMath::Abs((ppacb_anode - ppaca_anode) - 25.25) > 1.25) continue;

        strip_x = ((art::TTelescopeData*)tel1->At(0))->GetXID();
        strip_y = ((art::TTelescopeData*)tel1->At(0))->GetYID();
        dEX     = ((art::TTelescopeData*)tel1->At(0))->GetdEX();
        dEY     = ((art::TTelescopeData*)tel1->At(0))->GetdEY();
        E1      = ((art::TTelescopeData*)tel1->At(0))->GetEvec(0);
        E2      = ((art::TTelescopeData*)tel1->At(0))->GetEvec(1);
        dEX_T   = ((art::TTelescopeData*)tel1->At(0))->GetdEXTiming();
        dEY_T   = ((art::TTelescopeData*)tel1->At(0))->GetdEYTiming();
        E1_T    = ((art::TTelescopeData*)tel1->At(0))->GetETimingvec(0);
        E2_T    = ((art::TTelescopeData*)tel1->At(0))->GetETimingvec(1);
        telID   = ((art::TTelescopeData*)tel1->At(0))->GetID();

        outtree1->Fill();

      }
      if(tel2->GetEntriesFast() == 1){
        // si26a selection
        if(TMath::Abs(rf0 - 24.5) > 5. && TMath::Abs(rf0 - 76.25) > 4.75) continue;
        if(TMath::Abs((ppacb_anode - ppaca_anode) - 25.25) > 1.25) continue;

        strip_x = ((art::TTelescopeData*)tel2->At(0))->GetXID();
        strip_y = ((art::TTelescopeData*)tel2->At(0))->GetYID();
        dEX     = ((art::TTelescopeData*)tel2->At(0))->GetdEX();
        dEY     = ((art::TTelescopeData*)tel2->At(0))->GetdEY();
        E1      = ((art::TTelescopeData*)tel2->At(0))->GetEvec(0);
        E2      = ((art::TTelescopeData*)tel2->At(0))->GetEvec(1);
        dEX_T   = ((art::TTelescopeData*)tel2->At(0))->GetdEXTiming();
        dEY_T   = ((art::TTelescopeData*)tel2->At(0))->GetdEYTiming();
        E1_T    = ((art::TTelescopeData*)tel2->At(0))->GetETimingvec(0);
        E2_T    = ((art::TTelescopeData*)tel2->At(0))->GetETimingvec(1);
        telID   = ((art::TTelescopeData*)tel2->At(0))->GetID();

        outtree2->Fill();

      }
      if(tel3->GetEntriesFast() == 1){
        // si26a selection
        if(TMath::Abs(rf0 - 24.5) > 5. && TMath::Abs(rf0 - 76.25) > 4.75) continue;
        if(TMath::Abs((ppacb_anode - ppaca_anode) - 25.25) > 1.25) continue;

        strip_x = ((art::TTelescopeData*)tel3->At(0))->GetXID();
        strip_y = ((art::TTelescopeData*)tel3->At(0))->GetYID();
        dEX     = ((art::TTelescopeData*)tel3->At(0))->GetdEX();
        dEY     = ((art::TTelescopeData*)tel3->At(0))->GetdEY();
        E1      = ((art::TTelescopeData*)tel3->At(0))->GetEvec(0);
        E2      = ((art::TTelescopeData*)tel3->At(0))->GetEvec(1);
        dEX_T   = ((art::TTelescopeData*)tel3->At(0))->GetdEXTiming();
        dEY_T   = ((art::TTelescopeData*)tel3->At(0))->GetdEYTiming();
        E1_T    = ((art::TTelescopeData*)tel3->At(0))->GetETimingvec(0);
        E2_T    = ((art::TTelescopeData*)tel3->At(0))->GetETimingvec(1);
        telID   = ((art::TTelescopeData*)tel3->At(0))->GetID();

        outtree3->Fill();
        tmp_itr++;

      }
      if(tel4->GetEntriesFast() == 1){
        // si26a selection
        if(TMath::Abs(rf0 - 24.5) > 5. && TMath::Abs(rf0 - 76.25) > 4.75) continue;
        if(TMath::Abs((ppacb_anode - ppaca_anode) - 25.25) > 1.25) continue;

        strip_x = ((art::TTelescopeData*)tel4->At(0))->GetXID();
        strip_y = ((art::TTelescopeData*)tel4->At(0))->GetYID();
        dEX     = ((art::TTelescopeData*)tel4->At(0))->GetdEX();
        dEY     = ((art::TTelescopeData*)tel4->At(0))->GetdEY();
        E1      = ((art::TTelescopeData*)tel4->At(0))->GetEvec(0);
        E2      = ((art::TTelescopeData*)tel4->At(0))->GetEvec(1);
        dEX_T   = ((art::TTelescopeData*)tel4->At(0))->GetdEXTiming();
        dEY_T   = ((art::TTelescopeData*)tel4->At(0))->GetdEYTiming();
        E1_T    = ((art::TTelescopeData*)tel4->At(0))->GetETimingvec(0);
        E2_T    = ((art::TTelescopeData*)tel4->At(0))->GetETimingvec(1);
        telID   = ((art::TTelescopeData*)tel4->At(0))->GetID();

        outtree4->Fill();

      }
      if(tel5->GetEntriesFast() == 1){
        std::cout << "debug: itr " << tmp_itr << std::endl;
        // si26a selection
        if(TMath::Abs(rf0 - 24.5) > 5. && TMath::Abs(rf0 - 76.25) > 4.75) continue;
        if(TMath::Abs((ppacb_anode - ppaca_anode) - 25.25) > 1.25) continue;

        strip_x = ((art::TTelescopeData*)tel5->At(0))->GetXID();
        strip_y = ((art::TTelescopeData*)tel5->At(0))->GetYID();
        dEX     = ((art::TTelescopeData*)tel5->At(0))->GetdEX();
        dEY     = ((art::TTelescopeData*)tel5->At(0))->GetdEY();
        E1      = ((art::TTelescopeData*)tel5->At(0))->GetEvec(0);
        E2      = ((art::TTelescopeData*)tel5->At(0))->GetEvec(1);
        dEX_T   = ((art::TTelescopeData*)tel5->At(0))->GetdEXTiming();
        dEY_T   = ((art::TTelescopeData*)tel5->At(0))->GetdEYTiming();
        E1_T    = ((art::TTelescopeData*)tel5->At(0))->GetETimingvec(0);
        E2_T    = ((art::TTelescopeData*)tel5->At(0))->GetETimingvec(1);
        telID   = ((art::TTelescopeData*)tel5->At(0))->GetID();

        outtree5->Fill();

      }

    }

    std::cout << "======END======  (" << input << ")" << std::endl;
    std::cout << " tel1: " << outtree1->GetEntriesFast() << std::endl;
    std::cout << " tel2: " << outtree2->GetEntriesFast() << std::endl;
    std::cout << " tel3: " << outtree3->GetEntriesFast() << std::endl;
    std::cout << " tel4: " << outtree4->GetEntriesFast() << std::endl;
    std::cout << " tel5: " << outtree5->GetEntriesFast() << std::endl;

    outtree1->Write();
    fout1->Close();

    outtree2->Write();
    fout2->Close();

    outtree3->Write();
    fout3->Close();

    outtree4->Write();
    fout4->Close();

    outtree5->Write();
    fout5->Close();

    gROOT->ProcessLine(".q");
}
