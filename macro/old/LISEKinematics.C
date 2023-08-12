{
    TString file_angle      = "macro/txt/si26ap_kin_angle.txt";
    TString file_energy     = "macro/txt/si26ap_kin_energy.txt";
    TString file_rutherford = "macro/txt/si26aa_kin_rutherford.txt";

    TGraph *g_angle_h = new TGraph(file_angle.Data(), "%lg %*lg %lg");
    TGraph *g_angle_p = new TGraph(file_angle.Data(), "%lg %lg %*lg");

    gROOT->ProcessLine("zone");
    g_angle_h->SetTitle("LISE++;CM angle [deg];LAB angle [deg]");
    g_angle_h->SetLineColor(kRed);
    g_angle_h->SetLineWidth(2);
    g_angle_h->GetXaxis()->SetLimits(0.0, 180.0);
    g_angle_h->GetYaxis()->SetRangeUser(0.0, 180.0);
    g_angle_h->Draw("al");

    g_angle_p->SetLineColor(kBlue);
    g_angle_p->SetLineWidth(2);
    g_angle_p->Draw("l");

        TLegend *legend = new TLegend(0.68, 0.80, 0.89, 0.88);
        legend->AddEntry(g_angle_h, "proton" , "l");
        legend->AddEntry(g_angle_p, "29P" , "l");
        legend->SetFillColor(0);
        legend->Draw();

    gROOT->ProcessLine("artcanvas->Print(\"figure/kinematics/si26ap_angle.png\")");




    TGraph *g_energy_h = new TGraph(file_energy.Data(), "%*lg %*lg %lg %lg");
    TGraph *g_energy_p = new TGraph(file_energy.Data(), "%lg %lg %*lg %*lg");

    gROOT->ProcessLine("zone");
    g_energy_h->SetTitle("LISE++;LAB angle [deg];LAB Energy [MeV/u]");
    g_energy_h->SetLineColor(kRed);
    g_energy_h->SetLineWidth(2);
    g_energy_h->GetXaxis()->SetLimits(0.0, 180.0);
    g_energy_h->GetYaxis()->SetRangeUser(0.0, 25.0);
    g_energy_h->Draw("al");

    g_energy_p->SetLineColor(kBlue);
    g_energy_p->SetLineWidth(2);
    g_energy_p->Draw("l");

        TLegend *legend2 = new TLegend(0.68, 0.80, 0.89, 0.88);
        legend2->AddEntry(g_energy_h, "proton" , "l");
        legend2->AddEntry(g_energy_p, "29P" , "l");
        legend2->SetFillColor(0);
        legend2->Draw();

    gROOT->ProcessLine("artcanvas->Print(\"figure/kinematics/si26ap_energy.png\")");




    TGraph *g_rutherford_cm  = new TGraph(file_rutherford.Data(), "%lg %lg %*lg %*lg %*lg %*lg %*lg %*lg %*lg %*lg");
    TGraph *g_rutherford_a1  = new TGraph(file_rutherford.Data(), "%*lg %*lg %*lg %*lg %*lg %*lg %lg %lg %*lg %*lg");
    TGraph *g_rutherford_a2  = new TGraph(file_rutherford.Data(), "%*lg %*lg %*lg %*lg %*lg %*lg %*lg %*lg %lg %lg");
    TGraph *g_rutherford_si1 = new TGraph(file_rutherford.Data(), "%*lg %*lg %lg %lg %*lg %*lg %*lg %*lg %*lg %*lg");
    TGraph *g_rutherford_si2 = new TGraph(file_rutherford.Data(), "%*lg %*lg %*lg %*lg %lg %lg %*lg %*lg %*lg %*lg");

    gROOT->ProcessLine("zone");
    gPad->SetLogy(1);
    g_rutherford_cm->SetTitle("LISE++;(CM and LAB) angle [deg];cross section [mb/sr]");
    g_rutherford_cm->SetLineColor(kBlack);
    g_rutherford_cm->SetLineWidth(2);
    g_rutherford_cm->GetXaxis()->SetLimits(0.0, 180.0);
    g_rutherford_cm->GetYaxis()->SetRangeUser(0.0, 1.0e+12);
    g_rutherford_cm->Draw("al");

    g_rutherford_a1->SetLineColor(kRed);
    g_rutherford_a1->SetLineWidth(2);
    g_rutherford_a1->Draw("l");
    g_rutherford_a2->SetLineColor(kRed);
    g_rutherford_a2->SetLineWidth(2);
    g_rutherford_a2->Draw("l");

    g_rutherford_si1->SetLineColor(kBlue);
    g_rutherford_si1->SetLineWidth(2);
    g_rutherford_si1->Draw("l");
    g_rutherford_si2->SetLineColor(kBlue);
    g_rutherford_si2->SetLineWidth(2);
    g_rutherford_si2->Draw("l");

        TLegend *legend3 = new TLegend(0.68, 0.76, 0.89, 0.88);
        legend3->AddEntry(g_rutherford_cm, "CM system" , "l");
        legend3->AddEntry(g_rutherford_a1, "alpha (LAB)" , "l");
        legend3->AddEntry(g_rutherford_si1, "26Si (LAB)" , "l");
        legend3->SetFillColor(0);
        legend3->Draw();

    gROOT->ProcessLine("artcanvas->Print(\"figure/kinematics/si26aa_rutherford.png\")");


}