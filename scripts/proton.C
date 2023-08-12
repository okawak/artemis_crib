void proton(TString NAME="", TString NUM="", TString GATE="", TString TEL="")
{
  gROOT->ProcessLine(Form("add steering/procproton.yaml NAME=%s NUM=%s GATE=%s TEL=%s", NAME.Data(), NUM.Data(), GATE.Data(), TEL.Data()));
  art::TLoopManager::Instance()->GetLoop()->Resume();

  gROOT->ProcessLine(".q");
}
