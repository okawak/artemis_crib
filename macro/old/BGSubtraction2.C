//void BGSubtraction(){
{
    gStyle->SetOptStat(0);
    gStyle->SetOptFit(0);
    gStyle->SetMarkerStyle(20);
    //gStyle->SetMarkerSize(1.5);

    TString range = "(45,0.,9.)";
    TH1F *hall = new TH1F("hall","hall",45, 0., 9.);
    //Double_t bg_scale_factor = 3108601./702468.;// 4.4252564 beam single
    //Double_t bg_scale_factor = 8510./1293.; // 6.5815932 proton coin event
    Double_t bg_scale_factor = 5941./918.; // 6.4716776 low energy proton coin event
    //Double_t bg_scale_factor = 0.0; // no background 
    Int_t loopN = 1;

    gROOT->ProcessLine("zone");


    //========================================================================
    for(Int_t i=0; i<5; i++){
        gROOT->ProcessLine("fcd 2");
        gROOT->ProcessLine(Form("tree->Draw(\"yield.fEcm>>phys%s\",\"yield.fID==%d\")", range.Data(), i+1));
        TH1F *hphys = (TH1F*)phys->Clone("hphys");
        hphys->Sumw2();

        gROOT->ProcessLine("fcd 3");
        gROOT->ProcessLine(Form("tree->Draw(\"yield.fEcm>>bg%s\",\"yield.fID==%d\")", range.Data(), i+1));
        TH1F *hbg = (TH1F*)bg->Clone("hbg");

        // process
        TH1F *hfit = (TH1F*)bg->Clone("hfit");
        Int_t N = hfit->GetNbinsX()+1;
        if(1000 < N){
            std::cout << "nbins > N" << std::endl;
            return;
        }

        Double_t binArray[1000] = {0.0};
        Double_t binArray_1[1000] = {0.0};
        Double_t binArray_2[1000] = {0.0};
        for(Int_t j=0; j<N; j++){
            binArray[j] = hfit->GetBinContent(j);
        }

        for(Int_t j=0; j<1000; j++){
            if(j==0) binArray_1[0] = binArray[0]/2.0;
            else binArray_1[j] = (binArray[j-1] + binArray[j])/2.0;
        }
        for(Int_t j=0; j<1000; j++){
            if(j==0) binArray_2[0] = binArray_1[0]/2.0;
            else binArray_2[j] = (binArray_1[j-1] + binArray_1[j])/2.0;
        }
        for(Int_t j=0; j<loopN-1; j++){
            for(Int_t k=0; k<1000; k++){
                if(k==0) binArray_1[0] = binArray_2[0]/2.0;
                else binArray_1[k] = (binArray_2[k-1] + binArray_2[k])/2.0;
            }
            for(Int_t k=0; k<1000; k++){
                if(k==0) binArray_2[0] = binArray_1[0]/2.0;
                else binArray_2[k] = (binArray_1[k-1] + binArray_1[k])/2.0;
            }
        }

        for(Int_t j=0; j<N; j++){
            hfit->SetBinContent(j, binArray_2[j+loopN]);
        }
        hfit->Sumw2();
        hfit->Scale(bg_scale_factor);

        hbg->Sumw2();
        hbg->Scale(bg_scale_factor);

        gROOT->ProcessLine("zone");
        hphys->Draw("hist");
        hbg->SetLineColor(kRed);
        hbg->Draw("same");
        hfit->SetLineColor(kGreen);
        hfit->Draw("same hist");

            TLegend *legend = new TLegend(0.68, 0.76, 0.89, 0.88);
            legend->AddEntry(hphys, "physics data" , "l");
            legend->AddEntry(hbg, "BG data (scale)" , "l");
            legend->AddEntry(hfit, "BG estimation" , "l");
            legend->SetFillColor(0);
            legend->Draw();

        gROOT->ProcessLine(Form("artcanvas->Print(\"figure/yield2/tel%d_bg_scale.png\")",i+1));

        gROOT->ProcessLine("fcd 2");
        gROOT->ProcessLine("zone");
        
        TH1F *hsignal = (TH1F*)phys->Clone("hsignal");
        hsignal->Add(hfit,-1.);

        
        gROOT->ProcessLine("zone");
        hsignal->Draw();
        gROOT->ProcessLine(Form("artcanvas->Print(\"figure/yield2/tel%d.png\")",i+1));


        hall->Add(hsignal);

        THStack *hs = new THStack("hs","hs");
        hfit->SetFillColor(kGreen);
        hsignal->SetFillColor(kRed);

        hs->Add(hfit,"hist");
        hs->Add(hsignal,"hist");
    
        gROOT->ProcessLine("zone");
        hs->Draw();
        hphys->Draw("same hist");
        gROOT->ProcessLine(Form("artcanvas->Print(\"figure/yield2/tel%d_stack.png\")",i+1));


        gROOT->ProcessLine("zone");
        hsignal->GetXaxis()->SetRangeUser(5.0,9.0);
        hsignal->Draw();
        TF1 *zero = new TF1("zero","pol0",5.0,9.0);
        zero->SetParameter(0,0.);
        zero->Draw("same");
        gROOT->ProcessLine(Form("artcanvas->Print(\"figure/yield2/tel%d_highE.png\")",i+1));

    }

    //========================================================================
    // all

    gROOT->ProcessLine("zone");
    hall->Draw();
    gROOT->ProcessLine("artcanvas->Print(\"figure/yield2/all.png\")");

    gROOT->ProcessLine("zone");
//    hall->GetXaxis()->SetRangeUser(5.0,9.0);
//    hall->Draw("E0");

    TGraphErrors *gall_raw = new TGraphErrors();
    Int_t N_raw=0;
    for(Double_t val=5.1; val<8.8; val+=0.2){
        Int_t bin = hall->FindBin(val);
        gall_raw->SetPoint(N_raw, val, hall->GetBinContent(bin));
        gall_raw->SetPointError(N_raw, 0.0, hall->GetBinError(bin));
        N_raw++;
    }

    gall_raw->GetXaxis()->SetLimits(5.0, 9.0);
    //gall_raw->GetYaxis()->SetRangeUser(-8.0,60.0);
    gall_raw->Draw("ap");
 
    TF1 *zero = new TF1("zero","pol0",5.0,9.0);
    zero->SetParameter(0,0.);
    zero->Draw("same");
    gROOT->ProcessLine(Form("artcanvas->Print(\"figure/yield2/all_highE.png\")"));


    // all error
    gROOT->ProcessLine("zone");
    TGraphErrors *gall = new TGraphErrors();
    Double_t sys_err[20] = {0.305171, 0.289693, 0.263839, 0.25067, 0.236948, 0.218858, 0.203454, 0.191851, 0.180469, 0.169055, 0.15914, 0.149818, 0.14035, 0.133373, 0.124492, 0.118131, 0.112472, 0.106934, 0.100289, 0.0956919};
    Int_t N=0;
    for(Double_t val=5.1; val<8.8; val+=0.2){
        Int_t bin = hall->FindBin(val);
        gall->SetPoint(N, val, hall->GetBinContent(bin));
        gall->SetPointError(N, sys_err[N], hall->GetBinError(bin));
        N++;
    }

    gall->GetXaxis()->SetRangeUser(5.0,9.0);
    //gall->GetYaxis()->SetRangeUser(-8.0,60.0);
    gall->Draw("ap");
    zero->Draw("same");
    gROOT->ProcessLine(Form("artcanvas->Print(\"figure/yield2/all_highE_error.png\")"));

    //==================================================================
    // cross section
    Long_t ini_beam_num = 3100000000;
    gROOT->ProcessLine("zone");
    TGraph *solid = new TGraph("macro/txt/cs.txt", "%lg %lg %*lg");
    TGraph *thick = new TGraph("macro/txt/cs.txt", "%lg %*lg %lg");
    TGraph *nonsmoker = new TGraph("macro/txt/si26ap_nonsmoker.txt", "%lg %lg");
    TGraph *nonsmoker_scale = new TGraph("macro/txt/si26ap_nonsmoker.txt", "%lg %lg");

    TSpline3 *sp_nonsmoker = new TSpline3("sp_nonsmoker",nonsmoker);

    for(Int_t i=0;i<nonsmoker_scale->GetN();i++) nonsmoker_scale->GetY()[i] *= 0.08;
    TGraphErrors *cs = new TGraphErrors();
    for(Int_t i=0; i<gall->GetN(); i++){
        Double_t x, y;
        gall->GetPoint(i, x, y);
        cs->SetPoint(i, x, 1.0e+24*y/((Double_t)ini_beam_num*solid->Eval(x)*thick->Eval(x)));
        cs->SetPointError(i, gall->GetErrorX(i), 1.0e+24*gall->GetErrorY(i)/((Double_t)ini_beam_num*solid->Eval(x)*thick->Eval(x)));
        std::cout << std::setprecision(7) <<"\t" << x << " MeV: nonsmoker: " << nonsmoker->Eval(x) << " result: " << 1.0e+24*y/((Double_t)ini_beam_num*solid->Eval(x)*thick->Eval(x)) << " +/- " << 1.0e+24*gall->GetErrorY(i)/((Double_t)ini_beam_num*solid->Eval(x)*thick->Eval(x)) << std::endl;
    }
    //Int_t Ncs=0;
    //for(Double_t val=5.1; val<8.8; val+=0.2){
    //    Int_t bin = gall->FindBin(val);
    //    cs->SetPoint(Ncs, val, gall->Eval(val));
    //    cs->SetPointError(Ncs, gall->GetErrorX(bin), gall->GetErrorY(bin));
    //    Ncs++;
    //}

    gPad->SetLogy(1);
    nonsmoker->GetXaxis()->SetRangeUser(5.0,9.0);
    //nonsmoker->GetYaxis()->SetRangeUser(-0.1,1.0);
    nonsmoker->GetYaxis()->SetRangeUser(0.001,1.0);
    nonsmoker->SetLineColor(kRed);
    nonsmoker->SetLineWidth(2);
    nonsmoker->Draw("al");

    //sp_nonsmoker->SetLineColor(kGreen);
    //sp_nonsmoker->SetLineWidth(2);
    //sp_nonsmoker->Draw("same");

    //nonsmoker_scale->SetLineColor(kBlue);
    //nonsmoker_scale->SetLineWidth(2);
    //nonsmoker_scale->Draw("l");

    //cs->GetXaxis()->SetRangeUser(5.0,9.0);
    //cs->GetYaxis()->SetRangeUser(0.001,1.0);
    //cs->Draw("ap");
    cs->Draw("p same");
    zero->Draw("same");

    TF1 *cs_fit = new TF1("cs_fit","[&](double *x, double *p){ return p[0]*sp_nonsmoker->Eval(x[0]); }",5.0,9.0,1);
    cs_fit->SetParameter(0,0.1);
    cs_fit->SetLineColor(kGreen);
    cs_fit->SetLineWidth(2);
    cs->Fit(cs_fit,"","", 6.0, 7.45);
    //cs_fit->Draw("same");

    TF1 *cs_upper = new TF1("cs_upper","[&](double *x, double *p){ return p[0]*sp_nonsmoker->Eval(x[0]); }",5.0,9.0,1);
    cs_upper->SetParameter(0, cs_fit->GetParameter(0)+3.0*cs_fit->GetParError(0));
    cs_upper->SetLineColor(kBlue);
    cs_upper->SetLineWidth(2);
    cs_upper->Draw("same");

    std::cout << std::endl;
    std::cout << "estimated factor: " << cs_fit->GetParameter(0) << std::endl;
    std::cout << "upper limit     : " << cs_upper->GetParameter(0) << std::endl;
    std::cout << std::endl;

        TLegend *legend_cs = new TLegend(0.62, 0.67, 0.89, 0.82);
        legend_cs->AddEntry(nonsmoker, "NONSMOKER" , "l");
        legend_cs->AddEntry(cs_fit, "estimated CS" , "l");
        legend_cs->AddEntry(cs_upper, "upper limit (3#sigma:99.9%)" , "l");
        legend_cs->AddEntry(cs, "experiment" , "pl");
        legend_cs->SetFillColor(0);
        legend_cs->Draw();


    //gROOT->ProcessLine(Form("comment chi2/ndf=7.786/6"));
    gROOT->ProcessLine(Form("artcanvas->Print(\"figure/yield2/cs.png\")"));

    std::cout << "==========================" << std::endl;

    TGraph *chi2_test = new TGraph();
    Int_t chi2_test_n = 0;
    TF1 *cs_obj = new TF1("cs_obj","[&](double *x, double *p){ return p[0]*sp_nonsmoker->Eval(x[0]); }",5.0,9.0,1);
    TF1 *cs_deri = new TF1("cs_deri","[&](double *x, double *p){ return (p[0]*sp_nonsmoker->Eval(x[0] + 0.05) - p[0]*sp_nonsmoker->Eval(x[0] - 0.05) )/0.1; }",5.0,9.0,1);
    TF1 *cs_upper_chi = new TF1("cs_upper_chi","[&](double *x, double *p){ return p[0]*sp_nonsmoker->Eval(x[0]); }",5.0,9.0,1);
    for(Double_t fac=0.03; fac<0.14; fac+=0.01){
        cs_obj->SetParameter(0,fac);
        Double_t cs_chi2 = 0.0;
        for(Int_t i=0; i<cs->GetN(); i++){
            Double_t x, y;
            cs->GetPoint(i, x, y);
            if(x < 6.0 || x > 7.4) continue;
            //std::cout << x << " " << cs->GetErrorX(i) << ", " << y << " " << cs->GetErrorY(i) << std::endl;

            //cs_chi2+=((cs_obj->Eval(x) - y)/(TMath::Sqrt(cs->GetErrorY(i)*cs->GetErrorY(i) + (cs_obj->Eval(x) - cs_obj->Eval(x-cs->GetErrorX(i)))*(cs_obj->Eval(x) - cs_obj->Eval(x-cs->GetErrorX(i))))))*((cs_obj->Eval(x) - y)/(TMath::Sqrt(cs->GetErrorY(i)*cs->GetErrorY(i) + (cs_obj->Eval(x) - cs_obj->Eval(x-cs->GetErrorX(i)))*(cs_obj->Eval(x) - cs_obj->Eval(x-cs->GetErrorX(i))))));
            cs_chi2+=((cs_obj->Eval(x) - y)/(TMath::Sqrt(cs->GetErrorY(i)*cs->GetErrorY(i) + (cs_deri->Eval(x) * cs->GetErrorX(i))*(cs_deri->Eval(x) * cs->GetErrorX(i)) )))* ((cs_obj->Eval(x) - y)/(TMath::Sqrt(cs->GetErrorY(i)*cs->GetErrorY(i) + (cs_deri->Eval(x) * cs->GetErrorX(i))*(cs_deri->Eval(x) * cs->GetErrorX(i)) )));
            //cs_chi2+=((cs_obj->Eval(x) - y)/(cs->GetErrorY(i)))*((cs_obj->Eval(x) - y)/(cs->GetErrorY(i)));
        }
        //std::cout << fac << " " << cs_chi2 << std::endl;
        std::cout << fac << " " << cs_chi2 - 1.440486 << std::endl;
        chi2_test->SetPoint(chi2_test_n, fac, cs_chi2);
        chi2_test_n++;
    }
    gPad->SetLogy(0);
    gROOT->ProcessLine("zone");
    chi2_test->SetMarkerColor(kRed);
    chi2_test->SetMarkerSize(0.5);
    chi2_test->Draw("ap");
    gROOT->ProcessLine(Form("artcanvas->Print(\"figure/simulation/chi2.png\")"));
 
}