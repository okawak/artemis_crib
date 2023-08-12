void PPACLineCalibration(TH2* h2=NULL, const Int_t PPACID=0, const Double_t x_off=0.0, const Double_t y_off=0.0, const Int_t x_ref=0){

  const TString ARTEMIS_WORKDIR = "/home/okawa/art_analysis/user/okawa";
  const TString output_fig_base = ARTEMIS_WORKDIR + "/figure/calib/ppac";
  const Double_t width = 7.0;

  if(!h2 || PPACID == 0){
    std::cout << "PPAC Line calibration" << std::endl;
    std::cout << "Usage: PPACLineCalibration(TH2* h2=NULL, const Int_t PPACID=0, const Double_t x_off=0.0, const Double_t y_off=0.0, const Int_t x_ref=0\");" << std::endl;
    std::cout << "\th2         : PPAC x vs y histogram" << std::endl;
    std::cout << "\tPPACID     : CRIB PPAC Number" << std::endl;
    std::cout << "\tx_off      : x offset at alpha calibration" << std::endl;
    std::cout << "\ty_off      : y offset at alpha calibration" << std::endl;
    std::cout << "\tx_ref      : has x reflection" << std::endl;
    return;
  }
  Int_t sgn;
  if(x_ref == 0){ sgn = 1; }
  else{ sgn = -1; }

  Double_t kx, ky;
  if(PPACID == 2){
    kx = 1.256;
    ky = 1.256;
  }else if(PPACID == 3){
    kx = 1.264;
    ky = 1.253;
  }else if(PPACID == 7){
    kx = 1.240;
    ky = 1.242;
  }else if(PPACID == 8){
    kx = 1.241;
    ky = 1.233;
  }else if(PPACID == 9){
    kx = 1.257;
    ky = 1.257;
  }else{
    std::cout << "--ERROR: Invalid PPACID" << std::endl;
    return;
  }

  Int_t first_x = h2->GetYaxis()->FindBin(-width);
  Int_t last_x  = h2->GetYaxis()->FindBin(width);
  Int_t first_y = h2->GetXaxis()->FindBin(-width);
  Int_t last_y  = h2->GetXaxis()->FindBin(width);

  TH1 *h1x = h2->ProjectionX("hx", first_x, last_x);
  h1x->SetAxisRange(-width, width);
  TH1 *h1y = h2->ProjectionY("hy", first_y, last_y);
  h1y->SetAxisRange(-width, width);

  Double_t *xpeak, *ypeak;
  Int_t nfound_x, nfound_y;
  TSpectrum *s_x = new TSpectrum(1);
  nfound_x = s_x->Search(h1x, 1, "", 0.01);
  TSpectrum *s_y = new TSpectrum(1);
  nfound_y = s_y->Search(h1y, 1, "", 0.01);
  if(nfound_x != 1 || nfound_y != 1){
      std::cout << "--ERROR: cannot find 1 peak ( found " << nfound_x << " and " << nfound_y << "peaks" << std::endl;
      return;
  }
  xpeak = s_x->GetPositionX();
  ypeak = s_y->GetPositionX();
  
  TF1 *fx = new TF1("fx","gaus(0)");
  fx->SetRange(xpeak[0]-3.0, xpeak[0]+3.0);
  fx->SetParameters(100, xpeak[0], 3);
  fx->SetParLimits(2, 0, 100);
  
  gROOT->ProcessLine("zone");
  h1x->Draw("hist e");
  h1x->Fit(fx, "rq");
  fx->Draw("same");
  gROOT->ProcessLine(Form("artcanvas->Print(\"%s/ppac#%d_x.png\")",output_fig_base.Data(), PPACID));
  
  TF1 *fy = new TF1("fy","gaus(0)");
  fy->SetRange(ypeak[0]-3.0, ypeak[0]+3.0);
  fy->SetParameters(100, ypeak[0], 3);
  fy->SetParLimits(2, 0, 100);
  
  gROOT->ProcessLine("zone");
  h1y->Draw("hist e");
  h1y->Fit(fy, "rq");
  fy->Draw("same");
  gROOT->ProcessLine(Form("artcanvas->Print(\"%s/ppac#%d_y.png\")",output_fig_base.Data(), PPACID));
  
  std::cout << "center position: (" << fx->GetParameter(1) << ", " << fy->GetParameter(1) << ")" << std::endl;
  std::cout << "move parameters: (" << sgn*(fx->GetParameter(1)-x_off)*2.0/kx << ", " << (fy->GetParameter(1)-y_off)*2.0/ky << ")" << std::endl;

}