{
    gStyle->SetOptStat(0);

    //Double_t si_factor = 4.42;
    //Double_t al_factor = 5.21;
    //Double_t mg_factor = 5.56;
    Double_t si_factor = 6.45;
    Double_t al_factor = 7.1;
    Double_t mg_factor = 5.35;

    // for si26
    for(Int_t i=1; i<6; i++){
      gROOT->ProcessLine("fcd 0");
      gROOT->ProcessLine("zone");

      gROOT->ProcessLine(Form("tree->Draw(\"tel.fEtotal>>phys(50,0.,25.)\",\"tel.fID==%d\")",i));
      TH1F *hphys = (TH1F*)phys->Clone("hphys");
      hphys->Sumw2();

      gROOT->ProcessLine("fcd 1");
      gROOT->ProcessLine("zone");

      gROOT->ProcessLine(Form("tree->Draw(\"tel.fEtotal>>bg(50,0.,25.)\",\"tel.fID==%d\")",i));
      TH1F *hbg = (TH1F*)bg->Clone("hbg");
      hbg->Sumw2();
      hbg->Scale(si_factor);

      gROOT->ProcessLine("cd");
      hphys->Draw("hist");

      hbg->SetLineColor(kRed);
      hbg->Draw("same");
      gROOT->ProcessLine(Form("artcanvas->Print(\"figure/proton/si26_tel%d.png\")",i));
    }

    // for al25
    for(Int_t i=1; i<6; i++){
      gROOT->ProcessLine("fcd 2");
      gROOT->ProcessLine("zone");

      gROOT->ProcessLine(Form("tree->Draw(\"tel.fEtotal>>phys(50,0.,25.)\",\"tel.fID==%d\")",i));
      TH1F *hphys = (TH1F*)phys->Clone("hphys");
      hphys->Sumw2();

      gROOT->ProcessLine("fcd 3");
      gROOT->ProcessLine("zone");

      gROOT->ProcessLine(Form("tree->Draw(\"tel.fEtotal>>bg(50,0.,25.)\",\"tel.fID==%d\")",i));
      TH1F *hbg = (TH1F*)bg->Clone("hbg");
      hbg->Sumw2();
      hbg->Scale(al_factor);

      gROOT->ProcessLine("cd");
      hphys->Draw("hist");

      hbg->SetLineColor(kRed);
      hbg->Draw("same");
      gROOT->ProcessLine(Form("artcanvas->Print(\"figure/proton/al25_tel%d.png\")",i));
    }

    // for mg24
    for(Int_t i=1; i<6; i++){
      gROOT->ProcessLine("fcd 4");
      gROOT->ProcessLine("zone");

      gROOT->ProcessLine(Form("tree->Draw(\"tel.fEtotal>>phys(50,0.,25.)\",\"tel.fID==%d\")",i));
      TH1F *hphys = (TH1F*)phys->Clone("hphys");
      hphys->Sumw2();

      gROOT->ProcessLine("fcd 5");
      gROOT->ProcessLine("zone");

      gROOT->ProcessLine(Form("tree->Draw(\"tel.fEtotal>>bg(50,0.,25.)\",\"tel.fID==%d\")",i));
      TH1F *hbg = (TH1F*)bg->Clone("hbg");
      hbg->Sumw2();
      hbg->Scale(mg_factor);

      gROOT->ProcessLine("cd");
      hphys->Draw("hist");

      hbg->SetLineColor(kRed);
      hbg->Draw("same");
      gROOT->ProcessLine(Form("artcanvas->Print(\"figure/proton/mg24_tel%d.png\")",i));
    }


  //gROOT->ProcessLine(".q");

}



