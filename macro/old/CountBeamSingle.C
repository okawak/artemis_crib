void CountBeamSingle(TString RUNNAME, TString RUNNUM){

    const TString ARTEMIS_WORKDIR = "/home/okawa/art_analysis/user/okawa/";
    TString INROOT = ARTEMIS_WORKDIR + "rootfile/single/single_" + RUNNAME + RUNNUM + ".root";
    TString OUTTXT = ARTEMIS_WORKDIR + "ana/prm/single/" + RUNNAME + RUNNUM + ".txt";

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
    fout << "# " << OUTTXT << "is created from CountBeamSingle.C" << std::endl;
    fout << "# RUNNAME RUNNUM beamsingle_count" << std::endl;

    intree->SetAlias("rf","abs(rf_cal_0.fTiming - 24.0) < 4.0 || abs(rf_cal_0.fTiming - 76.0) < 4.0");
    if(atoi(RUNNUM.Data()) < 249){
      intree->SetAlias("tof","abs((f3bppac.fTAnode - f3appac.fTAnode) - 31.75) < 1.25");
    }else{
      intree->SetAlias("tof","abs((f3bppac.fTAnode - f3appac.fTAnode) - 25.25) < 1.25");
    }
    fout << RUNNAME << " " << RUNNUM << " " << intree->GetEntries("rf && tof");

    fout.close();

    gROOT->ProcessLine(".q");
}
