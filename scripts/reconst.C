void reconst(TString NAME = "", TString NUM = "", TString GATE = "", TString TEL = "")
{
   gROOT->ProcessLine(Form("add steering/procTGTIK.yaml NAME=%s NUM=%s GATE=%s", NAME.Data(), NUM.Data(), GATE.Data()));
   art::TLoopManager::Instance()->GetLoop()->Resume();

   gROOT->ProcessLine(".q");
}
