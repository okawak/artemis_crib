{
    gStyle->SetOptStat(0);
    gROOT->ProcessLine("zone");

    TString range = "(50,0.,25.)";
    //TString sim_range = "(200,0.,25.)";
    TString sim_range = "(50,0.,25.)";
    //TString bg_scale_factor = "4.4282141"; // beam single
    TString bg_scale_factor = "5941./918."; // 6.4716776 low energy proton coin event
    //TString sim_scale_factor = "3.8/200.0";
    TString sim_scale_factor = "0.89/200.0";

    TString tel1_gate_name = "\"tel1_proton\"";
    TString tel1_gate = "\"(abs(sqrt(tel1.fdEY * tel1.fEtotal) - 5.3) < 0.5) && (abs(tel1.GetETimingvec(0) + 172.5) < 27.5) && tel1.GetEvec(0) > 0.1\"";

    TString tel2_gate_name = "\"tel2_proton\"";
    TString tel2_gate = "\"abs(sqrt(tel2.fdEY * tel2.fEtotal) - 5.45) < 0.55 && tel2.GetEvec(0) > 0.1 && abs(tel2.GetETimingvec(0) + 170.0) < 50.0\"";

    TString tel3_gate_name = "\"tel3_proton\"";
    TString tel3_gate = "\"abs(sqrt(tel3.fdEY * tel3.fEtotal) - 7.7) < 1.0 && tel3.GetEvec(0) > 0.1 && abs(tel3.GetETimingvec(0) + 190.0) < 50.0\"";

    TString tel4_gate_name = "\"tel4_proton\"";
    TString tel4_gate = "\"( (abs(sqrt(tel4.fdE * tel4.fEtotal) - 2.5) < 1.0) || (tel4.fdE < 0.1 && tel4.fEtotal > 3.0) ) && abs(tel4.GetETimingvec(0) + 190.0) < 30.0\"";

    TString tel5_gate_name = "\"tel5_proton\"";
    TString tel5_gate = "\"( (abs(sqrt(tel5.fdE * tel5.fEtotal) - 2.9) < 0.7) || (tel5.fdE < 0.1 && tel5.fEtotal > 3.0) ) && abs(tel5.GetETimingvec(0) + 190.0) < 30.0\"";

    TH1F *hall_phys = new TH1F("hall_phys","hall_phys",50, 0., 25.);
    TH1F *hall_bg = new TH1F("hall_bg","hall_bg",50, 0., 25.);
    TH1F *hall_sim = new TH1F("hall_sim","hall_sim",50, 0., 25.);

    for(Int_t i=0; i<5; i++){
        TString gate_name, gate;
        if(i==0){
            gate_name.Form("%s",tel1_gate_name.Data());
            gate.Form("%s",tel1_gate.Data());
        }else if(i==1){
            gate_name.Form("%s",tel2_gate_name.Data());
            gate.Form("%s",tel2_gate.Data());
        }else if(i==2){
            gate_name.Form("%s",tel3_gate_name.Data());
            gate.Form("%s",tel3_gate.Data());
        }else if(i==3){
            gate_name.Form("%s",tel4_gate_name.Data());
            gate.Form("%s",tel4_gate.Data());
        }else if(i==4){
            gate_name.Form("%s",tel5_gate_name.Data());
            gate.Form("%s",tel5_gate.Data());
        }

        gROOT->ProcessLine(Form("fcd %d",i));
        gROOT->ProcessLine(Form("tree->SetAlias(%s,%s)", gate_name.Data(), gate.Data()));
        gROOT->ProcessLine(Form("tree->Draw(\"tel%d.fEtotal>>phys_E%s\",%s)", i+1, range.Data(), gate_name.Data()));

        hall_phys->Add(phys_E);

        gROOT->ProcessLine(Form("fcd %d",i+5));
        gROOT->ProcessLine(Form("tree->SetAlias(%s,%s)",gate_name.Data(), gate.Data()));
        gROOT->ProcessLine(Form("tree->Draw(\"tel%d.fEtotal>>bg_E%s\",%s)", i+1, range.Data(), gate_name.Data()));
        gROOT->ProcessLine(Form("bg_E->Sumw2()"));
        gROOT->ProcessLine(Form("bg_E->Scale(%s)", bg_scale_factor.Data()));
        gROOT->ProcessLine("bg_E->SetLineColor(kRed)");

        hall_bg->Add(bg_E);

        gROOT->ProcessLine("fcd 10");
        gROOT->ProcessLine(Form("tree->Draw(\"result.fEtotal>>sim_E%s\",\"result.fID==%d\")",sim_range.Data(), i+1));
        gROOT->ProcessLine(Form("sim_E->Scale(%s)", sim_scale_factor.Data()));
        gROOT->ProcessLine("sim_E->SetLineColor(kGreen)");

        hall_sim->Add(sim_E);

        gROOT->ProcessLine(Form("fcd %d",i));
        gROOT->ProcessLine("zone");
        gROOT->ProcessLine("phys_E->Draw()");

        gROOT->ProcessLine(Form("fcd %d",i+5));
        gROOT->ProcessLine("bg_E->Draw(\"same\")");

        gROOT->ProcessLine("fcd 10");
        gROOT->ProcessLine("sim_E->Draw(\"same hist\")");

        TLegend *legend = new TLegend(0.68, 0.76, 0.89, 0.88);
        legend->AddEntry(phys_E, "physics data" , "l");
        legend->AddEntry(bg_E, "BG data (scale)" , "l");
        legend->AddEntry(sim_E, "simulation" , "l");
        legend->SetFillColor(0);
        legend->Draw();

        gROOT->ProcessLine(Form("artcanvas->Print(\"figure/eventselection/tel%d_sim.png\")",i+1));

    }

    gROOT->ProcessLine("zone");
    hall_bg->SetLineColor(kRed);
    hall_sim->SetLineColor(kGreen);

    hall_phys->Draw();
    hall_bg->Draw("same");
    hall_sim->Draw("same hist");

    TLegend *legend = new TLegend(0.68, 0.76, 0.89, 0.88);
    legend->AddEntry(hall_phys, "physics data" , "l");
    legend->AddEntry(hall_bg, "BG data (scale)" , "l");
    legend->AddEntry(hall_sim, "simulation" , "l");
    legend->SetFillColor(0);
    legend->Draw();

    gROOT->ProcessLine(Form("artcanvas->Print(\"figure/eventselection/all_sim.png\")"));



}