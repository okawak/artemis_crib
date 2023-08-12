//void BGSubtraction(){
{
    gStyle->SetOptStat(0);
    gStyle->SetOptFit(0);

    TString range = "(45,0.,9.)";
    TString fit_option = "r0";
    Double_t bg_scale_factor = 4.4282141;

    gROOT->ProcessLine("zone");
    gROOT->ProcessLine("fcd 2");

    //========================================================================
    // telescope1
    gROOT->ProcessLine("fcd 2");
    gROOT->ProcessLine(Form("tree->Draw(\"yield.fEcm>>tel1_phys%s\",\"yield.fID==1\")", range.Data()));
    TH1F *hphys1 = (TH1F*)tel1_phys->Clone("hphys1");
    hphys1->Sumw2();

    gROOT->ProcessLine("fcd 3");
    gROOT->ProcessLine(Form("tree->Draw(\"yield.fEcm>>tel1_bg%s\",\"yield.fID==1\")", range.Data()));
    TH1F *hbg1 = (TH1F*)tel1_bg->Clone("hbg1");
    // process
    Double_t fit_low1 = 0.0;
    Double_t fit_high1 = 9.0;
    TF1 *f1 = new TF1("f1","([0]*(x)**[1])*(1-exp(-((x)/[2])**[3]))", fit_low1, fit_high1);
    f1->SetParameters(100.0, -2.0, 1.0, 3.0);
    hbg1->Fit(f1,fit_option.Data());

    TH1F *hfit1 = (TH1F*)tel1_bg->Clone("hfit1");
    for(Int_t i=0; i<hfit1->GetNbinsX()+1; i++){
        //std::cout << "   " << hfit1->GetBinCenter(i) << " " << hfit1->GetBinContent(i) << std::endl;
        if(hfit1->GetBinCenter(i) < fit_low1) hfit1->SetBinContent(i, 0.0);
        else hfit1->SetBinContent(i, f1->Eval(hfit1->GetBinCenter(i)));
    }
    hfit1->Sumw2();
    hfit1->Scale(bg_scale_factor);

    hbg1->Sumw2();
    hbg1->Scale(bg_scale_factor);
    Double_t fit_factor1 = f1->GetParameter(0);
    f1->SetParameter(0, fit_factor1*bg_scale_factor);

    gROOT->ProcessLine("zone");
    hphys1->Draw("hist");
    hbg1->SetLineColor(kRed);
    hbg1->Draw("same");
    f1->Draw("same");

        TLegend *legend1 = new TLegend(0.68, 0.76, 0.89, 0.88);
        legend1->AddEntry(hphys1, "physics data" , "l");
        legend1->AddEntry(hbg1, "BG data (scale)" , "l");
        legend1->AddEntry(f1, "fitting" , "l");
        legend1->SetFillColor(0);
        legend1->Draw();

    gROOT->ProcessLine("artcanvas->Print(\"figure/yield/tel1_bg_scale.png\")");

    gROOT->ProcessLine("zone");
    hbg1->Draw();
    hfit1->Draw("hist same");
    gROOT->ProcessLine("artcanvas->Print(\"figure/yield/tel1_bg_fit.png\")");


    gROOT->ProcessLine("fcd 2");
    TH1F *hsignal1 = (TH1F*)tel1_phys->Clone("hsignal1");
    //hsignal1->Add(hbg1,-1.);
    hsignal1->Add(hfit1,-1.);


    gROOT->ProcessLine("zone");
    hsignal1->Draw("");
    gROOT->ProcessLine("artcanvas->Print(\"figure/yield/tel1.png\")");

    THStack *hs1 = new THStack("hs1","hs1");
    hsignal1->SetFillColor(kRed);
    //hbg1->SetFillColor(kGreen);
    hfit1->SetFillColor(kGreen);

    //hs1->Add(hbg1,"hist");
    hs1->Add(hfit1,"hist");
    hs1->Add(hsignal1,"hist");
    
    gROOT->ProcessLine("zone");
    hs1->Draw();
    hphys1->Draw("same hist");
    gROOT->ProcessLine("artcanvas->Print(\"figure/yield/tel1_stack.png\")");



    //========================================================================
    // telescope2
    gROOT->ProcessLine("fcd 2");
    gROOT->ProcessLine(Form("tree->Draw(\"yield.fEcm>>tel2_phys%s\",\"yield.fID==2\")", range.Data()));
    TH1F *hphys2 = (TH1F*)tel2_phys->Clone("hphys2");
    hphys2->Sumw2();

    gROOT->ProcessLine("fcd 3");
    gROOT->ProcessLine(Form("tree->Draw(\"yield.fEcm>>tel2_bg%s\",\"yield.fID==2\")", range.Data()));
    TH1F *hbg2 = (TH1F*)tel2_bg->Clone("hbg2");
    // process
    Double_t fit_low2 = 0.51;
    Double_t fit_high2 = 9.0;
    TF1 *f2 = new TF1("f2","([0]*(x-0.51)**[1])*(1-exp(-((x-0.51)/[2])**[3]))", fit_low2, fit_high2);
    f2->SetParameters(100.0, -2.0, 10.0, 3.0);
    hbg2->Fit(f2,fit_option.Data());

    TH1F *hfit2 = (TH1F*)tel2_bg->Clone("hfit2");
    for(Int_t i=0; i<hfit2->GetNbinsX()+1; i++){
        if(hfit2->GetBinCenter(i) < fit_low2) hfit2->SetBinContent(i, 0.0);
        else hfit2->SetBinContent(i, f2->Eval(hfit2->GetBinCenter(i)));
        //std::cout << "   " << hfit2->GetBinCenter(i) << " " << hfit2->GetBinContent(i) << std::endl;
    }
    hfit2->Sumw2();
    hfit2->Scale(bg_scale_factor);

    hbg2->Sumw2();
    hbg2->Scale(bg_scale_factor);
    Double_t fit_factor2 = f2->GetParameter(0);
    f2->SetParameter(0, fit_factor2*bg_scale_factor);

    gROOT->ProcessLine("zone");
    hphys2->Draw("hist");
    hbg2->SetLineColor(kRed);
    hbg2->Draw("same");
    f2->Draw("same");

        TLegend *legend2 = new TLegend(0.68, 0.76, 0.89, 0.88);
        legend2->AddEntry(hphys2, "physics data" , "l");
        legend2->AddEntry(hbg2, "BG data (scale)" , "l");
        legend2->AddEntry(f2, "fitting" , "l");
        legend2->SetFillColor(0);
        legend2->Draw();

    gROOT->ProcessLine("artcanvas->Print(\"figure/yield/tel2_bg_scale.png\")");

    gROOT->ProcessLine("zone");
    hbg2->Draw();
    hfit2->Draw("hist same");
    gROOT->ProcessLine("artcanvas->Print(\"figure/yield/tel2_bg_fit.png\")");


    gROOT->ProcessLine("fcd 2");
    TH1F *hsignal2 = (TH1F*)tel2_phys->Clone("hsignal2");
    //hsignal2->Add(hbg2,-1.);
    hsignal2->Add(hfit2,-1.);


    gROOT->ProcessLine("zone");
    hsignal2->Draw("");
    gROOT->ProcessLine("artcanvas->Print(\"figure/yield/tel2.png\")");

    THStack *hs2 = new THStack("hs2","hs2");
    hsignal2->SetFillColor(kRed);
    //hbg2->SetFillColor(kGreen);
    hfit2->SetFillColor(kGreen);

    //hs2->Add(hbg2,"hist");
    hs2->Add(hfit2,"hist");
    hs2->Add(hsignal2,"hist");
    
    gROOT->ProcessLine("zone");
    hs2->Draw();
    hphys2->Draw("same hist");
    gROOT->ProcessLine("artcanvas->Print(\"figure/yield/tel2_stack.png\")");



    //========================================================================
    // telescope3
    gROOT->ProcessLine("fcd 2");
    gROOT->ProcessLine(Form("tree->Draw(\"yield.fEcm>>tel3_phys%s\",\"yield.fID==3\")", range.Data()));
    TH1F *hphys3 = (TH1F*)tel3_phys->Clone("hphys3");
    hphys3->Sumw2();

    gROOT->ProcessLine("fcd 3");
    gROOT->ProcessLine(Form("tree->Draw(\"yield.fEcm>>tel3_bg%s\",\"yield.fID==3\")", range.Data()));
    TH1F *hbg3 = (TH1F*)tel3_bg->Clone("hbg3");
    // process
    Double_t fit_low3 = 1.8;
    Double_t fit_high3 = 9.0;
    TF1 *f3 = new TF1("f3","([0]*(x-1.8)**[1])*(1-exp(-((x-1.8)/[2])**[3]))", fit_low3, fit_high3);
    f3->SetParameters(100.0, -2.0, 10.0, 3.0);
    hbg3->Fit(f3,fit_option.Data());

    TH1F *hfit3 = (TH1F*)tel3_bg->Clone("hfit3");
    for(Int_t i=0; i<hfit3->GetNbinsX()+1; i++){
        //std::cout << "   " << hfit3->GetBinCenter(i) << " " << hfit3->GetBinContent(i) << std::endl;
        if(hfit3->GetBinCenter(i) < fit_low3) hfit3->SetBinContent(i, 0.0);
        else hfit3->SetBinContent(i, f3->Eval(hfit3->GetBinCenter(i)));
    }
    hfit3->Sumw2();
    hfit3->Scale(bg_scale_factor);

    hbg3->Sumw2();
    hbg3->Scale(bg_scale_factor);
    Double_t fit_factor3 = f3->GetParameter(0);
    f3->SetParameter(0, fit_factor3*bg_scale_factor);

    gROOT->ProcessLine("zone");
    hphys3->Draw("hist");
    hbg3->SetLineColor(kRed);
    hbg3->Draw("same");
    f3->Draw("same");

        TLegend *legend3 = new TLegend(0.68, 0.76, 0.89, 0.88);
        legend3->AddEntry(hphys3, "physics data" , "l");
        legend3->AddEntry(hbg3, "BG data (scale)" , "l");
        legend3->AddEntry(f3, "fitting" , "l");
        legend3->SetFillColor(0);
        legend3->Draw();

    gROOT->ProcessLine("artcanvas->Print(\"figure/yield/tel3_bg_scale.png\")");

    gROOT->ProcessLine("zone");
    hbg3->Draw();
    hfit3->Draw("hist same");
    gROOT->ProcessLine("artcanvas->Print(\"figure/yield/tel3_bg_fit.png\")");


    gROOT->ProcessLine("fcd 2");
    TH1F *hsignal3 = (TH1F*)tel3_phys->Clone("hsignal3");
    //hsignal3->Add(hbg3,-1.);
    hsignal3->Add(hfit3,-1.);


    gROOT->ProcessLine("zone");
    hsignal3->Draw("");
    gROOT->ProcessLine("artcanvas->Print(\"figure/yield/tel3.png\")");

    THStack *hs3 = new THStack("hs3","hs3");
    hsignal3->SetFillColor(kRed);
    //hbg3->SetFillColor(kGreen);
    hfit3->SetFillColor(kGreen);

    //hs3->Add(hbg3,"hist");
    hs3->Add(hfit3,"hist");
    hs3->Add(hsignal3,"hist");
    
    gROOT->ProcessLine("zone");
    hs3->Draw();
    hphys3->Draw("same hist");
    gROOT->ProcessLine("artcanvas->Print(\"figure/yield/tel3_stack.png\")");



    //========================================================================
    // telescope4
    gROOT->ProcessLine("fcd 2");
    gROOT->ProcessLine(Form("tree->Draw(\"yield.fEcm>>tel4_phys%s\",\"yield.fID==4\")", range.Data()));
    TH1F *hphys4 = (TH1F*)tel4_phys->Clone("hphys4");
    hphys4->Sumw2();

    gROOT->ProcessLine("fcd 3");
    gROOT->ProcessLine(Form("tree->Draw(\"yield.fEcm>>tel4_bg%s\",\"yield.fID==4\")", range.Data()));
    TH1F *hbg4 = (TH1F*)tel4_bg->Clone("hbg4");
    // process
    Double_t fit_low4 = 1.2;
    Double_t fit_high4 = 9.0;
    TF1 *f4 = new TF1("f4","([0]*(x-1.2)**[1])*(1-exp(-((x-1.2)/[2])**[3]))", fit_low4, fit_high4);
    f4->SetParameters(100.0, -2.0, 10.0, 3.0);
    hbg4->Fit(f4,fit_option.Data());

    TH1F *hfit4 = (TH1F*)tel4_bg->Clone("hfit4");
    for(Int_t i=0; i<hfit4->GetNbinsX()+1; i++){
        //std::cout << "   " << hfit4->GetBinCenter(i) << " " << hfit4->GetBinContent(i) << std::endl;
        if(hfit4->GetBinCenter(i) < fit_low4) hfit4->SetBinContent(i, 0.0);
        else hfit4->SetBinContent(i, f4->Eval(hfit4->GetBinCenter(i)));
    }
    hfit4->Sumw2();
    hfit4->Scale(bg_scale_factor);

    hbg4->Sumw2();
    hbg4->Scale(bg_scale_factor);
    Double_t fit_factor4 = f4->GetParameter(0);
    f4->SetParameter(0, fit_factor4*bg_scale_factor);

    gROOT->ProcessLine("zone");
    hphys4->Draw("hist");
    hbg4->SetLineColor(kRed);
    hbg4->Draw("same");
    f4->Draw("same");

        TLegend *legend4 = new TLegend(0.68, 0.76, 0.89, 0.88);
        legend4->AddEntry(hphys4, "physics data" , "l");
        legend4->AddEntry(hbg4, "BG data (scale)" , "l");
        legend4->AddEntry(f4, "fitting" , "l");
        legend4->SetFillColor(0);
        legend4->Draw();

    gROOT->ProcessLine("artcanvas->Print(\"figure/yield/tel4_bg_scale.png\")");

    gROOT->ProcessLine("zone");
    hbg4->Draw();
    hfit4->Draw("hist same");
    gROOT->ProcessLine("artcanvas->Print(\"figure/yield/tel4_bg_fit.png\")");


    gROOT->ProcessLine("fcd 2");
    TH1F *hsignal4 = (TH1F*)tel4_phys->Clone("hsignal4");
//    hsignal4->Add(hbg4,-1.);
    hsignal4->Add(hfit4,-1.);


    gROOT->ProcessLine("zone");
    hsignal4->Draw("");
    gROOT->ProcessLine("artcanvas->Print(\"figure/yield/tel4.png\")");


    THStack *hs4 = new THStack("hs4","hs4");
    hsignal4->SetFillColor(kRed);
    //hbg4->SetFillColor(kGreen);
    hfit4->SetFillColor(kGreen);

    //hs4->Add(hbg4,"hist");
    hs4->Add(hfit4,"hist");
    hs4->Add(hsignal4,"hist");
    
    gROOT->ProcessLine("zone");
    hs4->Draw();
    hphys4->Draw("same hist");
    gROOT->ProcessLine("artcanvas->Print(\"figure/yield/tel4_stack.png\")");


    //========================================================================
    // telescope5
    gROOT->ProcessLine("fcd 2");
    gROOT->ProcessLine(Form("tree->Draw(\"yield.fEcm>>tel5_phys%s\",\"yield.fID==5\")", range.Data()));
    TH1F *hphys5 = (TH1F*)tel5_phys->Clone("hphys5");
    hphys5->Sumw2();

    gROOT->ProcessLine("fcd 3");
    gROOT->ProcessLine(Form("tree->Draw(\"yield.fEcm>>tel5_bg%s\",\"yield.fID==5\")", range.Data()));
    TH1F *hbg5 = (TH1F*)tel5_bg->Clone("hbg5");
    // process
    Double_t fit_low5 = 1.8;
    Double_t fit_high5 = 9.0;
    TF1 *f5 = new TF1("f5","([0]*(x-1.8)**[1])*(1-exp(-((x-1.8)/[2])**[3]))", fit_low5, fit_high5);
    f5->SetParameters(100.0, -2.0, 10.0, 3.0);
    hbg5->Fit(f5,fit_option.Data());

    TH1F *hfit5 = (TH1F*)tel5_bg->Clone("hfit5");
    for(Int_t i=0; i<hfit5->GetNbinsX()+1; i++){
        //std::cout << "   " << hfit5->GetBinCenter(i) << " " << hfit5->GetBinContent(i) << std::endl;
        if(hfit5->GetBinCenter(i) < fit_low5) hfit5->SetBinContent(i, 0.0);
        else hfit5->SetBinContent(i, f5->Eval(hfit5->GetBinCenter(i)));
    }
    hfit5->Sumw2();
    hfit5->Scale(bg_scale_factor);

    hbg5->Sumw2();
    hbg5->Scale(bg_scale_factor);
    Double_t fit_factor5 = f5->GetParameter(0);
    f5->SetParameter(0, fit_factor5*bg_scale_factor);

    gROOT->ProcessLine("zone");
    hphys5->Draw("hist");
    hbg5->SetLineColor(kRed);
    hbg5->Draw("same");
    f5->Draw("same");

        TLegend *legend5 = new TLegend(0.68, 0.76, 0.89, 0.88);
        legend5->AddEntry(hphys5, "physics data" , "l");
        legend5->AddEntry(hbg5, "BG data (scale)" , "l");
        legend5->AddEntry(f5, "fitting" , "l");
        legend5->SetFillColor(0);
        legend5->Draw();

    gROOT->ProcessLine("artcanvas->Print(\"figure/yield/tel5_bg_scale.png\")");

    gROOT->ProcessLine("zone");
    hbg5->Draw();
    hfit5->Draw("hist same");
    gROOT->ProcessLine("artcanvas->Print(\"figure/yield/tel5_bg_fit.png\")");


    gROOT->ProcessLine("fcd 2");
    TH1F *hsignal5 = (TH1F*)tel5_phys->Clone("hsignal5");
    //hsignal5->Add(hbg5,-1.);
    hsignal5->Add(hfit5,-1.);


    gROOT->ProcessLine("zone");
    hsignal5->Draw("");
    gROOT->ProcessLine("artcanvas->Print(\"figure/yield/tel5.png\")");

    THStack *hs5 = new THStack("hs5","hs5");
    hsignal5->SetFillColor(kRed);
    //hbg5->SetFillColor(kGreen);
    hfit5->SetFillColor(kGreen);

    //hs5->Add(hbg5,"hist");
    hs5->Add(hfit5,"hist");
    hs5->Add(hsignal5,"hist");
    
    gROOT->ProcessLine("zone");
    hs5->Draw();
    hphys5->Draw("same hist");
    gROOT->ProcessLine("artcanvas->Print(\"figure/yield/tel5_stack.png\")");

    //========================================================================
    // all

    TH1F *hall = (TH1F*)hsignal1->Clone("hall");
    hall->Add(hsignal2);
    hall->Add(hsignal3);
    hall->Add(hsignal4);
    hall->Add(hsignal5);

    gROOT->ProcessLine("zone");
    hall->Draw();
    gROOT->ProcessLine("artcanvas->Print(\"figure/yield/all.png\")");

    gROOT->ProcessLine("zone");
    hall->GetXaxis()->SetRangeUser(5.0,9.0);
    hall->Draw();
    TF1 *zero = new TF1("zero","pol0",5.0,9.0);
    zero->SetParameter(0,0.);
    zero->Draw("same");
    gROOT->ProcessLine(Form("artcanvas->Print(\"figure/yield/all_highE.png\")"));



}