void MakeProtonRoot(TString Input, TString Output){ // full path

    FileStat_t info;
    if(gSystem->GetPathInfo(Input.Data(), info) != 0){
      std::cerr << "ERROR: file: '" << Input.Data() << "' does not exist." << std::endl;
      return;
    }

    // input ROOT file setting------------------------------
    TFile *fin  = TFile::Open(Input.Data());
    TTree *intree = (TTree*)fin->Get("tree");

    TClonesArray *proton = NULL;

    intree->SetBranchAddress("proton", &proton);
    // input ROOT file setting end---------------------------

    // output ROOT file setting------------------------------
    TString pwd = gSystem->pwd();
    TString target = gSystem->DirName(Output);
    if (gSystem->ChangeDirectory(target)) {
      // target directory exists
      gSystem->ChangeDirectory(pwd);
    } else {
      gSystem->mkdir(target,kTRUE);
    }
    TFile *fout = new TFile(Output.Data(),"recreate");
    TTree *outtree = new TTree("tree","tree");

    Int_t    reac_flag;
    Double_t Etotal;
    Double_t Winx;
    Double_t Winy;
    Double_t Winz;
    Double_t Detx;
    Double_t Dety;
    Double_t Detz;
    Int_t    telID;

    outtree->Branch("reac_flag",&reac_flag,"reac_flag/I");
    outtree->Branch("Etotal",&Etotal,"Etotal/D");
    outtree->Branch("Winx",&Winx,"Winx/D");
    outtree->Branch("Winy",&Winy,"Winy/D");
    outtree->Branch("Winz",&Winz,"Winz/D");
    outtree->Branch("Detx",&Detx,"Detx/D");
    outtree->Branch("Dety",&Dety,"Dety/D");
    outtree->Branch("Detz",&Detz,"Detz/D");
    outtree->Branch("telID",&telID,"telID/I");
    // output ROOT file setting end---------------------------

    Int_t progress_tmp = 1;
    Bool_t debug = true;
    for(Int_t iEntry=0; iEntry<intree->GetEntriesFast(); ++iEntry){
      if((iEntry+1) % (Int_t)(intree->GetEntriesFast()/100) == 0){
        std::cout << "tel" << ((art::TTGTIKPrepData*)proton->At(0))->GetID() << " " << iEntry << " / " << intree->GetEntriesFast() << " : " << progress_tmp << " %" << std::endl;
        progress_tmp++;
      }
      intree->GetEntry(iEntry);

      reac_flag = ((art::TTGTIKPrepData*)proton->At(0))->GetReac_flag();
      Etotal    = ((art::TTGTIKPrepData*)proton->At(0))->GetEtotal();
      Winx      = ((art::TTGTIKPrepData*)proton->At(0))->GetWinx();
      Winy      = ((art::TTGTIKPrepData*)proton->At(0))->GetWiny();
      Winz      = ((art::TTGTIKPrepData*)proton->At(0))->GetWinz();
      Detx      = ((art::TTGTIKPrepData*)proton->At(0))->GetDetx();
      Dety      = ((art::TTGTIKPrepData*)proton->At(0))->GetDety();
      Detz      = ((art::TTGTIKPrepData*)proton->At(0))->GetDetz();
      telID     = ((art::TTGTIKPrepData*)proton->At(0))->GetID();

      outtree->Fill();
    }

    outtree->Write();
    fout->Close();

    gROOT->ProcessLine(".q");
}
