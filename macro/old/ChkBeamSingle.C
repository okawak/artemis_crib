{

  gStyle->SetMarkerStyle(20);
  gStyle->SetMarkerSize(0.8);
  gStyle->SetOptStat(0);
  gStyle->SetOptFit(0);
  gROOT->ProcessLine("fcd 0");
  gROOT->ProcessLine("zone");

  tree->Draw("rf_cal_0.fTiming:(f3bppac.fTAnode - f3appac.fTAnode)>>PI_cut(150,20.,35., 1000,0.,120.)","","colz");
  tree->Draw("rf_cal_0.fTiming>>rf(200,70.,88.)","");
  //tree->Draw("rf_cal_0.fTiming>>rf2(200,20.,38.)","");

  //TF1 *f = new TF1("f", "[0]*exp(-0.5* ( (x-[1])/[2])**2) / (sqrt(2*pi)*[2]) ) + [3]*exp(-0.5* ( (x-[4])/[2])**2) / (sqrt(2*pi)*[2]) )");
  TF1 *f = new TF1("f", "[0]*TMath::Gaus(x, [1], [2], true) + [3]*TMath::Gaus(x, [4], [2], true)");
  f->SetRange(70., 88.);
  f->SetParameters(10000., 78., 5., 5000, 81.);
  f->SetParLimits(0, 0., 1.e+10);
  f->SetParLimits(2, 0., 1000.);
  f->SetParLimits(3, 0., 1.e+10);
  //f->SetParLimits(5, 0., 1000.);

  f->SetLineColor(kRed);
  rf->Sumw2();
  rf->Draw();
  rf->Fit(f,"r");

  TF1 *f1 = new TF1("f1", "gausn(0)");
  f1->SetRange(70., 88.);
  f1->SetParameters(f->GetParameter(0), f->GetParameter(1), f->GetParameter(2));
  f1->SetLineColorAlpha(kBlue, 0.3);
  f1->Draw("same");

  TF1 *f2 = new TF1("f2", "gausn(0)");
  f2->SetRange(70., 88.);
  f2->SetParameters(f->GetParameter(3), f->GetParameter(4), f->GetParameter(2));
  f2->SetLineColorAlpha(kGreen, 0.3);
  f2->Draw("same");

  gROOT->ProcessLine("artcanvas->Print(\"c1.png\")");

  gROOT->ProcessLine("zone");

  //Double_t total_number = rf->Integral(rf->FindBin(72.0), rf->FindBin(80.0)) + rf2->Integral(rf2->FindBin(20.0), rf2->FindBin(28.0));
  //std::cout << total_number << std::endl;
  std::cout << "=============================" << std::endl;
  std::cout << "integral 72 to 80" << std::endl; 
  Double_t si = f1->Integral(72.,80.) * (200./18.) * 2. ;
  Double_t al = f2->Integral(72.,80.) * (200./18.) * 2. ;
  std::cout << "\t si => " << si << std::endl;
  std::cout << "\t al => " << al << " +/- " << TMath::Sqrt(al) << std::endl;
  std::cout << "\t ratio al/(si+al) => " << al/(si+al) << std::endl;
  std::cout << "\t ratio al/(GetEntries) => " << al/3277352.0 << " +/- " << TMath::Sqrt(al)/3277352.0 << std::endl;
  std::cout << std::endl;

  TGraphErrors *g1 = new TGraphErrors(41);
  TGraphErrors *g2 = new TGraphErrors(41);
  Double_t all_event = rf->Integral(rf->FindBin(72.), rf->FindBin(80.));
  Double_t rf_cut = 76.0;
  Int_t tmp = 0;
  while(rf_cut < 80.0){
    Double_t all_cut = rf->Integral(rf->FindBin(72.), rf->FindBin(rf_cut));
    Double_t al_cut = f2->Integral(72.,rf_cut) * (200./18.);

    g1->SetPoint(tmp, rf_cut, all_cut/all_event);
    g1->SetPointError(tmp, 0.0, 0.0);
    g2->SetPoint(tmp, rf_cut, al_cut/all_cut);
    g2->SetPointError(tmp, 0.0, TMath::Sqrt(al_cut)/all_cut);

    tmp++;
    rf_cut += 0.09;
  }

  g1->GetXaxis()->SetLimits(76.,80.);
  g1->GetYaxis()->SetRangeUser(0.1,1.);
  g1->SetTitle(Form("ratio;RF [ns];ratio"));
  g1->SetMarkerColor(kRed);
  g1->Draw("ap");

  gROOT->ProcessLine(Form("lgy"));
  gROOT->ProcessLine(Form("artcanvas->Print(\"figure/beam/al/total.png\")"));

  gROOT->ProcessLine(Form("zone"));
  g2->GetXaxis()->SetLimits(76.,80.);
  g2->GetYaxis()->SetRangeUser(0.0001,0.1);
  g2->SetTitle(Form("ratio;RF [ns];ratio"));
  g2->Draw("ap");

  gROOT->ProcessLine(Form("lgy"));
  gROOT->ProcessLine(Form("artcanvas->Print(\"figure/beam/al/al.png\")"));


  std::cout << g1->Eval(79.5) << " " << g2->Eval(79.5) << std::endl;

  //std::cout << "integral 73.41 to 77.11" << std::endl; 
  //Double_t si2 = f1->Integral(73.41,77.11);
  //Double_t al2 = f2->Integral(73.41,77.11);
  //std::cout << "\t si => " << si2 << std::endl;
  //std::cout << "\t al => " << al2 << std::endl;
  //std::cout << "\t ratio al/(si+al) => " << al2/(si2+al2) << std::endl;
  //std::cout << std::endl;
  //std::cout << "ratio of all event" << std::endl;
  //std::cout << "\t (si+al 73.41 to 77.11)/(si+al 72 to 80) => " << (si2+al2)/(si+al) << std::endl;


  // for ppac tof
  //tree->Draw("(f3bppac.fTAnode - f3appac.fTAnode)>>tof(50,24.,29.)","70 < rf_cal_0.fTiming && rf_cal_0.fTiming < 80")
  //TF1 *f = new TF1("f", "[0]*TMath::Gaus(x, [1], [2], true) + [3]*TMath::Gaus(x, [4], [5], true)");
  //f->SetRange(70., 88.);
  //f->SetParameters(10000., 78., 5., 5000, 81.);
  //f->SetParLimits(0, 0., 1.e+10);
  //f->SetParLimits(2, 0., 1000.);
  //f->SetParLimits(3, 0., 1.e+10);
}
