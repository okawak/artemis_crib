// use chkcoinroot.yaml
{
    gStyle->SetOptStat(0);
    gStyle->SetOptFit(0);
    gStyle->SetMarkerStyle(20);


    gROOT->ProcessLine("zone");
    gROOT->ProcessLine("fcd 12");

    gROOT->ProcessLine("tree->Draw(\"result.fEtotal:result.fTiming>>phys_timing(1000,-10.,40., 1000,4.,25.)\",\"result.fID==1\",\"colz\")");

    TH2F *hphys = (TH2F*)phys_timing->Clone("hphys");
    hphys->Draw("colz");
    gROOT->ProcessLine("artcanvas->Print(\"c1.png\")");

    TGraph *gphys = new TGraph();

    Int_t phys_count = 0;
    for(Int_t i=0; i<hphys->GetNbinsX(); i++){
        for(Int_t j=0; j<hphys->GetNbinsY(); j++){
            if(hphys->GetBinContent(i, j) > 0){
                //TH1D *prx = hphys->ProjectionX("prx", i, i);
                //TH1D *pry = hphys->ProjectionY("pry", j, j);
                TH1D *prx = (TH1D*)hphys->ProjectionX("prx", 0, hphys->GetNbinsX());
                TH1D *pry = (TH1D*)hphys->ProjectionY("pry", 0, hphys->GetNbinsY());

                gphys->SetPoint(phys_count, prx->GetBinCenter(i), pry->GetBinCenter(j));
                phys_count++;
            }
        }
    }
    gphys->GetXaxis()->SetLimits(-10.0, 40.0);
    gphys->GetYaxis()->SetRangeUser(4.0, 25.0);
    gphys->SetMarkerColor(kRed);
    gphys->SetMarkerSize(0.5);
    gphys->Draw("ap");

    gROOT->ProcessLine("artcanvas->Print(\"c2.png\")");





    gROOT->ProcessLine("zone");
    gROOT->ProcessLine("fcd 13");

    gROOT->ProcessLine("tree->Draw(\"result.fEtotal:result.fTiming>>ES_timing(1000,-10.,40., 1000,4.,25.)\",\"result.fID==1\",\"colz\")");

    TH2F *hES = (TH2F*)ES_timing->Clone("hphys");
    hES->Draw("colz");
    gROOT->ProcessLine("artcanvas->Print(\"c1.png\")");

    TGraph *gES = new TGraph();

    Int_t ES_count = 0;
    for(Int_t i=0; i<hES->GetNbinsX(); i++){
        for(Int_t j=0; j<hES->GetNbinsY(); j++){
            if(hES->GetBinContent(i, j) > 0){
                //TH1D *prx = hphys->ProjectionX("prx", i, i);
                //TH1D *pry = hphys->ProjectionY("pry", j, j);
                TH1D *prx = (TH1D*)hES->ProjectionX("prx", 0, hES->GetNbinsX());
                TH1D *pry = (TH1D*)hES->ProjectionY("pry", 0, hES->GetNbinsY());

                gES->SetPoint(ES_count, prx->GetBinCenter(i), pry->GetBinCenter(j));
                ES_count++;
            }
        }
    }
    gES->GetXaxis()->SetLimits(-10.0, 40.0);
    gES->GetYaxis()->SetRangeUser(4.0, 25.0);
    gES->SetMarkerColor(kRed);
    gES->SetMarkerSize(0.5);
    gES->Draw("ap");

    gROOT->ProcessLine("artcanvas->Print(\"c2.png\")");


}