void MakeSimpleRoot(TString RUNNAME, TString RUNNUM, Int_t telescopeID){
    if(telescopeID == 0 || telescopeID > 5){
      std::cerr << "ERROR: invalid telescopeID" << std::endl;
      return;
    }

    const TString ARTEMIS_WORKDIR = "/home/okawa/art_analysis/user/okawa/";
    TString TELESCOPE;
    TELESCOPE.Form("tel%d/", telescopeID);
    TString INROOT = ARTEMIS_WORKDIR + "output/artemis/artemis_" + RUNNAME + RUNNUM + ".root";
    TString OUTROOT = ARTEMIS_WORKDIR + "rootfile/" + TELESCOPE + "coin_" + RUNNAME + RUNNUM + ".root";
    std::cout << "[info] output file is " << OUTROOT.Data() << std::endl;

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
    TClonesArray *tel         = NULL;
    TClonesArray *lowgain_cal = NULL;

    intree->SetBranchAddress("single",   &single);
    intree->SetBranchAddress("coin",     &coin);
    intree->SetBranchAddress("pileup",   &pileup);
    intree->SetBranchAddress("rf_cal_0", &rf_cal_0);
    intree->SetBranchAddress("f3bppac",  &f3bppac);
    intree->SetBranchAddress("f3appac",  &f3appac);
    if(telescopeID == 1){
      intree->SetBranchAddress("tel1", &tel);
    }else if(telescopeID == 2){
      intree->SetBranchAddress("tel2", &tel);
    }else if(telescopeID == 3){
      intree->SetBranchAddress("tel3", &tel);
    }else if(telescopeID == 4){
      intree->SetBranchAddress("tel4", &tel);
    }else if(telescopeID == 5){
      intree->SetBranchAddress("tel5", &tel);
    }
    intree->SetBranchAddress("lowgain_cal",&lowgain_cal);
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
    Double_t Etotal;
    Int_t tel_ID;

    outtree->Branch("rf_cal_0.fTiming",&rf0,"rf_cal_0.fTiming/D");
    outtree->Branch("f3appac.fTAnode",&ppaca_anode,"f3appac.fTAnode/D");
    outtree->Branch("f3appac.fX",&ppaca_x,"f3appac.fX/D");
    outtree->Branch("f3appac.fY",&ppaca_y,"f3appac.fY/D");
    outtree->Branch("f3appac.fZ",&ppaca_z,"f3appac.fZ/D");
    outtree->Branch("f3bppac.fTAnode",&ppacb_anode,"f3bppac.fTAnode/D");
    outtree->Branch("f3bppac.fX",&ppacb_x,"f3bppac.fX/D");
    outtree->Branch("f3bppac.fY",&ppacb_y,"f3bppac.fY/D");
    outtree->Branch("f3bppac.fZ",&ppacb_z,"f3bppac.fZ/D");

    outtree->Branch("tel.fXID",&strip_x,"tel.fXID/I");
    outtree->Branch("tel.fYID",&strip_y,"tel.fYID/I");
    outtree->Branch("tel.fdEX",&dEX,"tel.fdEX/D");
    outtree->Branch("tel.fdEY",&dEY,"tel.fdEY/D");
    outtree->Branch("tel.fE1",&E1,"tel.fE1/D");
    outtree->Branch("tel.fE2",&E2,"tel.fE2/D");
    outtree->Branch("tel.fdEX_T",&dEX_T,"tel.fdEX_T/D");
    outtree->Branch("tel.fdEY_T",&dEY_T,"tel.fdEY_T/D");
    outtree->Branch("tel.fE1_T",&E1_T,"tel.fE1_T/D");
    outtree->Branch("tel.fE2_T",&E2_T,"tel.fE2_T/D");
    outtree->Branch("tel.fEtotal",&Etotal,"tel.fEtotal/D");
    outtree->Branch("tel.fID",&tel_ID,"tel.fID/I");
    // output ROOT file setting end---------------------------

    // analysis start-----------------------------------------
    Int_t progress_tmp = 1;
    Bool_t debug = true;
    for(Int_t iEntry=0; iEntry<intree->GetEntriesFast(); ++iEntry){
      if((iEntry+1) % (Int_t)(intree->GetEntriesFast()/100) == 0){
        std::cout << "tel" << telescopeID << " " << iEntry << " / " << intree->GetEntriesFast() << " : " << progress_tmp << " %" << std::endl;
        progress_tmp++;
      }
      intree->GetEntry(iEntry);

      // event selection start--------------------------------
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
        if(TMath::Abs(((art::TPPACData*)f3appac->At(i))->GetTAnode() - 840.0) < 20.0){
          ppaca_hit = i;
          ppaca_itr++;
        }
      }
      if(ppaca_itr == 0) continue;
      if(ppaca_itr > 1) std::cout << "warning: f3appac event is not 1 (Get last event)" << std::endl;
      ppaca_anode = ((art::TPPACData*)f3appac->At(ppaca_hit))->GetTAnode();

      for(Int_t i=0; i<f3bppac->GetEntriesFast(); ++i){
        if(atoi(RUNNUM.Data()) < 249){
          if(TMath::Abs((((art::TPPACData*)f3bppac->At(i))->GetTAnode() - ppaca_anode) - 32.5) < 4.5){
            ppacb_hit = i;
            ppacb_itr++;
          }
        }else{
          if(TMath::Abs((((art::TPPACData*)f3bppac->At(i))->GetTAnode() - ppaca_anode) - 26.5) < 4.5){
            ppacb_hit = i;
            ppacb_itr++;
          }
        }
      }
      if(ppacb_itr == 0) continue;
      if(ppacb_itr > 1) std::cout << "warning: f3bppac event is not 1 (Get last event)" << std::endl;
      ppacb_anode = ((art::TPPACData*)f3bppac->At(ppacb_hit))->GetTAnode();


      // si26 process
      if(rf_cal_0->GetEntriesFast() == 1){
        rf0 = ((art::TTimingData*)rf_cal_0->At(0))->GetTiming();
      }else{
        std::cout << "warning: rf_cal_0 event num is not 1, continue" << std::endl;
        continue;
      }
      
      Double_t rf_offset = 0.0;
      if(telescopeID == 1){
        rf_offset = 2.171;
      }else if(telescopeID == 2){
        rf_offset = 2.221;
      }else if(telescopeID == 3){
        rf_offset = 2.211;
      }else if(telescopeID == 4){
        rf_offset = 2.141;
      }else if(telescopeID == 5){
        rf_offset = 2.091;
      }

      if(atoi(RUNNUM.Data()) < 249){
        if(TMath::Abs((ppacb_anode - ppaca_anode) - 31.75) > 1.25) continue;
      }else{
        if(TMath::Abs((ppacb_anode - ppaca_anode) - 25.25) > 1.25) continue;
      }
      if(TMath::Abs(rf0 - 24.0 - rf_offset) > 4.0 && TMath::Abs(rf0 - 76.0 - rf_offset) > 4.0) continue;


      // telescope process
      if(tel->GetEntriesFast() == 0) continue;

      // event selection end----------------------------------


      //main
      ppaca_x = TMath::QuietNaN();
      ppaca_y = TMath::QuietNaN();
      ppaca_z = TMath::QuietNaN();
      ppacb_x = TMath::QuietNaN();
      ppacb_y = TMath::QuietNaN();
      ppacb_z = TMath::QuietNaN();

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
      tel_ID = 0;

      ppaca_x = ((art::TPPACData*)f3appac->At(ppaca_hit))->GetX();
      ppaca_y = ((art::TPPACData*)f3appac->At(ppaca_hit))->GetY();
      ppaca_z = ((art::TPPACData*)f3appac->At(ppaca_hit))->GetZ();
      ppacb_x = ((art::TPPACData*)f3bppac->At(ppacb_hit))->GetX();
      ppacb_y = ((art::TPPACData*)f3bppac->At(ppacb_hit))->GetY();
      ppacb_z = ((art::TPPACData*)f3bppac->At(ppacb_hit))->GetZ();


      if(tel->GetEntriesFast() == 1){
        strip_x = ((art::TTelescopeData*)tel->At(0))->GetXID();
        strip_y = ((art::TTelescopeData*)tel->At(0))->GetYID();
        dEX     = ((art::TTelescopeData*)tel->At(0))->GetdEX();
        dEY     = ((art::TTelescopeData*)tel->At(0))->GetdEY();
        E1      = ((art::TTelescopeData*)tel->At(0))->GetEvec(0);
        E2      = ((art::TTelescopeData*)tel->At(0))->GetEvec(1);
        dEX_T   = ((art::TTelescopeData*)tel->At(0))->GetdEXTiming();
        dEY_T   = ((art::TTelescopeData*)tel->At(0))->GetdEYTiming();
        E1_T    = ((art::TTelescopeData*)tel->At(0))->GetETimingvec(0);
        E2_T    = ((art::TTelescopeData*)tel->At(0))->GetETimingvec(1);
        Etotal  = ((art::TTelescopeData*)tel->At(0))->GetEtotal();
        tel_ID  = ((art::TTelescopeData*)tel->At(0))->GetID();
      }else if(tel->GetEntriesFast() > 1){
        std::cout << "warning: tel" << telescopeID << " event num is not 0 or 1" << std::endl;
      }

      outtree->Fill();
    }
    // analysis end-------------------------------------------

    std::cout << "\ttel" << telescopeID << ", Entry number: " << outtree->GetEntriesFast() << std::endl;
    outtree->Write();
    fout->Close();

    gROOT->ProcessLine(".q");
}
