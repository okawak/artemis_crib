void GausFit(TH1* h1=NULL, TString output="test", Double_t ref_energy=0.0, Double_t ref_ene_err=0.0, Double_t width=400.0)
{

    const TString ARTEMIS_WORKDIR = "/home/okawa/art_analysis/user/okawa";
    const TString output_prm = ARTEMIS_WORKDIR + "/ana/prm/" + output + ".txt";
    const TString output_fig = ARTEMIS_WORKDIR + "/figure/calib/" + output + ".png";

    if(!h1){
        std::cout << "[Error] (in " << output << ") no TH1 hist" << std::endl;
        return;
    }
    
    Int_t bin_min = h1->FindBin(h1->GetXaxis()->GetXmin());
    Int_t bin_max = h1->FindBin(h1->GetXaxis()->GetXmax());
    if(h1->Integral(bin_min, bin_max) < 10){
        std::cout << "[Error] (in " << output << ") too small entries" << std::endl;
        return;
    }

    if(output == "test"){
        std::cout << "Warning: output file name is DEFAULT" << std::endl;
    }

    TSpectrum *spec = new TSpectrum(1,1.0);
    TF1 *f = new TF1("f", "gaus(0)");

    Int_t nfound = spec->Search(h1, 2, "", 0.05);
    if(nfound != 1){
        std::cout << "[Error] (in " << output << ") no peaks" << std::endl;
        return;
    }

    gROOT->ProcessLine("zone");
    h1->Draw();

    Double_t *xpeaks = spec->GetPositionX();
    //Int_t peak_num = h1->GetBinContent(h1->GetBin(xpeaks[0]));

    if(h1->GetXaxis()->GetXmin() > xpeaks[0]-width){
        f->SetRange(h1->GetXaxis()->GetXmin(), xpeaks[0]+width);
    }else{
        f->SetRange(xpeaks[0]-width, xpeaks[0]+width);
    }

    f->SetParameters(100, xpeaks[0], 50.0);
    f->SetParLimits(2,0,4000);
    h1->Fit(f,"rq");
    f->Draw("same");

    if(f->GetParameter(1) < h1->GetXaxis()->GetXmin() || h1->GetXaxis()->GetXmax() < f->GetParameter(1)){
        std::cout << "[Error] (in " << output << ") not succeed in the fit" << std::endl;
        return;
    }

    //if(2.35 * f->GetParameter(2) / f->GetParameter(1) > 0.4){
    //    std::cout << "[Error] (in " << output << ") not succeed in the fit" << std::endl;
    //    return;
    //}

    if(f->GetParError(1) > 100.0){
        std::cout << "[Error] (in " << output << ") not succeed in the fit" << std::endl;
        return;
    }


    gROOT->ProcessLine(Form("artcanvas->Print(\"%s\")", output_fig.Data()));

    std::ofstream fout(output_prm.Data());
    std::cout << "[Info] " << output_prm << " is created" << std::endl;
    fout << "# " << output << ".txt is created from GausFit.C" << endl;
    fout << "# x, x err, y, y err" << endl;

    fout << f->GetParameter(1) << " " << f->GetParError(1) << " " << ref_energy << " " << ref_ene_err << endl;

    fout.close();
}