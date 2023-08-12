{
    gStyle->SetOptStat(0);
    gStyle->SetOptFit(0);
    gStyle->SetMarkerStyle(20);

    Double_t timing_offset = 14.5;


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
                if(pry->GetBinCenter(j) < 10.0) continue;

                gphys->SetPoint(phys_count, prx->GetBinCenter(i)-timing_offset, pry->GetBinCenter(j));
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
    gROOT->ProcessLine("fcd 14");

    gROOT->ProcessLine("tree->Draw(\"result.fEtotal:result.fTiming>>phys_timing2(1000,-10.,40., 1000,4.,25.)\",\"result.fID==1\",\"colz\")");

    TH2F *hphys2 = (TH2F*)phys_timing2->Clone("hphys2");
    hphys2->Draw("colz");
    gROOT->ProcessLine("artcanvas->Print(\"c1.png\")");

    TGraph *gphys2 = new TGraph();

    Int_t phys_count2 = 0;
    for(Int_t i=0; i<hphys2->GetNbinsX(); i++){
        for(Int_t j=0; j<hphys2->GetNbinsY(); j++){
            if(hphys2->GetBinContent(i, j) > 0){
                //TH1D *prx = hphys->ProjectionX("prx", i, i);
                //TH1D *pry = hphys->ProjectionY("pry", j, j);
                TH1D *prx = (TH1D*)hphys2->ProjectionX("prx", 0, hphys2->GetNbinsX());
                TH1D *pry = (TH1D*)hphys2->ProjectionY("pry", 0, hphys2->GetNbinsY());
                if(pry->GetBinCenter(j) < 10.0) continue;

                gphys2->SetPoint(phys_count2, prx->GetBinCenter(i)-timing_offset, pry->GetBinCenter(j));
                phys_count2++;
            }
        }
    }
    gphys2->GetXaxis()->SetLimits(-10.0, 40.0);
    gphys2->GetYaxis()->SetRangeUser(4.0, 25.0);
    gphys2->SetMarkerColor(kRed);
    gphys2->SetMarkerSize(0.5);
    gphys2->Draw("ap");

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

                gES->SetPoint(ES_count, prx->GetBinCenter(i)-timing_offset, pry->GetBinCenter(j));
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











    gROOT->ProcessLine("zone");
    gROOT->ProcessLine("fcd 0");
    tree->SetAlias("tel1_proton_all","(abs(sqrt(tel1.fdEY * tel1.fEtotal) - 5.3) < 0.5) && tel1.GetEvec(0) > 0.1");
    tree->SetAlias("tel1_proton","(abs(sqrt(tel1.fdEY * tel1.fEtotal) - 5.3) < 0.5) && (abs(tel1.GetETimingvec(0) + 172.5) < 27.5) && tel1.GetEvec(0) > 0.1");
    tree->Draw("tel1.GetEvec(0):tel1.GetETimingvec(0)>>all(50,-310.,-90.,50,0.,16.)","tel1_proton_all","colz");
    gROOT->ProcessLine("ht 1 colz");

    Double_t factor = 50.0;
    Double_t offset = 0.9;

    TF1 *f1 = new TF1("f1","([0]*[0])/((x-[1])*(x-[1]))+[2]",-300.,-240.);
    TF1 *f2 = new TF1("f2","([0]*[0])/((x-[1])*(x-[1]))+[2]",-230.,-170.);
    TF1 *f3 = new TF1("f3","([0]*[0])/((x-[1])*(x-[1]))+[2]",-150.,-90.);
    TF1 *fphys = new TF1("fphys","([0]*[0])/((x-[1])*(x-[1]))+[2]",-190.,-130.);

    f1->SetParameters(factor,-301, offset);
    f1->SetLineWidth(3);
    //all->Fit(f1,"","",-300,-230);
    f1->Draw("same");

    f2->SetParameters(factor,-229, offset);
    f2->SetLineWidth(3);
    f2->Draw("same");

    f3->SetParameters(factor,-152, offset);
    f3->SetLineWidth(3);
    f3->Draw("same");

    fphys->SetParameters(factor,-193, offset);
    fphys->SetLineWidth(3);
    fphys->Draw("same");

    gROOT->ProcessLine("artcanvas->Print(\"figure/walk/tel1.png\")");



    gROOT->ProcessLine("zone");
    tree->Draw("tel1.GetEvec(0):tel1.GetETimingvec(0)-(-193.0 + 50.0/TMath::Sqrt(tel1.GetEvec(0)-0.9))>>corr(75,-150.0,100.0,75,0.,16.)","tel1_proton_all","colz");

    //TF1 *fnext = new TF1("fphys","[0]+[1]*x",-20.,20.);
    //fnext->SetParameters(8.0,0.6);
    //fnext->Draw("same");
    gROOT->ProcessLine("artcanvas->Print(\"figure/walk/tel1_corr.png\")");

    //gROOT->ProcessLine("zone");
    //tree->Draw("tel1.GetEvec(0):tel1.GetETimingvec(0)-(-195.0 + 60.0/TMath::Sqrt(tel1.GetEvec(0)))-((tel1.GetEvec(0)-8.0)/0.6)>>corr(50,-100.0,100.0,50,0.,16.)","tel1_proton_all","colz");
    //gROOT->ProcessLine("artcanvas->Print(\"figure/walk/tel1_corr2.png\")");

    gROOT->ProcessLine("zone");
    tree->Draw("tel1.fEtotal:tel1.GetETimingvec(0)-(-193.0 + 50.0/TMath::Sqrt(tel1.GetEvec(0)-0.9))>>corr_tot(82,-60.,60.,82,4.,25.)","tel1_proton_all","colz");

    gphys->Draw("same p");
    gphys2->Draw("same p");
    gES->Draw("same p");
    gROOT->ProcessLine("artcanvas->Print(\"figure/walk/tel1_zoom.png\")");




    gROOT->ProcessLine("fcd 5");
    tree->SetAlias("tel1_proton_all","(abs(sqrt(tel1.fdEY * tel1.fEtotal) - 5.3) < 0.5) && tel1.GetEvec(0) > 0.1");
    tree->SetAlias("tel1_proton","(abs(sqrt(tel1.fdEY * tel1.fEtotal) - 5.3) < 0.5) && (abs(tel1.GetETimingvec(0) + 172.5) < 27.5) && tel1.GetEvec(0) > 0.1");
    gROOT->ProcessLine("zone");
    tree->Draw("tel1.fEtotal:tel1.GetETimingvec(0)-(-193.0 + 50.0/TMath::Sqrt(tel1.GetEvec(0)-0.9))>>corr_tot(41,-60.,60.,41,4.,25.)","tel1_proton_all","colz");
    gROOT->ProcessLine("artcanvas->Print(\"figure/walk/tel1_bg_zoom.png\")");
}