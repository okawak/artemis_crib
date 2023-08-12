{
    gROOT->ProcessLine("fcd 0");
    gROOT->ProcessLine("zone");
    //gROOT->ProcessLine("lgy");

    gROOT->ProcessLine("tree->Draw(\"rf_cal_0.fTiming>>rf0(1000,0.,120.)\")");
    gROOT->ProcessLine("tree->Draw(\"rf_cal_0.fTiming:(f3bppac.fTAnode-f3appac.fTAnode)>>PI(150,20.,35., 1000,0.,120.)\",\"\",\"colz\")");

    tree->SetAlias("tel1_cut", "tel1.fID == 1");
    tree->SetAlias("tel2_cut", "tel2.fID == 2");
    tree->SetAlias("tel3_cut", "tel3.fID == 3");
    tree->SetAlias("tel4_cut", "tel4.fID == 4");
    tree->SetAlias("tel5_cut", "tel5.fID == 5");
    

    gROOT->ProcessLine("tree->Draw(\"rf_cal_0.fTiming>>rf0_tel1(1000,0.,120.)\",\"tel1_cut\")");
    gROOT->ProcessLine("tree->Draw(\"rf_cal_0.fTiming:(f3bppac.fTAnode-f3appac.fTAnode)>>PI_tel1(150,20.,35., 1000,0.,120.)\",\"tel1_cut\",\"colz\")");

    gROOT->ProcessLine("tree->Draw(\"rf_cal_0.fTiming>>rf0_tel2(1000,0.,120.)\",\"tel2_cut\")");
    gROOT->ProcessLine("tree->Draw(\"rf_cal_0.fTiming:(f3bppac.fTAnode-f3appac.fTAnode)>>PI_tel2(150,20.,35., 1000,0.,120.)\",\"tel2_cut\",\"colz\")");

    gROOT->ProcessLine("tree->Draw(\"rf_cal_0.fTiming>>rf0_tel3(1000,0.,120.)\",\"tel3_cut\")");
    gROOT->ProcessLine("tree->Draw(\"rf_cal_0.fTiming:(f3bppac.fTAnode-f3appac.fTAnode)>>PI_tel3(150,20.,35., 1000,0.,120.)\",\"tel3_cut\",\"colz\")");

    gROOT->ProcessLine("tree->Draw(\"rf_cal_0.fTiming>>rf0_tel4(1000,0.,120.)\",\"tel4_cut\")");
    gROOT->ProcessLine("tree->Draw(\"rf_cal_0.fTiming:(f3bppac.fTAnode-f3appac.fTAnode)>>PI_tel4(150,20.,35., 1000,0.,120.)\",\"tel4_cut\",\"colz\")");

    gROOT->ProcessLine("tree->Draw(\"rf_cal_0.fTiming>>rf0_tel5(1000,0.,120.)\",\"tel5_cut\")");
    gROOT->ProcessLine("tree->Draw(\"rf_cal_0.fTiming:(f3bppac.fTAnode-f3appac.fTAnode)>>PI_tel5(150,20.,35., 1000,0.,120.)\",\"tel5_cut\",\"colz\")");

    // for Al peak
    //TF1 *f = new TF1("f1","gaus",62.,65.);
    //rf0_tel1->GetXaxis()->SetRangeUser(54.,70.);
    //rf0_tel1->Fit(f,"r");

    //rf0_tel2->GetXaxis()->SetRangeUser(54.,70.);
    //rf0_tel2->Fit(f,"r");

    //rf0_tel3->GetXaxis()->SetRangeUser(54.,70.);
    //rf0_tel3->Fit(f,"r");

    //rf0_tel4->GetXaxis()->SetRangeUser(54.,70.);
    //rf0_tel4->Fit(f,"r");

    //rf0_tel5->GetXaxis()->SetRangeUser(54.,70.);
    //rf0_tel5->Fit(f,"r");

    // for Si peak
    TF1 *f = new TF1("f","gaus",78.,81.);
    rf0_tel1->GetXaxis()->SetRangeUser(72.,90.);
    rf0_tel1->Fit(f,"r");

    rf0_tel2->GetXaxis()->SetRangeUser(72.,90.);
    rf0_tel2->Fit(f,"r");

    rf0_tel3->GetXaxis()->SetRangeUser(72.,90.);
    rf0_tel3->Fit(f,"r");

    rf0_tel4->GetXaxis()->SetRangeUser(72.,90.);
    rf0_tel4->Fit(f,"r");

    rf0_tel5->GetXaxis()->SetRangeUser(72.,90.);
    rf0_tel5->Fit(f,"r");


    // beam single
    gROOT->ProcessLine("fcd 1");
    gROOT->ProcessLine("zone");
    //gROOT->ProcessLine("lgy");

    gROOT->ProcessLine("tree->Draw(\"rf_cal_0.fTiming>>rf0(1000,0.,120.)\")");
    gROOT->ProcessLine("tree->Draw(\"rf_cal_0.fTiming:(f3bppac.fTAnode-f3appac.fTAnode)>>PI(150,20.,35., 1000,0.,120.)\",\"\",\"colz\")");

    TF1 *fsingle = new TF1("fsingle","gaus",76.,79.);
    rf0->GetXaxis()->SetRangeUser(70.,88.);
    rf0->Fit(fsingle,"r");
}