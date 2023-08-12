void run_MUXParamMaker(TString RUNNAME="hoge", TString RUNNUM="0000"){

  gROOT->ProcessLine(Form("add steering/calibration.yaml NAME=%s NUM=%s", RUNNAME.Data(), RUNNUM.Data()));
  art::TLoopManager::Instance()->GetLoop()->Resume();

  gROOT->ProcessLine("fcd 0");
  gROOT->ProcessLine("zone");

  //tel2_dE1
  gROOT->ProcessLine("tree->Draw(\"tel2_dE1_raw.fP1>>h1(450,300.,750.)\")");
  gROOT->ProcessLine(".x /home/okawa/art_analysis/user/okawa/macro/MUXParamMaker.C(h1, \"prm/ssd/tel2/pos/" + RUNNAME + RUNNUM + "_dE1.dat\")");
  gROOT->ProcessLine("artcanvas->Print(\"figure/calib/tel2/pos/" + RUNNAME + RUNNUM + "_dE1.png\")");

  //tel3_dE1
  gROOT->ProcessLine("tree->Draw(\"tel3_dE1_raw.fP1>>h2(500,600.,1100.)\")");
  gROOT->ProcessLine(".x /home/okawa/art_analysis/user/okawa/macro/MUXParamMaker.C(h2, \"prm/ssd/tel3/pos/" + RUNNAME + RUNNUM + "_dE1.dat\")");
  gROOT->ProcessLine("artcanvas->Print(\"figure/calib/tel3/pos/" + RUNNAME + RUNNUM + "_dE1.png\")");

  //tel4_dE1
  gROOT->ProcessLine("tree->Draw(\"tel4_dE1_raw.fP1>>h3(450,800.,1250.)\")");
  gROOT->ProcessLine(".x /home/okawa/art_analysis/user/okawa/macro/MUXParamMaker.C(h3, \"prm/ssd/tel4/pos/" + RUNNAME + RUNNUM + "_dE1.dat\")");
  gROOT->ProcessLine("artcanvas->Print(\"figure/calib/tel4/pos/" + RUNNAME + RUNNUM + "_dE1.png\")");

  //tel4_dE2
  gROOT->ProcessLine("tree->Draw(\"tel4_dE2_raw.fP1>>h4(500,1200.,1700.)\")");
  gROOT->ProcessLine(".x /home/okawa/art_analysis/user/okawa/macro/MUXParamMaker.C(h4, \"prm/ssd/tel4/pos/" + RUNNAME + RUNNUM + "_dE2.dat\")");
  gROOT->ProcessLine("artcanvas->Print(\"figure/calib/tel4/pos/" + RUNNAME + RUNNUM + "_dE2.png\")");

  //tel5_dE1
  gROOT->ProcessLine("tree->Draw(\"tel5_dE1_raw.fP1>>h5(500,1350.,1850.)\")");
  gROOT->ProcessLine(".x /home/okawa/art_analysis/user/okawa/macro/MUXParamMaker.C(h5, \"prm/ssd/tel5/pos/" + RUNNAME + RUNNUM + "_dE1.dat\")");
  gROOT->ProcessLine("artcanvas->Print(\"figure/calib/tel5/pos/" + RUNNAME + RUNNUM + "_dE1.png\")");

  //tel5_dE2
  gROOT->ProcessLine("tree->Draw(\"tel5_dE2_raw.fP1>>h6(500,1550.,2050.)\")");
  gROOT->ProcessLine(".x /home/okawa/art_analysis/user/okawa/macro/MUXParamMaker_1miss_strip.C(h6, \"prm/ssd/tel5/pos/" + RUNNAME + RUNNUM + "_dE2.dat\")");
  gROOT->ProcessLine("artcanvas->Print(\"figure/calib/tel5/pos/" + RUNNAME + RUNNUM + "_dE2.png\")");

  gROOT->ProcessLine(".q");
}
