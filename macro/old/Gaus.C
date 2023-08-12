void Usage()
{
    std::cout << std::endl;
    std::cout << "Usage: Gaus(TH1* h1=NULL, TString prm_dir=\"default\", TString fig_dir=\"default\", Double_t width=1.0, Double_t ref=0.0)" << std::endl;
    std::cout << "\th1      : hist name" << std::endl;
    std::cout << "\tprm_dir : absolute path for the parameter file (if default, not created)" << std::endl;
    std::cout << "\tfig_dir : absolute path for the figure file (if default, not created)" << std::endl;
    std::cout << "\twidth   : width for the gaus fitting (peak +/- width)" << std::endl;
    std::cout << "\tref     : value to distingish the parameter (if you need)" << std::endl;
}


void Gaus(TH1* h1=NULL, TString prm_dir="default", TString fig_dir="default", Double_t width=1.0, Double_t ref=0.0)
{
    if(!h1){
        std::cout << "[Error 15 line in Gaus.C] no TH1 hist" << std::endl;
        Usage();
        return;
    }

    Bool_t make_param=true;
    Bool_t make_figure=true;
    if(prm_dir == "default") make_param=false;
    if(fig_dir == "default") make_figure=false;

    Int_t bin_min = h1->FindBin(h1->GetXaxis()->GetXmin());
    Int_t bin_max = h1->FindBin(h1->GetXaxis()->GetXmax());
    if(h1->Integral(bin_min, bin_max) < 10){
        std::cout << "[Error 28 line in Gaus.C] too small entries" << std::endl;
        return;
    }

    TSpectrum *spec = new TSpectrum(1, 1.0);
    TF1 *f = new TF1("f", "gaus(0)");

    Int_t nfound = spec->Search(h1, 2, "", 0.05);
    if(nfound != 1){
        std::cout << "[Error 37 line in Gaus.C] no peaks" << std::endl;
        return;
    }

    gROOT->ProcessLine("zone");
    h1->Draw();

    Double_t *xpeaks = spec->GetPositionX();
    if(h1->GetXaxis()->GetXmin() > xpeaks[0]-width){
        f->SetRange(h1->GetXaxis()->GetXmin(), xpeaks[0]+width);
    }else if(h1->GetXaxis()->GetXmax() < xpeaks[0]+width){
        f->SetRange(xpeaks[0]-width, h1->GetXaxis()->GetXmax());
    }else{
        f->SetRange(xpeaks[0]-width, xpeaks[0]+width);
    }

    f->SetParameters(100, xpeaks[0], 50.0);
    f->SetParLimits(2,0,4000);
    h1->Fit(f,"rq");
    f->Draw("same");

    if(f->GetParameter(1) < h1->GetXaxis()->GetXmin() || h1->GetXaxis()->GetXmax() < f->GetParameter(1)){
        std::cout << "[Error 59 line in Gaus.C] not succeed in the fit" << std::endl;
        return;
    }

    if(f->GetParError(1) > 100.0){
        std::cout << "[Error 64 line in Gaus.C] not succeed in the fit" << std::endl;
        return;
    }

    if(make_figure){
        gROOT->ProcessLine(Form("artcanvas->Print(\"%s\")", fig_dir.Data()));
    }

    if(make_param){
        std::ofstream fout(prm_dir.Data());
        std::cout << "[Info] " << prm_dir << " is created" << std::endl;
        fout << "# This file is created from Gaus.C" << endl;
        fout << "# peak mean, peak mean err, ref (if you need)" << endl;

        fout << f->GetParameter(1) << " " << f->GetParError(1) << " " << ref << endl;

        fout.close();
    }

}