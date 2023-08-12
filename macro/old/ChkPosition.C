{
    gStyle->SetOptStat(0);
    gROOT->ProcessLine("fcd 0");
    gROOT->ProcessLine("zone");
    gROOT->ProcessLine("lgy");

    gROOT->ProcessLine("tree->Draw(\"tel2_dEX_raw.fP1>>tel2XP1(400,300.,700.)\")");
    gROOT->ProcessLine("tree->Draw(\"tel3_dEX_raw.fP1>>tel3XP1(400,650.,1050.)\")");
    gROOT->ProcessLine("tree->Draw(\"tel4_dEX_raw.fP1>>tel4XP1(300,850.,1150.)\")");
    gROOT->ProcessLine("tree->Draw(\"tel4_dEY_raw.fP1>>tel4YP1(400,1250.,1650.)\")");
    gROOT->ProcessLine("tree->Draw(\"tel5_dEX_raw.fP1>>tel5XP1(350,1400.,1750.)\")");
    gROOT->ProcessLine("tree->Draw(\"tel5_dEY_raw.fP1>>tel5YP1(350,1600.,1950.)\")");

    gROOT->ProcessLine(".x macro/ArtcanvasSetting.C");
    //gROOT->ProcessLine("zone 3 2");
    //gROOT->ProcessLine("ht 2");
    //gROOT->ProcessLine("ht 3");
    //gROOT->ProcessLine("ht 4");
    //gROOT->ProcessLine("ht 6");
    //gROOT->ProcessLine("ht 7");
    //gROOT->ProcessLine("ht 8");

}