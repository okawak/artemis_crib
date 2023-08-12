void run_AlphaCalibration(){
  const TString ARTEMIS_WORKDIR = "/home/okawa/art_analysis/user/okawa";


  gROOT->ProcessLine("fcd 0");
  gROOT->ProcessLine("zone");

  gStyle->SetOptStat(0);

//  // tel1 dEX calib0317
//  gROOT->ProcessLine("tree->Draw(\"tel1_dEX_raw.fCharge:tel1_dEX_raw.fID>>h11(16,-0.5,15.5, 300,300.,3000.)\",\"\",\"colz\")");
//  gROOT->ProcessLine("artcanvas->Print(\"" + ARTEMIS_WORKDIR + "/figure/calib/tel1/dEX_raw.png\")");
//  gROOT->ProcessLine(".x " + ARTEMIS_WORKDIR + "/macro/AlphaCalibration.C(h11, \"tel1/ch2MeV_dEX\",3,16)");
//  gROOT->ProcessLine("tree->Draw(\"tel1_dEX_cal.fCharge:tel1_dEX_cal.fID>>h16(16,-0.5,15.5, 200,2.,6.)\",\"\",\"colz\")");
//  gROOT->ProcessLine("lgz");
//  gROOT->ProcessLine("artcanvas->Print(\"" + ARTEMIS_WORKDIR + "/figure/calib/tel1/dEX_cal.png\")");
//
//  // tel1 dEY calib0310
//  gROOT->ProcessLine("tree->Draw(\"tel1_dEY_raw.fCharge:tel1_dEY_raw.fID>>h12(16,-0.5,15.5, 300,200.,1000.)\",\"\",\"colz\")");
//  gROOT->ProcessLine("artcanvas->Print(\"" + ARTEMIS_WORKDIR + "/figure/calib/tel1/dEY_raw.png\")");
//  gROOT->ProcessLine(".x " + ARTEMIS_WORKDIR + "/macro/AlphaCalibration.C(h12, \"tel1/ch2MeV_dEY\",3,16)");
//  gROOT->ProcessLine("tree->Draw(\"tel1_dEY_cal.fCharge:tel1_dEY_cal.fID>>h17(16,-0.5,15.5, 200,2.,6.)\",\"\",\"colz\")");
//  gROOT->ProcessLine("lgz");
//  gROOT->ProcessLine("artcanvas->Print(\"" + ARTEMIS_WORKDIR + "/figure/calib/tel1/dEY_cal.png\")");
//
//  // tel1 E calib0316
//  gROOT->ProcessLine("tree->Draw(\"tel1_E_raw.fCharge:tel1_E_raw.fID>>h13(2,-0.5,1.5, 300,0.,3000.)\",\"\",\"colz\")");
//  gROOT->ProcessLine("artcanvas->Print(\"" + ARTEMIS_WORKDIR + "/figure/calib/tel1/E_raw.png\")");
//  gROOT->ProcessLine(".x " + ARTEMIS_WORKDIR + "/macro/AlphaCalibration.C(h13, \"tel1/ch2MeV_E\",2,2)");
//  gROOT->ProcessLine("tree->Draw(\"tel1_E_cal.fCharge:tel1_E_cal.fID>>h18(2,-0.5,1.5, 200,4.,6.)\",\"\",\"colz\")");
//  gROOT->ProcessLine("lgz");
//  gROOT->ProcessLine("artcanvas->Print(\"" + ARTEMIS_WORKDIR + "/figure/calib/tel1/E_cal.png\")");
//
//
//  // tel2 dEX calib0317
//  gROOT->ProcessLine("tree->Draw(\"tel2_dEX_cal.fCharge:tel2_dEX_cal.fID>>h21(16,-0.5,15.5, 300,500.,3000.)\",\"\",\"colz\")");
//  gROOT->ProcessLine("artcanvas->Print(\"" + ARTEMIS_WORKDIR + "/figure/calib/tel2/dEX_raw.png\")");
//  gROOT->ProcessLine(".x " + ARTEMIS_WORKDIR + "/macro/AlphaCalibration.C(h21, \"tel2/ch2MeV_dEX\",3,16)");
//  gROOT->ProcessLine("tree->Draw(\"tel2_dEX_cal.fCharge:tel2_dEX_cal.fID>>h26(16,-0.5,15.5, 200,2.,6.)\",\"\",\"colz\")");
//  gROOT->ProcessLine("lgz");
//  gROOT->ProcessLine("artcanvas->Print(\"" + ARTEMIS_WORKDIR + "/figure/calib/tel2/dEX_cal.png\")");
//
//  // tel2 dEY calib0310
//  gROOT->ProcessLine("tree->Draw(\"tel2_dEY_raw.fCharge:tel2_dEY_raw.fID>>h22(16,-0.5,15.5, 300,200.,800.)\",\"\",\"colz\")");
//  gROOT->ProcessLine("artcanvas->Print(\"" + ARTEMIS_WORKDIR + "/figure/calib/tel2/dEY_raw.png\")");
//  gROOT->ProcessLine(".x " + ARTEMIS_WORKDIR + "/macro/AlphaCalibration.C(h22, \"tel2/ch2MeV_dEY\",3,16)");
//  gROOT->ProcessLine("tree->Draw(\"tel2_dEY_cal.fCharge:tel2_dEY_cal.fID>>h27(16,-0.5,15.5, 200,2.,6.)\",\"\",\"colz\")");
//  gROOT->ProcessLine("lgz");
//  gROOT->ProcessLine("artcanvas->Print(\"" + ARTEMIS_WORKDIR + "/figure/calib/tel2/dEY_cal.png\")");
//
//  // tel2 E calib0316
//  gROOT->ProcessLine("tree->Draw(\"tel2_E_raw.fCharge:tel2_E_raw.fID>>h23(2,-0.5,1.5, 300,0.,3000.)\",\"\",\"colz\")");
//  gROOT->ProcessLine("artcanvas->Print(\"" + ARTEMIS_WORKDIR + "/figure/calib/tel2/E_raw.png\")");
//  gROOT->ProcessLine(".x " + ARTEMIS_WORKDIR + "/macro/AlphaCalibration.C(h23, \"tel2/ch2MeV_E\",2,2)");
//  gROOT->ProcessLine("tree->Draw(\"tel2_E_cal.fCharge:tel2_E_cal.fID>>h28(2,-0.5,1.5, 200,4.,6.)\",\"\",\"colz\")");
//  gROOT->ProcessLine("lgz");
//  gROOT->ProcessLine("artcanvas->Print(\"" + ARTEMIS_WORKDIR + "/figure/calib/tel2/E_cal.png\")");
//
//
//  // tel3 dEX calib0317
//  gROOT->ProcessLine("tree->Draw(\"tel3_dEX_cal.fCharge:tel3_dEX_cal.fID>>h31(16,-0.5,15.5, 300,500.,3000.)\",\"\",\"colz\")");
//  gROOT->ProcessLine("artcanvas->Print(\"" + ARTEMIS_WORKDIR + "/figure/calib/tel3/dEX_raw.png\")");
//  gROOT->ProcessLine(".x " + ARTEMIS_WORKDIR + "/macro/AlphaCalibration.C(h31, \"tel3/ch2MeV_dEX\",3,16)");
//  gROOT->ProcessLine("tree->Draw(\"tel3_dEX_cal.fCharge:tel3_dEX_cal.fID>>h36(16,-0.5,15.5, 200,2.,6.)\",\"\",\"colz\")");
//  gROOT->ProcessLine("lgz");
//  gROOT->ProcessLine("artcanvas->Print(\"" + ARTEMIS_WORKDIR + "/figure/calib/tel3/dEX_cal.png\")");
//
//  // tel3 dEY calib0310
//  gROOT->ProcessLine("tree->Draw(\"tel3_dEY_raw.fCharge:tel3_dEY_raw.fID>>h32(16,-0.5,15.5, 200,200.,1000.)\",\"\",\"colz\")");
//  gROOT->ProcessLine("artcanvas->Print(\"" + ARTEMIS_WORKDIR + "/figure/calib/tel3/dEY_raw.png\")");
//  gROOT->ProcessLine(".x " + ARTEMIS_WORKDIR + "/macro/AlphaCalibration.C(h32, \"tel3/ch2MeV_dEY\",3,16)");
//  gROOT->ProcessLine("tree->Draw(\"tel3_dEY_cal.fCharge:tel3_dEY_cal.fID>>h37(16,-0.5,15.5, 200,2.,6.)\",\"\",\"colz\")");
//  gROOT->ProcessLine("lgz");
//  gROOT->ProcessLine("artcanvas->Print(\"" + ARTEMIS_WORKDIR + "/figure/calib/tel3/dEY_cal.png\")");
//
//  // tel3 E calib0316
//  gROOT->ProcessLine("tree->Draw(\"tel3_E_raw.fCharge:tel3_E_raw.fID>>h33(2,-0.5,1.5, 300,0.,3000.)\",\"\",\"colz\")");
//  gROOT->ProcessLine("artcanvas->Print(\"" + ARTEMIS_WORKDIR + "/figure/calib/tel3/E_raw.png\")");
//  gROOT->ProcessLine(".x " + ARTEMIS_WORKDIR + "/macro/AlphaCalibration.C(h33, \"tel3/ch2MeV_E\",2,2)");
//  gROOT->ProcessLine("tree->Draw(\"tel3_E_cal.fCharge:tel3_E_cal.fID>>h38(2,-0.5,1.5, 200,4.,6.)\",\"\",\"colz\")");
//  gROOT->ProcessLine("lgz");
//  gROOT->ProcessLine("artcanvas->Print(\"" + ARTEMIS_WORKDIR + "/figure/calib/tel3/E_cal.png\")");
//
//
//  // tel4 dEX calib0308
//  gROOT->ProcessLine("tree->Draw(\"tel4_dEX_cal.fCharge:tel4_dEX_cal.fID>>h41(16,-0.5,15.5, 200,500.,1500.)\",\"\",\"colz\")");
//  gROOT->ProcessLine("artcanvas->Print(\"" + ARTEMIS_WORKDIR + "/figure/calib/tel4/dEX_raw.png\")");
//  gROOT->ProcessLine(".x " + ARTEMIS_WORKDIR + "/macro/AlphaCalibration.C(h41, \"tel4/ch2MeV_dEX\",2,16)");
//  gROOT->ProcessLine("tree->Draw(\"tel4_dEX_cal.fCharge:tel4_dEX_cal.fID>>h46(16,-0.5,15.5, 200,4.,6.)\",\"\",\"colz\")");
//  gROOT->ProcessLine("lgz");
//  gROOT->ProcessLine("artcanvas->Print(\"" + ARTEMIS_WORKDIR + "/figure/calib/tel4/dEX_cal.png\")");
//
//  // tel4 dEY calib0308
//  gROOT->ProcessLine("tree->Draw(\"tel4_dEY_cal.fCharge:tel4_dEY_cal.fID>>h42(16,-0.5,15.5, 200,500.,1500.)\",\"\",\"colz\")");
//  gROOT->ProcessLine("artcanvas->Print(\"" + ARTEMIS_WORKDIR + "/figure/calib/tel4/dEY_raw.png\")");
//  gROOT->ProcessLine(".x " + ARTEMIS_WORKDIR + "/macro/AlphaCalibration.C(h42, \"tel4/ch2MeV_dEY\",2,16)");
//  gROOT->ProcessLine("tree->Draw(\"tel4_dEY_cal.fCharge:tel4_dEY_cal.fID>>h47(16,-0.5,15.5, 200,4.,6.)\",\"\",\"colz\")");
//  gROOT->ProcessLine("lgz");
//  gROOT->ProcessLine("artcanvas->Print(\"" + ARTEMIS_WORKDIR + "/figure/calib/tel4/dEY_cal.png\")");
//
//  // tel4 E calib0310
//  gROOT->ProcessLine("tree->Draw(\"tel4_E_raw.fCharge:tel4_E_raw.fID>>h43(2,-0.5,1.5, 200,500.,1500.)\",\"\",\"colz\")");
//  gROOT->ProcessLine("artcanvas->Print(\"" + ARTEMIS_WORKDIR + "/figure/calib/tel4/E_raw.png\")");
//  gROOT->ProcessLine(".x " + ARTEMIS_WORKDIR + "/macro/AlphaCalibration.C(h43, \"tel4/ch2MeV_E\",2,2)");
  gROOT->ProcessLine("tree->Draw(\"tel4_E_cal.fCharge:tel4_E_cal.fID>>h48(2,-0.5,1.5, 200,4.,6.)\",\"\",\"colz\")");
  gROOT->ProcessLine("lgz");
  gROOT->ProcessLine("artcanvas->Print(\"" + ARTEMIS_WORKDIR + "/figure/calib/tel4/E_cal.png\")");
//
//
//  // tel5 dEX calib0308
//  gROOT->ProcessLine("tree->Draw(\"tel5_dEX_cal.fCharge:tel5_dEX_cal.fID>>h51(16,-0.5,15.5, 100,500.,1500.)\",\"\",\"colz\")");
//  gROOT->ProcessLine("artcanvas->Print(\"" + ARTEMIS_WORKDIR + "/figure/calib/tel5/dEX_raw.png\")");
//  gROOT->ProcessLine(".x " + ARTEMIS_WORKDIR + "/macro/AlphaCalibration.C(h51, \"tel5/ch2MeV_dEX\",2,16)");
//  gROOT->ProcessLine("tree->Draw(\"tel5_dEX_cal.fCharge:tel5_dEX_cal.fID>>h56(16,-0.5,15.5, 200,4.,6.)\",\"\",\"colz\")");
//  gROOT->ProcessLine("lgz");
//  gROOT->ProcessLine("artcanvas->Print(\"" + ARTEMIS_WORKDIR + "/figure/calib/tel5/dEX_cal.png\")");
//
//  // tel5 dEY calib0308
//  gROOT->ProcessLine("tree->Draw(\"tel5_dEY_cal.fCharge:tel5_dEY_cal.fID>>h52(16,-0.5,15.5, 100,500.,1500.)\",\"\",\"colz\")");
//  gROOT->ProcessLine("artcanvas->Print(\"" + ARTEMIS_WORKDIR + "/figure/calib/tel5/dEY_raw.png\")");
//  gROOT->ProcessLine(".x " + ARTEMIS_WORKDIR + "/macro/AlphaCalibration.C(h52, \"tel5/ch2MeV_dEY\",2,16)");
//  gROOT->ProcessLine("tree->Draw(\"tel5_dEY_cal.fCharge:tel5_dEY_cal.fID>>h57(16,-0.5,15.5, 200,4.,6.)\",\"\",\"colz\")");
//  gROOT->ProcessLine("lgz");
//  gROOT->ProcessLine("artcanvas->Print(\"" + ARTEMIS_WORKDIR + "/figure/calib/tel5/dEY_cal.png\")");
//
//  // tel5 E calib0310
//  gROOT->ProcessLine("tree->Draw(\"tel5_E_raw.fCharge:tel5_E_raw.fID>>h53(2,-0.5,1.5, 200,500.,1500.)\",\"\",\"colz\")");
//  gROOT->ProcessLine("artcanvas->Print(\"" + ARTEMIS_WORKDIR + "/figure/calib/tel5/E_raw.png\")");
//  gROOT->ProcessLine(".x " + ARTEMIS_WORKDIR + "/macro/AlphaCalibration.C(h53, \"tel5/ch2MeV_E\",2,2)");
  gROOT->ProcessLine("tree->Draw(\"tel5_E_cal.fCharge:tel5_E_cal.fID>>h58(2,-0.5,1.5, 200,4.,6.)\",\"\",\"colz\")");
  gROOT->ProcessLine("lgz");
  gROOT->ProcessLine("artcanvas->Print(\"" + ARTEMIS_WORKDIR + "/figure/calib/tel5/E_cal.png\")");

//gROOT->ProcessLine(".q");

}
