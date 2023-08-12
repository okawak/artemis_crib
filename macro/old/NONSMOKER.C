{
    TString file = "macro/txt/si26ap_nonsmoker.txt";

    TGraph *g = new TGraph(file.Data(), "%lg %lg");

    gROOT->ProcessLine("zone");
    gPad->SetLogx(1);
    gPad->SetLogy(1);
    g->SetTitle("NONSMOKER;center of mass energy [MeV];total cross section [barn]");
    g->SetLineColor(kRed);
    g->SetLineWidth(2);
    g->GetXaxis()->SetLimits(0.0, 25.0);
    //g->GetYaxis()->SetRangeUser(0.0, 180.0);
    g->Draw("al");

    gROOT->ProcessLine("artcanvas->Print(\"figure/kinematics/nonsmoker.png\")");

}