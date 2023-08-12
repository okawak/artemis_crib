{
   gROOT->ProcessLine("fcd 0");
   gROOT->ProcessLine("zone");

   //telescope1
   gROOT->ProcessLine("tree->SetAlias(\"tel1dEdE\",\"tel1_dE1_cal.fID >=0 && tel1_dE2_cal.fID >=0 && tel1_dE1_cal.fCharge>0 && tel1_dE2_cal.fCharge>0\")");

   gROOT->ProcessLine("tree->Draw(\"tel1_dE2_cal.fTiming:tel1_dE1_cal.fTiming>>(200,0.,1000., 200,0.,1000.,)\",\"tel1dEdE\",\"colz\")");
   gROOT->ProcessLine("artcanvas->Print(\"/home/crib/art_analysis/user/develop/figure/si26a/validtime/tel1_dEdE_2dim.png\")");

   gROOT->ProcessLine("tree->Draw(\"tel1_dE1_cal.fTiming - tel1_dE2_cal.fTiming>>(1000,-1000.,1000.)\",\"tel1dEdE\")");
   gROOT->ProcessLine("artcanvas->Print(\"/home/crib/art_analysis/user/develop/figure/si26a/validtime/tel1_dEdE.png\")");


   gROOT->ProcessLine("tree->SetAlias(\"tel1dEE\",\"tel1_dE2_cal.fID >=0 && tel1_E_cal.fID >=0 && tel1_dE2_cal.fCharge>0 && tel1_E_cal.fCharge>0\")");

   gROOT->ProcessLine("tree->Draw(\"tel1_E_cal.fTiming:tel1_dE2_cal.fTiming>>(200,0.,1300., 200,0.,1300.,)\",\"tel1dEE\",\"colz\")");
   gROOT->ProcessLine("artcanvas->Print(\"/home/crib/art_analysis/user/develop/figure/si26a/validtime/tel1_dEE_2dim.png\")");

   gROOT->ProcessLine("tree->Draw(\"tel1_dE2_cal.fTiming - tel1_E_cal.fTiming>>(1000,-1000.,1000.)\",\"tel1dEE\")");
   gROOT->ProcessLine("artcanvas->Print(\"/home/crib/art_analysis/user/develop/figure/si26a/validtime/tel1_dEE.png\")");


   //telescope2
   gROOT->ProcessLine("tree->SetAlias(\"tel2dEdE\",\"tel2_dE1_cal.fID >=0 && tel2_dE2_cal.fID >=0 && tel2_dE1_cal.fCharge>0 && tel2_dE2_cal.fCharge>0\")");

   gROOT->ProcessLine("tree->Draw(\"tel2_dE2_cal.fTiming:tel2_dE1_cal.fTiming>>(200,0.,1000., 200,0.,1000.,)\",\"tel2dEdE\",\"colz\")");
   gROOT->ProcessLine("artcanvas->Print(\"/home/crib/art_analysis/user/develop/figure/si26a/validtime/tel2_dEdE_2dim.png\")");

   gROOT->ProcessLine("tree->Draw(\"tel2_dE1_cal.fTiming - tel2_dE2_cal.fTiming>>(1300,-1000.,1300.)\",\"tel2dEdE\")");
   gROOT->ProcessLine("artcanvas->Print(\"/home/crib/art_analysis/user/develop/figure/si26a/validtime/tel2_dEdE.png\")");


   gROOT->ProcessLine("tree->SetAlias(\"tel2dEE\",\"tel2_dE2_cal.fID >=0 && tel2_E_cal.fID >=0 && tel2_dE2_cal.fCharge>0 && tel2_E_cal.fCharge>0\")");

   gROOT->ProcessLine("tree->Draw(\"tel2_E_cal.fTiming:tel2_dE2_cal.fTiming>>(200,0.,1000., 200,0.,1000.,)\",\"tel2dEE\",\"colz\")");
   gROOT->ProcessLine("artcanvas->Print(\"/home/crib/art_analysis/user/develop/figure/si26a/validtime/tel2_dEE_2dim.png\")");

   gROOT->ProcessLine("tree->Draw(\"tel2_dE2_cal.fTiming - tel2_E_cal.fTiming>>(1000,-1000.,1000.)\",\"tel2dEE\")");
   gROOT->ProcessLine("artcanvas->Print(\"/home/crib/art_analysis/user/develop/figure/si26a/validtime/tel2_dEE.png\")");



   //telescope3
   gROOT->ProcessLine("tree->SetAlias(\"tel3dEdE\",\"tel3_dE1_cal.fID >=0 && tel3_dE2_cal.fID >=0 && tel3_dE1_cal.fCharge>0 && tel3_dE2_cal.fCharge>0\")");

   gROOT->ProcessLine("tree->Draw(\"tel3_dE2_cal.fTiming:tel3_dE1_cal.fTiming>>(200,0.,1000., 200,0.,1000.,)\",\"tel3dEdE\",\"colz\")");
   gROOT->ProcessLine("artcanvas->Print(\"/home/crib/art_analysis/user/develop/figure/si26a/validtime/tel3_dEdE_2dim.png\")");

   gROOT->ProcessLine("tree->Draw(\"tel3_dE1_cal.fTiming - tel3_dE2_cal.fTiming>>(1300,-1000.,1300.)\",\"tel3dEdE\")");
   gROOT->ProcessLine("artcanvas->Print(\"/home/crib/art_analysis/user/develop/figure/si26a/validtime/tel3_dEdE.png\")");


   gROOT->ProcessLine("tree->SetAlias(\"tel3dEE\",\"tel3_dE2_cal.fID >=0 && tel3_E_cal.fID >=0 && tel3_dE2_cal.fCharge>0 && tel3_E_cal.fCharge>0\")");

   gROOT->ProcessLine("tree->Draw(\"tel3_E_cal.fTiming:tel3_dE2_cal.fTiming>>(200,0.,1000., 200,0.,1000.,)\",\"tel3dEE\",\"colz\")");
   gROOT->ProcessLine("artcanvas->Print(\"/home/crib/art_analysis/user/develop/figure/si26a/validtime/tel3_dEE_2dim.png\")");

   gROOT->ProcessLine("tree->Draw(\"tel3_dE2_cal.fTiming - tel3_E_cal.fTiming>>(1000,-1000.,1000.)\",\"tel3dEE\")");
   gROOT->ProcessLine("artcanvas->Print(\"/home/crib/art_analysis/user/develop/figure/si26a/validtime/tel3_dEE.png\")");



   //telescope4
   gROOT->ProcessLine("tree->SetAlias(\"tel4dEdE\",\"tel4_dE1_cal.fID >=0 && tel4_dE2_cal.fID >=0 && tel4_dE1_cal.fCharge>0 && tel4_dE2_cal.fCharge>0\")");

   gROOT->ProcessLine("tree->Draw(\"tel4_dE2_cal.fTiming:tel4_dE1_cal.fTiming>>(200,0.,1000., 200,0.,1000.,)\",\"tel4dEdE\",\"colz\")");
   gROOT->ProcessLine("artcanvas->Print(\"/home/crib/art_analysis/user/develop/figure/si26a/validtime/tel4_dEdE_2dim.png\")");

   gROOT->ProcessLine("tree->Draw(\"tel4_dE1_cal.fTiming - tel4_dE2_cal.fTiming>>(1300,-1000.,1300.)\",\"tel4dEdE\")");
   gROOT->ProcessLine("artcanvas->Print(\"/home/crib/art_analysis/user/develop/figure/si26a/validtime/tel4_dEdE.png\")");


   gROOT->ProcessLine("tree->SetAlias(\"tel4dEE\",\"tel4_dE2_cal.fID >=0 && tel4_E_cal.fID >=0 && tel4_dE2_cal.fCharge>0 && tel4_E_cal.fCharge>0\")");

   gROOT->ProcessLine("tree->Draw(\"tel4_E_cal.fTiming:tel4_dE2_cal.fTiming>>(200,0.,1000., 200,0.,1000.,)\",\"tel4dEE\",\"colz\")");
   gROOT->ProcessLine("artcanvas->Print(\"/home/crib/art_analysis/user/develop/figure/si26a/validtime/tel4_dEE_2dim.png\")");

   gROOT->ProcessLine("tree->Draw(\"tel4_dE2_cal.fTiming - tel4_E_cal.fTiming>>(1000,-1000.,1000.)\",\"tel4dEE\")");
   gROOT->ProcessLine("artcanvas->Print(\"/home/crib/art_analysis/user/develop/figure/si26a/validtime/tel4_dEE.png\")");



   //telescope5
   gROOT->ProcessLine("tree->SetAlias(\"tel5dEdE\",\"tel5_dE1_cal.fID >=0 && tel5_dE2_cal.fID >=0 && tel5_dE1_cal.fCharge>0 && tel5_dE2_cal.fCharge>0\")");

   gROOT->ProcessLine("tree->Draw(\"tel5_dE2_cal.fTiming:tel5_dE1_cal.fTiming>>(200,0.,1000., 200,0.,1000.,)\",\"tel5dEdE\",\"colz\")");
   gROOT->ProcessLine("artcanvas->Print(\"/home/crib/art_analysis/user/develop/figure/si26a/validtime/tel5_dEdE_2dim.png\")");

   gROOT->ProcessLine("tree->Draw(\"tel5_dE1_cal.fTiming - tel5_dE2_cal.fTiming>>(1300,-1000.,1300.)\",\"tel5dEdE\")");
   gROOT->ProcessLine("artcanvas->Print(\"/home/crib/art_analysis/user/develop/figure/si26a/validtime/tel5_dEdE.png\")");


   gROOT->ProcessLine("tree->SetAlias(\"tel5dEE\",\"tel5_dE2_cal.fID >=0 && tel5_E_cal.fID >=0 && tel5_dE2_cal.fCharge>0 && tel5_E_cal.fCharge>0\")");

   gROOT->ProcessLine("tree->Draw(\"tel5_E_cal.fTiming:tel5_dE2_cal.fTiming>>(200,0.,1000., 200,0.,1000.,)\",\"tel5dEE\",\"colz\")");
   gROOT->ProcessLine("artcanvas->Print(\"/home/crib/art_analysis/user/develop/figure/si26a/validtime/tel5_dEE_2dim.png\")");

   gROOT->ProcessLine("tree->Draw(\"tel5_dE2_cal.fTiming - tel5_E_cal.fTiming>>(1000,-1000.,1000.)\",\"tel5dEE\")");
   gROOT->ProcessLine("artcanvas->Print(\"/home/crib/art_analysis/user/develop/figure/si26a/validtime/tel5_dEE.png\")");



}
