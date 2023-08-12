Double_t Brho2Energy(Double_t, Double_t, Int_t);

void EnergyResolution()
{
    gStyle->SetMarkerStyle(20);
    gStyle->SetMarkerSize(1.2);

    // data input
    static const Int_t N1 = 4;
    Double_t tel1_alpha_energy[N1] = {9.873, 16.76, 18.89, 20.87};
    Double_t tel1_brho[N1]         = {0.4587, 0.58207, 0.6331, 0.666};
    Double_t tel1_sigma[N1]        = {0.092, 0.153, 0.139, 0.137};
    Double_t tel1_sigma_err[N1]    = {0.001, 0.003, 0.002, 0.003};
    Double_t tel1_brho_energy[N1]  = {0.0};
    for(Int_t i=0; i<N1; i++){
       tel1_brho_energy[i] = Brho2Energy(tel1_brho[i], 1.007825031898, 1); 
    }

    static const Int_t N2 = 3;
    Double_t tel2_alpha_energy[N2] = {9.976, 16.19, 19.1};
    Double_t tel2_brho[N2]         = {0.4580, 0.58109, 0.6335};
    Double_t tel2_sigma[N2]        = {0.076, 0.0880, 0.105};
    Double_t tel2_sigma_err[N2]    = {0.001, 0.0006, 0.003};
    Double_t tel2_brho_energy[N2]  = {0.0};
    for(Int_t i=0; i<N2; i++){
       tel2_brho_energy[i] = Brho2Energy(tel2_brho[i], 1.007825031898, 1); 
    }

    static const Int_t N3 = 3;
    Double_t tel3_alpha_energy[N3] = {9.908, 15.16, 18.5};
    Double_t tel3_brho[N3]         = {0.4580, 0.58109, 0.6335};
    Double_t tel3_sigma[N3]        = {0.063, 0.0832, 0.134};
    Double_t tel3_sigma_err[N3]    = {0.002, 0.0001, 0.002};
    Double_t tel3_brho_energy[N3]  = {0.0};
    for(Int_t i=0; i<N3; i++){
       tel3_brho_energy[i] = Brho2Energy(tel3_brho[i], 1.007825031898, 1); 
    }

    static const Int_t N4 = 4;
    Double_t tel4_alpha_energy[N4] = {5.06, 7.181, 9.382, 11.47};
    Double_t tel4_brho[N4]         = {0.35287, 0.40695, 0.4580, 0.50231};
    Double_t tel4_sigma[N4]        = {0.071, 0.0673, 0.0766, 0.0761};
    Double_t tel4_sigma_err[N4]    = {0.002, 0.0006, 0.0004, 0.0003};
    Double_t tel4_brho_energy[N4]  = {0.0};
    for(Int_t i=0; i<N4; i++){
       tel4_brho_energy[i] = Brho2Energy(tel4_brho[i], 1.007825031898, 1); 
    }

    static const Int_t N5 = 5;
    Double_t tel5_alpha_energy[N5] = {6.086, 8.024, 10.12, 12.12, 13.92};
    Double_t tel5_brho[N5]         = {0.35287, 0.40695, 0.4580, 0.50231, 0.54283};
    Double_t tel5_sigma[N5]        = {0.053, 0.0610, 0.0724, 0.0795, 0.111};
    Double_t tel5_sigma_err[N5]    = {0.001, 0.0008, 0.0004, 0.0006, 0.006};
    Double_t tel5_brho_energy[N5]  = {0.0};
    for(Int_t i=0; i<N5; i++){
       tel5_brho_energy[i] = Brho2Energy(tel5_brho[i], 1.007825031898, 1); 
    }



    // residual calculation
    TGraphErrors *g_res1 = new TGraphErrors();
    TGraphErrors *g_res2 = new TGraphErrors();
    TGraphErrors *g_res3 = new TGraphErrors();
    TGraphErrors *g_res4 = new TGraphErrors();
    TGraphErrors *g_res5 = new TGraphErrors();
    TF1 *zero = new TF1("zero","pol0",0.0, 30.0);
    zero->SetParameter(0,0.0);

    for(Int_t i=0; i<N1; i++){
        g_res1->SetPoint(i, tel1_alpha_energy[i], - (tel1_alpha_energy[i] - tel1_brho_energy[i]));
        g_res1->SetPointError(i, 0.0, tel1_sigma[i]);
    }
    for(Int_t i=0; i<N2; i++){
        g_res2->SetPoint(i, tel2_alpha_energy[i], -(tel2_alpha_energy[i] - tel2_brho_energy[i]));
        g_res2->SetPointError(i, 0.0, tel2_sigma[i]);
    }
    for(Int_t i=0; i<N3; i++){
        g_res3->SetPoint(i, tel3_alpha_energy[i], -(tel3_alpha_energy[i] - tel3_brho_energy[i]));
        g_res3->SetPointError(i, 0.0, tel3_sigma[i]);
    }
    for(Int_t i=0; i<N4; i++){
        g_res4->SetPoint(i, tel4_alpha_energy[i], -(tel4_alpha_energy[i] - tel4_brho_energy[i]));
        g_res4->SetPointError(i, 0.0, tel4_sigma[i]);
    }
    for(Int_t i=0; i<N5; i++){
        g_res5->SetPoint(i, tel5_alpha_energy[i], -(tel5_alpha_energy[i] - tel5_brho_energy[i]));
        g_res5->SetPointError(i, 0.0, tel5_sigma[i]);
    }

    g_res1->SetMarkerColor(kBlack);
    g_res1->SetLineColor(kBlack);
    g_res2->SetMarkerColor(kBlue);
    g_res2->SetLineColor(kBlue);
    g_res3->SetMarkerColor(kRed);
    g_res3->SetLineColor(kRed);
    g_res4->SetMarkerColor(kGreen);
    g_res4->SetLineColor(kGreen);
    g_res5->SetMarkerColor(kMagenta);
    g_res5->SetLineColor(kMagenta);
    
    gROOT->ProcessLine("zone");
    g_res1->GetXaxis()->SetLimits(0.0, 25.0);
    g_res1->GetYaxis()->SetRangeUser(-1.0, 1.0);
    g_res1->SetTitle("residual;energy using alpha parameters [MeV];residual [MeV]");

    g_res1->Draw("ap");
    g_res2->Draw("p");
    g_res3->Draw("p");
    g_res4->Draw("p");
    g_res5->Draw("p");
    zero->Draw("same");

    TLegend *legend = new TLegend(0.13, 0.15, 0.28, 0.33);
    legend->AddEntry(g_res1, "tel1" , "pl");
    legend->AddEntry(g_res2, "tel2" , "pl");
    legend->AddEntry(g_res3, "tel3" , "pl");
    legend->AddEntry(g_res4, "tel4" , "pl");
    legend->AddEntry(g_res5, "tel5" , "pl");
    legend->SetFillColor(0);
    legend->Draw();

    gROOT->ProcessLine("artcanvas->Print(\"figure/calib/calibrun/residual.png\")");

    // for telescope
    TGraphErrors *g1 = new TGraphErrors();
    TGraphErrors *g2 = new TGraphErrors();
    TGraphErrors *g3 = new TGraphErrors();
    TGraphErrors *g4 = new TGraphErrors();
    TGraphErrors *g5 = new TGraphErrors();

    for(Int_t i=0; i<N1; i++){
        g1->SetPoint(i, tel1_brho_energy[i], tel1_sigma[i]*2.35);
        g1->SetPointError(i, 0.0, tel1_sigma_err[i]*2.35);
    }
    for(Int_t i=0; i<N2; i++){
        g2->SetPoint(i, tel2_brho_energy[i], tel2_sigma[i]*2.35);
        g2->SetPointError(i, 0.0, tel2_sigma_err[i]*2.35);
    }
    for(Int_t i=0; i<N3; i++){
        g3->SetPoint(i, tel3_brho_energy[i], tel3_sigma[i]*2.35);
        g3->SetPointError(i, 0.0, tel3_sigma_err[i]*2.35);
    }
    for(Int_t i=0; i<N4; i++){
        g4->SetPoint(i, tel4_brho_energy[i], tel4_sigma[i]*2.35);
        g4->SetPointError(i, 0.0, tel4_sigma_err[i]*2.35);
    }
    for(Int_t i=0; i<N5; i++){
        g5->SetPoint(i, tel5_brho_energy[i], tel5_sigma[i]*2.35);
        g5->SetPointError(i, 0.0, tel5_sigma_err[i]*2.35);
    }

    g1->SetMarkerColor(kBlack);
    g1->SetLineColor(kBlack);
    g2->SetMarkerColor(kBlue);
    g2->SetLineColor(kBlue);
    g3->SetMarkerColor(kRed);
    g3->SetLineColor(kRed);
    g4->SetMarkerColor(kGreen);
    g4->SetLineColor(kGreen);
    g5->SetMarkerColor(kMagenta);
    g5->SetLineColor(kMagenta);
    
    gROOT->ProcessLine("zone");
    g1->GetXaxis()->SetLimits(0.0, 25.0);
    g1->GetYaxis()->SetRangeUser(0.0, 0.4);
    g1->SetTitle("resolution;energy using alpha parameters [MeV];resolution [MeV]");

    g1->Draw("ap");
    g2->Draw("p");
    g3->Draw("p");
    g4->Draw("p");
    g5->Draw("p");

    TLegend *legend2 = new TLegend(0.13, 0.70, 0.28, 0.88);
    legend2->AddEntry(g1, "tel1" , "pl");
    legend2->AddEntry(g2, "tel2" , "pl");
    legend2->AddEntry(g3, "tel3" , "pl");
    legend2->AddEntry(g4, "tel4" , "pl");
    legend2->AddEntry(g5, "tel5" , "pl");
    legend2->SetFillColor(0);
    legend2->Draw();

    gROOT->ProcessLine("artcanvas->Print(\"figure/calib/calibrun/resolution.png\")");

}


Double_t Brho2Energy(Double_t brho, Double_t m, Int_t z)
{
    Double_t mass = m * 931.478;
    //Double_t brhoqc = brho * z * 1.602176634e-19 * 299792458.0 * 6.242e+12;
    Double_t brhoqc = brho * z * 299.8160602;
    return TMath::Sqrt(mass * mass + brhoqc * brhoqc) - mass;
}
