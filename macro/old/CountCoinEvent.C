void CountCoinEvent(TString RUNNAME, TString RUNNUM, Int_t telescopeID){

    const TString ARTEMIS_WORKDIR = "/home/okawa/art_analysis/user/okawa/";
    TString TELESCOPE;
    TELESCOPE.Form("tel%d", telescopeID);
    TString INROOT = ARTEMIS_WORKDIR + "rootfile/" + TELESCOPE + "/coin_" + RUNNAME + RUNNUM + ".root";
    TString OUTTXT = ARTEMIS_WORKDIR + "ana/prm/coin/" + TELESCOPE + "/" + RUNNAME + RUNNUM + ".txt";

    FileStat_t info;
    if(gSystem->GetPathInfo(INROOT.Data(), info) != 0){
      std::cerr << "ERROR: file: '" << INROOT.Data() << "' does not exist." << std::endl;
      return;
    }

    // input ROOT file setting------------------------------
    TFile *fin  = TFile::Open(INROOT.Data());
    TTree *intree = (TTree*)fin->Get("tree");

    // output text file setting-----------------------------
    std::ofstream fout(OUTTXT.Data());
    std::cout << "[Info] " << OUTTXT << " is created" << std::endl;
    fout << "# " << OUTTXT << "is created from CountCoinEvent.C" << std::endl;
    fout << "# RUNNAME RUNNUM coin_count" << std::endl;
    fout << RUNNAME << " " << RUNNUM << " " << intree->GetEntriesFast();

    fout.close();

    gROOT->ProcessLine(".q");
}
