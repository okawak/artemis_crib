// AlphaCalibration.C
// for TH2 histogram


void AlphaCalibration(TH2* h2=NULL, TString output="/test/test.dat", const Int_t alphaID=0, const Int_t SSDID=0){

  const TString ARTEMIS_WORKDIR = "/home/okawa/art_analysis/user/okawa";
  const TString output_prm = ARTEMIS_WORKDIR + "/prm/ssd/" + output + ".dat";
  const TString output_prm2 = ARTEMIS_WORKDIR + "/ana/prm/" + output;
  const TString output_fig_base = ARTEMIS_WORKDIR + "/figure/calib/" + output;

  if(!h2){
    std::cout << "Alpha calibration" << std::endl;
    std::cout << "Usage: AlphaCalibration(TH2* h2, TString output=\"/test/test.dat, const Int_t telID=0, const Int_t alphaID=0\");" << std::endl;
    std::cout << "\th2     : create position histogram before using this" << std::endl;
    std::cout << "\toutput : the name of parameter file like 'tel1/ch2MeV_dE1', not include .dat (base prm/si26a/ssd/)" << std::endl;
    std::cout << "\talphaID: alpha-2 (4.780, 5.480, 5.795), alpha-3 (3.148, 5.462, 5.771)" << std::endl;
    std::cout << "\tSSDID  : number of line, 16:16strip, 2:E1 and E2 SSD, 1:one SSD" << std::endl;
    return;
  }

  Double_t E_alpha[3];
  if(alphaID == 2){
    E_alpha[0] = 4.780;
    E_alpha[1] = 5.480;
    E_alpha[2] = 5.795;
  }else if(alphaID == 3){
    E_alpha[0] = 3.148;
    E_alpha[1] = 5.462;
    E_alpha[2] = 5.771;
  }else{
    std::cout << "--ERROR: invalid alpha ID" << std::endl;
    return;
  }

  if(SSDID == 0){
    std::cout << "--ERROR: invalid SSDID" << std::endl;
    return;
  }

  Int_t ch_num = h2->GetNbinsX();
  if(ch_num != SSDID){
    std::cout << "--ERROR: invalid TH2 histogram (num of Xbin (" << ch_num << ") != num of ch (" << SSDID << "))" << std::endl;
    return;
  }


  if(output == "prm/test/test.dat"){
    std::cout << "Warning: output file name is DEFAULT" << std::endl;
  }

  std::ofstream fout(output_prm.Data());
  std::cout << "--Info: " << output_prm << " is created" << std::endl;
  fout << "# " << output << ".dat is created from AlphaCalibration.C" << endl;
  fout << "# offset gain" << endl;

  TSpectrum *spec = new TSpectrum(3,1.0);
  TF1 *f[3];
  for(Int_t i=0; i<3; ++i){
    TString tmp;
    tmp.Form("f[%d]",i);
    f[i] = new TF1(tmp.Data(), "gaus(0)");
  }

  for(Int_t i=0; i<ch_num; ++i){
    Double_t x[3] = {0.0};
    TH1 *h1 = h2->ProjectionY(Form("h%03d",i),i+1,i+1);
    if(!h1){
       std::cout << "--Warning: h1 is NULL (ch " << i+1 << " )" << std::endl;
       fout << "0.0 1.0" << endl;
       continue;
    }
    gROOT->ProcessLine("zone");
    h1->Draw();
    Int_t nfound = spec->Search(h1, 2, "", 0.05);
    if(nfound != 3){
      fout << "0.0 1.0" << endl;
      continue;
    }
    Double_t *xpeaks = spec->GetPositionX();
    std::sort(xpeaks, xpeaks+3);
    //std::cout << "--INFO: " << xpeaks[0] << " " << xpeaks[1] << " " << xpeaks[2] << std::endl;

    for(Int_t j=0; j<3; ++j){
        f[j]->SetRange(xpeaks[j]-30.0, xpeaks[j]+30.0);
        f[j]->SetParameters(200, xpeaks[j], 5.0);
        f[j]->SetParLimits(2,0,100);
        h1->Fit(f[j], "rq");
        x[j] = f[j]->GetParameter(1);
        f[j]->Draw("same");
    }
    //std::cout << "--INFO: " << x[0] << " " << x[1] << " " << x[2] << std::endl;
    gROOT->ProcessLine(Form("artcanvas->Print(\"%s_%d.png\")",output_fig_base.Data(),i));

    TGraphErrors *gr1 = new TGraphErrors();
    for(Int_t j=0; j<3; ++j){
        gr1->SetPoint(j, f[j]->GetParameter(1), E_alpha[j]);
        gr1->SetPointError(j, f[j]->GetParError(1), 0.0);
    }

    TString prm2_name = output_prm2 + Form("_%d.txt", i);
    std::ofstream fout2(prm2_name.Data());
    std::cout << "[Info] " << prm2_name << " is created" << std::endl;
    fout2 << "# " << output << ".txt is created from AlphaCalibration.C" << endl;
    fout2 << "# ch, ch err, energy, energy err" << endl;
    for(Int_t j=0; j<3; ++j){
        fout2 << f[j]->GetParameter(1) << " " << f[j]->GetParError(1) << " " << E_alpha[j] << " " << "0.0" << std::endl;
    }

    TF1 *line1 = new TF1("line1", "pol1");
    line1->SetParameters(1.0, 0.4);
    gr1->Fit(line1,"q");

    fout << line1->GetParameter(0) << " " << line1->GetParameter(1) << endl;

    TGraphErrors *gr2 = new TGraphErrors();
    gr2->SetMarkerStyle(8);
    gr2->SetMarkerColor(2);
    gr2->SetMarkerSize(1);
    for(Int_t j=0; j<3; ++j){
        gr2->SetPoint(j, E_alpha[j], line1->Eval(f[j]->GetParameter(1)) - E_alpha[j]);
        gr2->SetPointError(j, 0.0, TMath::Abs(line1->Eval(f[j]->GetParError(1))));
        //std::cout << "--INFO:\t" << E_alpha[j] << " " << line1->Eval(f[j]->GetParameter(1)) - E_alpha[j] << " " << line1->Eval(f[j]->GetParError(1)) << std::endl;
    }

    TF1 *line2 = new TF1("line2", "pol1");
    line2->SetParameters(0.0, 0.1);
    gr2->Fit(line2,"q");

    gROOT->ProcessLine("zone");

    gr2->Draw("ape");
    line2->Draw("same");

    gROOT->ProcessLine(Form("artcanvas->Print(\"%s_res_%d.png\")",output_fig_base.Data(),i));
    
    fout2.close();

  }

  fout.close();

  
}