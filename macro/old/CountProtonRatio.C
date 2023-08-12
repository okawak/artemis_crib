{
    TString tel1_gate_name = "tel1_proton";
    TString tel1_gate = "\"(abs(sqrt(tel1.fdEY * tel1.fEtotal) - 5.3) < 0.5) && (abs(tel1.GetETimingvec(0) + 172.5) < 27.5) && tel1.GetEvec(0) > 0.1\"";

    TString tel2_gate_name = "tel2_proton";
    TString tel2_gate = "\"abs(sqrt(tel2.fdEY * tel2.fEtotal) - 5.45) < 0.55 && tel2.GetEvec(0) > 0.1 && abs(tel2.GetETimingvec(0) + 170.0) < 50.0\"";

    TString tel3_gate_name = "tel3_proton";
    TString tel3_gate = "\"abs(sqrt(tel3.fdEY * tel3.fEtotal) - 7.7) < 1.0 && tel3.GetEvec(0) > 0.1 && abs(tel3.GetETimingvec(0) + 190.0) < 50.0\"";

    TString tel4_gate_name = "tel4_proton";
    TString tel4_gate = "\"( (abs(sqrt(tel4.fdE * tel4.fEtotal) - 2.5) < 1.0) || (tel4.fdE < 0.1 && tel4.fEtotal > 3.0) ) && abs(tel4.GetETimingvec(0) + 190.0) < 30.0\"";

    TString tel5_gate_name = "tel5_proton";
    TString tel5_gate = "\"( (abs(sqrt(tel5.fdE * tel5.fEtotal) - 2.9) < 0.7) || (tel5.fdE < 0.1 && tel5.fEtotal > 3.0) ) && abs(tel5.GetETimingvec(0) + 190.0) < 30.0\"";


    gROOT->ProcessLine("fcd 0");
    gROOT->ProcessLine(Form("tree->SetAlias(\"%s\",%s)", tel1_gate_name.Data(), tel1_gate.Data()));
    gROOT->ProcessLine(Form("tree->GetEntries(\"%s && tel1.fEtotal < 11.0\")", tel1_gate_name.Data()));
    gROOT->ProcessLine("fcd 5");
    gROOT->ProcessLine(Form("tree->SetAlias(\"%s\",%s)", tel1_gate_name.Data(), tel1_gate.Data()));
    gROOT->ProcessLine(Form("tree->GetEntries(\"%s && tel1.fEtotal < 11.0\")", tel1_gate_name.Data()));
    gROOT->ProcessLine("fcd 1");
    gROOT->ProcessLine(Form("tree->SetAlias(\"%s\",%s)", tel2_gate_name.Data(), tel2_gate.Data()));
    gROOT->ProcessLine(Form("tree->GetEntries(\"%s && tel2.fEtotal < 10.5\")", tel2_gate_name.Data()));
    gROOT->ProcessLine("fcd 6");
    gROOT->ProcessLine(Form("tree->SetAlias(\"%s\",%s)", tel2_gate_name.Data(), tel2_gate.Data()));
    gROOT->ProcessLine(Form("tree->GetEntries(\"%s && tel2.fEtotal < 10.5\")", tel2_gate_name.Data()));
    gROOT->ProcessLine("fcd 2");
    gROOT->ProcessLine(Form("tree->SetAlias(\"%s\",%s)", tel3_gate_name.Data(), tel3_gate.Data()));
    gROOT->ProcessLine(Form("tree->GetEntries(\"%s && tel3.fEtotal < 10.5\")", tel3_gate_name.Data()));
    gROOT->ProcessLine("fcd 7");
    gROOT->ProcessLine(Form("tree->SetAlias(\"%s\",%s)", tel3_gate_name.Data(), tel3_gate.Data()));
    gROOT->ProcessLine(Form("tree->GetEntries(\"%s && tel3.fEtotal < 10.5\")", tel3_gate_name.Data()));
    gROOT->ProcessLine("fcd 3");
    gROOT->ProcessLine(Form("tree->SetAlias(\"%s\",%s)", tel4_gate_name.Data(), tel4_gate.Data()));
    gROOT->ProcessLine(Form("tree->GetEntries(\"%s && tel4.fEtotal < 10.0\")", tel4_gate_name.Data()));
    gROOT->ProcessLine("fcd 8");
    gROOT->ProcessLine(Form("tree->SetAlias(\"%s\",%s)", tel4_gate_name.Data(), tel4_gate.Data()));
    gROOT->ProcessLine(Form("tree->GetEntries(\"%s && tel4.fEtotal < 10.0\")", tel4_gate_name.Data()));
    gROOT->ProcessLine("fcd 4");
    gROOT->ProcessLine(Form("tree->SetAlias(\"%s\",%s)", tel5_gate_name.Data(), tel5_gate.Data()));
    gROOT->ProcessLine(Form("tree->GetEntries(\"%s && tel5.fEtotal < 9.0\")", tel5_gate_name.Data()));
    gROOT->ProcessLine("fcd 9");
    gROOT->ProcessLine(Form("tree->SetAlias(\"%s\",%s)", tel5_gate_name.Data(), tel5_gate.Data()));
    gROOT->ProcessLine(Form("tree->GetEntries(\"%s && tel5.fEtotal < 9.0\")", tel5_gate_name.Data()));

}