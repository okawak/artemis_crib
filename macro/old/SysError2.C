//void SysError(){
{
    gStyle->SetOptStat(0);
    //gStyle->SetOptFit(0);
    gStyle->SetMarkerStyle(20);
    //gStyle->SetMarkerSize(1.5);

    TString range1 = "(1800,0.,9.)";
    TString range2 = "(900,0.,9.)";
    TString range3 = "(900,0.,9.)";
    TString range4 = "(900,0.,9.)";
    TString range5 = "(900,0.,9.)";

    Double_t de = 0.5;

    gROOT->ProcessLine("zone");
    gROOT->ProcessLine("fcd 5");

    //==============================================================================
    //tel1
    TGraphErrors *g1 = new TGraphErrors();
    Int_t n1 = 0;
    for(Double_t det_ene=1.0; det_ene<25.0; det_ene+=de){
        gROOT->ProcessLine(Form("tree->Draw(\"yield.fEcm>>tel1%s\",\"abs(proton.fEtotal - %g) < 0.05 && yield.fID == 1\")", range1.Data(), det_ene));

        TH1F *h = (TH1F*)tel1->Clone("h");
    
        TSpectrum *spec = new TSpectrum(1, 1.0);
        TF1 *f = new TF1("f", "gaus(0)");

        Int_t nfound = spec->Search(h, 2, "", 0.05);
        if(nfound != 1){
            continue;
        }
        Double_t *xpeaks = spec->GetPositionX();

        f->SetRange(xpeaks[0]-0.5, xpeaks[0]+0.5);
        f->SetParameters(100, xpeaks[0], 0.2);
        h->Fit(f,"rq");
        f->Draw("same");
    
        g1->SetPoint(n1, f->GetParameter(1), f->GetParameter(2));
        g1->SetPointError(n1, 0., f->GetParError(2));

        gROOT->ProcessLine(Form("artcanvas->Print(\"figure/error2/tel1/tel1_%d.png\")",n1));
        n1++;

    }

    gROOT->ProcessLine("zone");
    g1->Draw("ap");
    gROOT->ProcessLine(Form("artcanvas->Print(\"figure/error2/tel1.png\")"));

    //==============================================================================
    //tel2
    TGraphErrors *g2 = new TGraphErrors();
    Int_t n2 = 0;
    for(Double_t det_ene=1.0; det_ene<25.0; det_ene+=de){
        gROOT->ProcessLine(Form("tree->Draw(\"yield.fEcm>>tel2%s\",\"abs(proton.fEtotal - %g) < 0.05 && yield.fID == 2\")", range2.Data(), det_ene));

        TH1F *h = (TH1F*)tel2->Clone("h");
    
        TSpectrum *spec = new TSpectrum(1, 1.0);
        TF1 *f = new TF1("f", "gaus(0)");

        Int_t nfound = spec->Search(h, 2, "", 0.05);
        if(nfound != 1){
            continue;
        }
        Double_t *xpeaks = spec->GetPositionX();

        f->SetRange(xpeaks[0]-0.5, xpeaks[0]+0.5);
        f->SetParameters(100, xpeaks[0], 0.2);
        h->Fit(f,"rq");
        f->Draw("same");
    
        g2->SetPoint(n2, f->GetParameter(1), f->GetParameter(2));
        g2->SetPointError(n2, 0., f->GetParError(2));

        gROOT->ProcessLine(Form("artcanvas->Print(\"figure/error2/tel2/tel2_%d.png\")",n2));
        n2++;

    }

    gROOT->ProcessLine("zone");
    g2->Draw("ap");
    gROOT->ProcessLine(Form("artcanvas->Print(\"figure/error2/tel2.png\")"));

    //==============================================================================
    //tel3
    TGraphErrors *g3 = new TGraphErrors();
    Int_t n3 = 0;
    for(Double_t det_ene=1.0; det_ene<25.0; det_ene+=de){
        gROOT->ProcessLine(Form("tree->Draw(\"yield.fEcm>>tel3%s\",\"abs(proton.fEtotal - %g) < 0.05 && yield.fID == 3\")", range3.Data(), det_ene));

        TH1F *h = (TH1F*)tel3->Clone("h");
    
        TSpectrum *spec = new TSpectrum(1, 1.0);
        TF1 *f = new TF1("f", "gaus(0)");

        Int_t nfound = spec->Search(h, 2, "", 0.05);
        if(nfound != 1){
            continue;
        }
        Double_t *xpeaks = spec->GetPositionX();

        f->SetRange(xpeaks[0]-0.5, xpeaks[0]+0.5);
        f->SetParameters(100, xpeaks[0], 0.2);
        h->Fit(f,"rq");
        f->Draw("same");
    
        g3->SetPoint(n3, f->GetParameter(1), f->GetParameter(2));
        g3->SetPointError(n3, 0., f->GetParError(2));

        gROOT->ProcessLine(Form("artcanvas->Print(\"figure/error2/tel3/tel3_%d.png\")",n3));
        n3++;

    }

    gROOT->ProcessLine("zone");
    g3->Draw("ap");
    gROOT->ProcessLine(Form("artcanvas->Print(\"figure/error2/tel3.png\")"));

    //==============================================================================
    //tel4
    TGraphErrors *g4 = new TGraphErrors();
    Int_t n4 = 0;
    for(Double_t det_ene=1.0; det_ene<25.0; det_ene+=de){
        gROOT->ProcessLine(Form("tree->Draw(\"yield.fEcm>>tel4%s\",\"abs(proton.fEtotal - %g) < 0.05 && yield.fID == 4\")", range4.Data(), det_ene));

        TH1F *h = (TH1F*)tel4->Clone("h");
    
        TSpectrum *spec = new TSpectrum(1, 1.0);
        TF1 *f = new TF1("f", "gaus(0)");

        Int_t nfound = spec->Search(h, 2, "", 0.05);
        if(nfound != 1){
            continue;
        }
        Double_t *xpeaks = spec->GetPositionX();

        f->SetRange(xpeaks[0]-0.5, xpeaks[0]+0.5);
        f->SetParameters(100, xpeaks[0], 0.2);
        h->Fit(f,"rq");
        f->Draw("same");
    
        g4->SetPoint(n4, f->GetParameter(1), f->GetParameter(2));
        g4->SetPointError(n4, 0., f->GetParError(2));

        gROOT->ProcessLine(Form("artcanvas->Print(\"figure/error2/tel4/tel4_%d.png\")",n4));
        n4++;

    }

    gROOT->ProcessLine("zone");
    g4->Draw("ap");
    gROOT->ProcessLine(Form("artcanvas->Print(\"figure/error2/tel4.png\")"));


    //==============================================================================
    //tel5
    TGraphErrors *g5 = new TGraphErrors();
    Int_t n5 = 0;
    for(Double_t det_ene=1.0; det_ene<25.0; det_ene+=de){
        gROOT->ProcessLine(Form("tree->Draw(\"yield.fEcm>>tel5%s\",\"abs(proton.fEtotal - %g) < 0.05 && yield.fID == 5\")", range5.Data(), det_ene));

        TH1F *h = (TH1F*)tel5->Clone("h");
    
        TSpectrum *spec = new TSpectrum(1, 1.0);
        TF1 *f = new TF1("f", "gaus(0)");

        Int_t nfound = spec->Search(h, 2, "", 0.05);
        if(nfound != 1){
            continue;
        }
        Double_t *xpeaks = spec->GetPositionX();

        f->SetRange(xpeaks[0]-0.5, xpeaks[0]+0.5);
        f->SetParameters(100, xpeaks[0], 0.2);
        h->Fit(f,"rq");
        f->Draw("same");
    
        g5->SetPoint(n5, f->GetParameter(1), f->GetParameter(2));
        g5->SetPointError(n5, 0., f->GetParError(2));

        gROOT->ProcessLine(Form("artcanvas->Print(\"figure/error2/tel5/tel5_%d.png\")",n5));
        n5++;

    }

    gROOT->ProcessLine("zone");
    g5->Draw("ap");
    gROOT->ProcessLine(Form("artcanvas->Print(\"figure/error2/tel5.png\")"));


    gROOT->ProcessLine("zone");

    TSpline3 *sp1 = new TSpline3("sp1",g1);
    TSpline3 *sp2 = new TSpline3("sp2",g2);
    TSpline3 *sp3 = new TSpline3("sp3",g3);
    TSpline3 *sp4 = new TSpline3("sp4",g4);
    TSpline3 *sp5 = new TSpline3("sp5",g5);

    TGraph *gall = new TGraph();
    Int_t N=0;
    for(Double_t val=3.0; val<8.8; val+=0.1){
        gall->SetPoint(N, val, TMath::Sqrt(sp1->Eval(val)*sp1->Eval(val) + sp2->Eval(val)*sp2->Eval(val) + sp3->Eval(val)*sp3->Eval(val) + sp4->Eval(val)*sp4->Eval(val) + sp5->Eval(val)*sp5->Eval(val)));
        N++;
    }


    g1->SetMarkerColor(kOrange);
    g2->SetMarkerColor(kBlue);
    g3->SetMarkerColor(kRed);
    g4->SetMarkerColor(kGreen);
    g5->SetMarkerColor(kMagenta);

    gall->GetXaxis()->SetLimits(3.,9.);
    gall->GetYaxis()->SetRangeUser(0.0,0.5);
    gall->Draw("ap");
    g1->Draw("p");
    g2->Draw("p");
    g3->Draw("p");
    g4->Draw("p");
    g5->Draw("p");

        TLegend *legend = new TLegend(0.72, 0.56, 0.89, 0.88);
        legend->AddEntry(gall, "sum" , "p");
        legend->AddEntry(g1, "tel1" , "pl");
        legend->AddEntry(g2, "tel2" , "pl");
        legend->AddEntry(g3, "tel3" , "pl");
        legend->AddEntry(g4, "tel4" , "pl");
        legend->AddEntry(g5, "tel5" , "pl");
        legend->SetFillColor(0);
        legend->Draw();

    gROOT->ProcessLine(Form("artcanvas->Print(\"figure/error2/all.png\")"));

    for(Double_t val=5.1; val<9.0; val+=0.2){
        std::cout << val << " " << gall->Eval(val) << std::endl;
    }

}