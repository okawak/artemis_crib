{
    gStyle->SetOptStat(0);
    gROOT->ProcessLine("zone");

    // tel1
    gROOT->ProcessLine("fcd 0");
    gROOT->ProcessLine("tree->SetAlias(\"tel1_proton\",\"(abs(sqrt(tel1.fdEY * tel1.fEtotal) - 5.3) < 0.5) && (abs(tel1.GetETimingvec(0) + 172.5) < 27.5) && tel1.GetEvec(0) > 0.1\")");
    gROOT->ProcessLine("tree->Draw(\"tel1.fEtotal>>phys_E(50,0.,25.)\",\"tel1_proton\")");

    gROOT->ProcessLine("fcd 5");
    gROOT->ProcessLine("tree->SetAlias(\"tel1_proton\",\"(abs(sqrt(tel1.fdEY * tel1.fEtotal) - 5.3) < 0.5) && (abs(tel1.GetETimingvec(0) + 172.5) < 27.5) && tel1.GetEvec(0) > 0.1\")");
    gROOT->ProcessLine("tree->Draw(\"tel1.fEtotal>>bg_E(50,0.,25.)\",\"tel1_proton\")");
    gROOT->ProcessLine("bg_E->Scale(4.4282141)");
    gROOT->ProcessLine("bg_E->SetLineColor(kRed)");

    gROOT->ProcessLine("fcd 0");
    gROOT->ProcessLine("zone");
    gROOT->ProcessLine("phys_E->Draw()");

    gROOT->ProcessLine("fcd 5");
    gROOT->ProcessLine("bg_E->Draw(\"same\")");

    TLegend *legend1 = new TLegend(0.7, 0.78, 0.89, 0.88);
    legend1->AddEntry(phys_E, "physics data" , "l");
    legend1->AddEntry(bg_E, "BG data" , "l");
    legend1->SetFillColor(0);
    gROOT->ProcessLine("legend1->Draw(\"same\")");
    legend1->Draw();

    gROOT->ProcessLine("artcanvas->Print(\"figure/eventselection/tel1.png\")");


    // tel2
    gROOT->ProcessLine("fcd 1");
    gROOT->ProcessLine("tree->SetAlias(\"tel2_proton\",\"abs(sqrt(tel2.fdEY * tel2.fEtotal) - 5.45) < 0.55 && tel2.GetEvec(0) > 0.1 && abs(tel2.GetETimingvec(0) + 170.0) < 50.0\")");
    gROOT->ProcessLine("tree->Draw(\"tel2.fEtotal>>phys_E(50,0.,25.)\",\"tel2_proton\")");

    gROOT->ProcessLine("fcd 6");
    gROOT->ProcessLine("tree->SetAlias(\"tel2_proton\",\"abs(sqrt(tel2.fdEY * tel2.fEtotal) - 5.45) < 0.55 && tel2.GetEvec(0) > 0.1 && abs(tel2.GetETimingvec(0) + 170.0) < 50.0\")");
    gROOT->ProcessLine("tree->Draw(\"tel2.fEtotal>>bg_E(50,0.,25.)\",\"tel2_proton\")");
    gROOT->ProcessLine("bg_E->Scale(4.4282141)");
    gROOT->ProcessLine("bg_E->SetLineColor(kRed)");

    gROOT->ProcessLine("fcd 1");
    gROOT->ProcessLine("zone");
    gROOT->ProcessLine("phys_E->Draw()");

    gROOT->ProcessLine("fcd 6");
    gROOT->ProcessLine("bg_E->Draw(\"same\")");

    TLegend *legend2 = new TLegend(0.7, 0.78, 0.89, 0.88);
    legend2->AddEntry(phys_E, "physics data" , "l");
    legend2->AddEntry(bg_E, "BG data" , "l");
    legend2->SetFillColor(0);
    gROOT->ProcessLine("legend2->Draw(\"same\")");
    legend2->Draw();


    gROOT->ProcessLine("artcanvas->Print(\"figure/eventselection/tel2.png\")");


    // tel3
    gROOT->ProcessLine("fcd 2");
    gROOT->ProcessLine("tree->SetAlias(\"tel3_proton\",\"abs(sqrt(tel3.fdEY * tel3.fEtotal) - 7.7) < 1.0 && tel3.GetEvec(0) > 0.1 && abs(tel3.GetETimingvec(0) + 190.0) < 50.0\")");
    gROOT->ProcessLine("tree->Draw(\"tel3.fEtotal>>phys_E(50,0.,25.)\",\"tel3_proton\")");

    gROOT->ProcessLine("fcd 7");
    gROOT->ProcessLine("tree->SetAlias(\"tel3_proton\",\"abs(sqrt(tel3.fdEY * tel3.fEtotal) - 7.7) < 1.0 && tel3.GetEvec(0) > 0.1 && abs(tel3.GetETimingvec(0) + 190.0) < 50.0\")");
    gROOT->ProcessLine("tree->Draw(\"tel3.fEtotal>>bg_E(50,0.,25.)\",\"tel3_proton\")");
    gROOT->ProcessLine("bg_E->Scale(4.4282141)");
    gROOT->ProcessLine("bg_E->SetLineColor(kRed)");

    gROOT->ProcessLine("fcd 2");
    gROOT->ProcessLine("zone");
    gROOT->ProcessLine("phys_E->Draw()");

    gROOT->ProcessLine("fcd 7");
    gROOT->ProcessLine("bg_E->Draw(\"same\")");

    TLegend *legend3 = new TLegend(0.7, 0.78, 0.89, 0.88);
    legend3->AddEntry(phys_E, "physics data" , "l");
    legend3->AddEntry(bg_E, "BG data" , "l");
    legend3->SetFillColor(0);
    gROOT->ProcessLine("legend3->Draw(\"same\")");
    legend3->Draw();


    gROOT->ProcessLine("artcanvas->Print(\"figure/eventselection/tel3.png\")");


    // tel4
    gROOT->ProcessLine("fcd 3");
    gROOT->ProcessLine("tree->SetAlias(\"tel4_proton\",\"( (abs(sqrt(tel4.fdE * tel4.fEtotal) - 2.5) < 1.0) || (tel4.fdE < 0.1 && tel4.fEtotal > 4.0) ) && abs(tel4.GetETimingvec(0) + 190.0) < 30.0\")");
    gROOT->ProcessLine("tree->Draw(\"tel4.fEtotal>>phys_E(50,0.,25.)\",\"tel4_proton\")");

    gROOT->ProcessLine("fcd 8");
    gROOT->ProcessLine("tree->SetAlias(\"tel4_proton\",\"( (abs(sqrt(tel4.fdE * tel4.fEtotal) - 2.5) < 1.0) || (tel4.fdE < 0.1 && tel4.fEtotal > 4.0) ) && abs(tel4.GetETimingvec(0) + 190.0) < 30.0\")");
    gROOT->ProcessLine("tree->Draw(\"tel4.fEtotal>>bg_E(50,0.,25.)\",\"tel4_proton\")");
    gROOT->ProcessLine("bg_E->Scale(4.4282141)");
    gROOT->ProcessLine("bg_E->SetLineColor(kRed)");

    gROOT->ProcessLine("fcd 3");
    gROOT->ProcessLine("zone");
    gROOT->ProcessLine("phys_E->Draw()");

    gROOT->ProcessLine("fcd 8");
    gROOT->ProcessLine("bg_E->Draw(\"same\")");

    TLegend *legend4 = new TLegend(0.7, 0.78, 0.89, 0.88);
    legend4->AddEntry(phys_E, "physics data" , "l");
    legend4->AddEntry(bg_E, "BG data" , "l");
    legend4->SetFillColor(0);
    gROOT->ProcessLine("legend4->Draw(\"same\")");
    legend4->Draw();


    gROOT->ProcessLine("artcanvas->Print(\"figure/eventselection/tel4.png\")");



    // tel5
    gROOT->ProcessLine("fcd 4");
    gROOT->ProcessLine("tree->SetAlias(\"tel5_proton\",\"( (abs(sqrt(tel5.fdE * tel5.fEtotal) - 2.9) < 0.7) || (tel5.fdE < 0.1 && tel5.fEtotal > 8.0) ) && abs(tel5.GetETimingvec(0) + 190.0) < 30.0\")");
    gROOT->ProcessLine("tree->Draw(\"tel5.fEtotal>>phys_E(50,0.,25.)\",\"tel5_proton\")");

    gROOT->ProcessLine("fcd 9");
    gROOT->ProcessLine("tree->SetAlias(\"tel5_proton\",\"( (abs(sqrt(tel5.fdE * tel5.fEtotal) - 2.9) < 0.7) || (tel5.fdE < 0.1 && tel5.fEtotal > 8.0) ) && abs(tel5.GetETimingvec(0) + 190.0) < 30.0\")");
    gROOT->ProcessLine("tree->Draw(\"tel5.fEtotal>>bg_E(50,0.,25.)\",\"tel5_proton\")");
    gROOT->ProcessLine("bg_E->Scale(4.4282141)");
    gROOT->ProcessLine("bg_E->SetLineColor(kRed)");

    gROOT->ProcessLine("fcd 4");
    gROOT->ProcessLine("zone");
    gROOT->ProcessLine("phys_E->Draw()");

    gROOT->ProcessLine("fcd 9");
    gROOT->ProcessLine("bg_E->Draw(\"same\")");

    TLegend *legend5 = new TLegend(0.7, 0.78, 0.89, 0.88);
    legend5->AddEntry(phys_E, "physics data" , "l");
    legend5->AddEntry(bg_E, "BG data" , "l");
    legend5->SetFillColor(0);
    gROOT->ProcessLine("legend5->Draw(\"same\")");
    legend5->Draw();


    gROOT->ProcessLine("artcanvas->Print(\"figure/eventselection/tel5.png\")");




}