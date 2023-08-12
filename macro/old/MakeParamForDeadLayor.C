{
    const TString ARTEMIS_WORKDIR = "/home/okawa/art_analysis/user/okawa";

    const TString TEL = "tel5";
    const TString RUN = "0305";

    const Double_t e_brho_p = 7.89554;
    const Double_t e_brho_a = 7.97705;


    gROOT->ProcessLine("fcd 0");
    gROOT->ProcessLine(".x macro/setalias.C");
    gROOT->ProcessLine("zone");

    // proton
    gROOT->ProcessLine(Form("tree->Draw(\"tel5.fEtotal>>h_p(200,0.,10.)\",\"proton\")"));
    //gROOT->ProcessLine(Form("tree->Draw(\"tel1.fEtotal-tel1.GetEvec(1)>>h_p(100,10.,20.)\",\"proton\")"));
    gROOT->ProcessLine(Form(".x %s/macro/GausFit.C(h_p, \"correction/%s/proton%s\", %g, 0.0, 1.0)", ARTEMIS_WORKDIR.Data(), TEL.Data(), RUN.Data(), e_brho_p));

    // alpha
    gROOT->ProcessLine(Form("tree->Draw(\"tel5.fEtotal>>h_a(200,0.,10.)\",\"alpha\")"));
    //gROOT->ProcessLine(Form("tree->Draw(\"tel1.fEtotal-tel1.GetEvec(0)-tel1.GetEvec(1)>>h_a(100,10.,20.)\",\"alpha\")"));
    gROOT->ProcessLine(Form(".x %s/macro/GausFit.C(h_a, \"correction/%s/alpha%s\", %g, 0.0, 1.0)", ARTEMIS_WORKDIR.Data(), TEL.Data(), RUN.Data(), e_brho_a));

}