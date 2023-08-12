{
    Double_t energy[9] = {60.0, 65.5, 70.0, 75.0, 80.0, 85.0, 90.0, 95.0, 100.0};
    Double_t cs[9]     = {4.14e+1, 2.45e+2, 4.14e+2, 5.55e+2, 6.75e+2, 7.76e+2, 8.64e+2, 9.38e+2, 1.00e+3};

    for(Int_t i=0; i<9; i++) cs[i] *= 0.001;

    gROOT->ProcessLine("zone");
    gROOT->ProcessLine("lgy");
    TGraph *g = new TGraph(9,energy, cs);
    TSpline3 *sp = new TSpline3("sp", g);
    g->GetXaxis()->SetLimits(50.0, 100.0);
    g->GetYaxis()->SetRangeUser(0.01, 1.1);
    g->SetLineColor(kRed);
    g->SetLineWidth(2);
    g->Draw("ap");
    //sp->GetXaxis()->SetLimits(50.0, 100.0);
    //sp->GetYaxis()->SetRangeUser(0.001, 1.1);
    sp->SetLineColor(kRed);
    sp->SetLineWidth(2);
    sp->Draw("same");
    gROOT->ProcessLine("artcanvas->Print(\"c1.png\")");

}