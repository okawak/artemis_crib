void run_PPACLineCalibration(){
  gStyle->SetOptStat(0);

  const TString ARTEMIS_WORKDIR = "/home/okawa/art_analysis/user/okawa";

  gROOT->ProcessLine("fcd 0");
  gROOT->ProcessLine("zone");

  // F3bPPAC(#7) calib0325
  gROOT->ProcessLine("tree->Draw(\"f3bppac.fY:f3bppac.fX>>hxy(500,-50.,50., 500,-50.,50.)\",\"\",\"colz\")");
  gROOT->ProcessLine("artcanvas->Print(\"" + ARTEMIS_WORKDIR + "/figure/calib/ppac/ppac#7_f3b_xy.png\")");
  gROOT->ProcessLine(".x " + ARTEMIS_WORKDIR + "/macro/PPACLineCalibration.C(hxy,7,0.0,0.0,1)");


  // F3aPPAC(#2) calib0326
  //gROOT->ProcessLine("tree->Draw(\"f3appac.fY:f3appac.fX>>hxy(500,-50.,50., 500,-50.,50.)\",\"\",\"colz\")");
  //gROOT->ProcessLine("artcanvas->Print(\"" + ARTEMIS_WORKDIR + "/figure/calib/ppac/ppac#2_f3a_xy.png\")");
  //gROOT->ProcessLine(".x " + ARTEMIS_WORKDIR + "/macro/PPACLineCalibration.C(hxy,2,0.0,-0.51,1)");


}