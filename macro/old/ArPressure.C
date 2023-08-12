void ArPressure()
{
    gROOT->ProcessLine("zone");
    gStyle->SetOptStat(0);
    gStyle->SetOptFit(0);
    gStyle->SetMarkerStyle(20);
    gStyle->SetMarkerSize(1.5);

    static const Int_t N = 4;

    Double_t he_pressure[4] = {0.0, 50.0, 100.0, 150.0};
    Double_t ar_pressure[4] = {0.0, 8.8, 18.0, 27.5};

    Double_t he_adc[4] = {2485.0, 1920.0, 1259.0, 527.5};
    Double_t ar_adc[4] = {2465.0, 1953.0, 1387.0, 760.6};

    Double_t he_adc_err[4] = {1.0, 1.5, 1.6, 1.1};
    Double_t ar_adc_err[4] = {1.1, 1.6, 1.5, 1.2};

    Double_t he_adc_sigma[4] = {73.80, 86.91, 100.3, 64.3};
    Double_t ar_adc_sigma[4] = {75.35, 78.48, 83.70, 92.24};

    TGraphErrors *g1 = new TGraphErrors(N);
    TGraphErrors *g2 = new TGraphErrors(N);
    for(Int_t j=0; j<N; ++j){
        g1->SetPoint(j, he_pressure[j], he_adc[j]);
        g1->SetPointError(j, 0.0, he_adc_err[j]);
        //g1->SetPointError(j, 0.0, he_adc_sigma[j]);

        g2->SetPoint(j, ar_pressure[j], ar_adc[j]);
        g2->SetPointError(j, 0.0, ar_adc_err[j]);
        //g2->SetPointError(j, 0.0, ar_adc_sigma[j]);

    }

    TF1 *f1 = new TF1("f1", "pol1", 0., 200.);
    TF1 *f2 = new TF1("f2", "pol1", 0., 50.);

    f1->SetParameters(2500., -1.0); 
    f2->SetParameters(2500., -1.0); 
    
    g1->GetXaxis()->SetLimits(0.,200.);
    g1->GetYaxis()->SetRangeUser(0.,2700.);
    g1->SetTitle(Form("thickness check;pressure [Torr];ADC channel [ch]"));
    g1->SetMarkerColor(kBlue);
    g1->Draw("ap");

    g1->Fit(f1,"r");
    f1->SetLineColor(kBlue);
    f1->Draw("same");

    //g2->GetXaxis()->SetLimits(0.,300.);
    //g2->GetYaxis()->SetRangeUser(0.,3000.);
    //g2->SetTitle(Form("thickness check;pressure [Torr];ADC channel [ch]"));


    g2->SetMarkerColor(kRed);
    g2->Draw("p");

    g2->Fit(f2,"r");
    f2->SetLineColor(kRed);
    f2->Draw("same");

    gROOT->ProcessLine("artcanvas->Print(\"c1.png\")");
    return;
}