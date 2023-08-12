{
    const TString ARTEMIS_WORKDIR = "/home/okawa/art_analysis/user/okawa";

    const TString RUN = "0247";
    const Int_t debug = 2; // 0: raw 1: gate 2: fit

    TString RF = "1000,0.,120.";
    TString TOF = "150,25.,40.";
    TString PPACBX = "200,-50.,50.";
    TString RAWCH = "100,0.,4000.";
    TString RAWCH_SI = "100,0.,1500.";
    TString RAWCH_AL = "100,0.,1500.";
    TString RAWCH_MG =  "100,0.,1500.";
    TString RAWCH_SI2 = "100,0.,1500.";

    TString WIDTH = "150.0";

    gROOT->ProcessLine("fcd 0");
    gROOT->ProcessLine(".x macro/setalias.C");
    gROOT->ProcessLine("zone");


    if(debug == 0 || debug == 1){
        gROOT->ProcessLine("tree->Draw(\"f3appac.fTAnode>>ppaca(100,-50.,0.)\")");
        gROOT->ProcessLine("tree->Draw(\"f3bppac.fTAnode>>ppacb(100,-1., 1.)\")");
        gROOT->ProcessLine(Form("tree->Draw(\"rf_cal_0.fTiming:(f3bppac.fTAnode - f3appac.fTAnode)>>PI(%s, %s)\",\"\",\"colz\")", TOF.Data(), RF.Data()));

        if(debug == 1){
            // si26
            gROOT->ProcessLine(Form("tree->Draw(\"rf_cal_0.fTiming:(f3bppac.fTAnode - f3appac.fTAnode)>>PI_si26(%s, %s)\",\"si26\",\"colz\")", TOF.Data(), RF.Data()));
            gROOT->ProcessLine(Form("tree->Draw(\"rf_cal_0.fTiming:f3bppac.fX>>Pos_si26(%s, %s)\",\"si26\",\"colz\")", PPACBX.Data(), RF.Data()));

            // al25
            gROOT->ProcessLine(Form("tree->Draw(\"rf_cal_0.fTiming:(f3bppac.fTAnode - f3appac.fTAnode)>>PI_al25(%s, %s)\",\"al25\",\"colz\")", TOF.Data(), RF.Data()));
            gROOT->ProcessLine(Form("tree->Draw(\"rf_cal_0.fTiming:f3bppac.fX>>Pos_al25(%s, %s)\",\"al25\",\"colz\")", PPACBX.Data(), RF.Data()));

            // mg24
            gROOT->ProcessLine(Form("tree->Draw(\"rf_cal_0.fTiming:(f3bppac.fTAnode - f3appac.fTAnode)>>PI_mg24(%s, %s)\",\"mg24\",\"colz\")", TOF.Data(), RF.Data()));
            gROOT->ProcessLine(Form("tree->Draw(\"rf_cal_0.fTiming:f3bppac.fX>>Pos_mg24(%s, %s)\",\"mg24\",\"colz\")", PPACBX.Data(), RF.Data()));
        }
    }

    // lowgain check
    for(Int_t i=0; i<4; ++i){
        gROOT->ProcessLine(Form("tree->Draw(\"rf_cal_0.fTiming:lowgain_raw.fCharge>>PI_%d(%s, %s)\",\"lowgain_raw.fID==%d\",\"colz\")", i, RAWCH.Data(), RF.Data(), i));
        gROOT->ProcessLine(Form("tree->Draw(\"lowgain_raw.fCharge>>h%d(%s)\",\"lowgain_raw.fID==%d\")", i, RAWCH.Data(), i));

        if(debug == 1 || debug == 2){
            //si26
            gROOT->ProcessLine(Form("tree->Draw(\"rf_cal_0.fTiming:lowgain_raw.fCharge>>PIsi26_%d(%s, %s)\",\"si26 && lowgain_raw.fID==%d\",\"colz\")", i, RAWCH.Data(), RF.Data(), i));
            gROOT->ProcessLine(Form("tree->Draw(\"lowgain_raw.fCharge>>si26_h%d(%s)\",\"si26 && lowgain_raw.fID==%d\")", i, RAWCH_SI.Data(), i));

            //al25
            gROOT->ProcessLine(Form("tree->Draw(\"rf_cal_0.fTiming:lowgain_raw.fCharge>>PIal25_%d(%s, %s)\",\"al25 && lowgain_raw.fID==%d\",\"colz\")", i, RAWCH.Data(), RF.Data(), i));
            gROOT->ProcessLine(Form("tree->Draw(\"lowgain_raw.fCharge>>al25_h%d(%s)\",\"al25 && lowgain_raw.fID==%d\")", i, RAWCH_AL.Data(), i));

            //mg24
            gROOT->ProcessLine(Form("tree->Draw(\"rf_cal_0.fTiming:lowgain_raw.fCharge>>PImg24_%d(%s, %s)\",\"mg24 && lowgain_raw.fID==%d\",\"colz\")", i, RAWCH.Data(), RF.Data(), i));
            gROOT->ProcessLine(Form("tree->Draw(\"lowgain_raw.fCharge>>mg24_h%d(%s)\",\"mg24 && lowgain_raw.fID==%d\")", i, RAWCH_MG.Data(), i));

            //si26_2
            gROOT->ProcessLine(Form("tree->Draw(\"lowgain_raw.fCharge>>si26_2_h%d(%s)\",\"mg24 && lowgain_raw.fID==%d\")", i, RAWCH_SI2.Data(), i));

            if(debug == 2){
                //si26
                gROOT->ProcessLine(Form(".x %s/macro/Gaus.C(si26_h%d, \"default\", \"default\", %s, 0.0)", ARTEMIS_WORKDIR.Data(), i, WIDTH.Data()));

                //al25
                gROOT->ProcessLine(Form(".x %s/macro/Gaus.C(al25_h%d, \"default\", \"default\", %s, 0.0)", ARTEMIS_WORKDIR.Data(), i, WIDTH.Data()));

                //mg24
                gROOT->ProcessLine(Form(".x %s/macro/Gaus.C(mg24_h%d, \"default\", \"default\", %s, 0.0)", ARTEMIS_WORKDIR.Data(), i, WIDTH.Data()));

                //si26 +13
                gROOT->ProcessLine(Form(".x %s/macro/Gaus.C(si26_2_h%d, \"default\", \"default\", %s, 0.0)", ARTEMIS_WORKDIR.Data(), i, WIDTH.Data()));

            }
        }

    }

    if(debug == 1){
        artcanvas->SetCanvasSize(1200,800);
        gROOT->ProcessLine("zone 4 2");
        gROOT->ProcessLine("lgz");
        gROOT->ProcessLine("ht 4 colz");
        gROOT->ProcessLine("ht 5 colz");
        gROOT->ProcessLine("ht 7 colz");
        gROOT->ProcessLine("ht 9 colz");
        gROOT->ProcessLine("pcd 5");
        gROOT->ProcessLine("ht 6 colz");
        gROOT->ProcessLine("ht 8 colz");
        gROOT->ProcessLine("ht 10 colz");

        gROOT->ProcessLine(Form("artcanvas->Print(\"figure/beam/check/run%s_PI.png\")", RUN.Data()));


        artcanvas->SetCanvasSize(1200,1200);
        gROOT->ProcessLine("zone 4 4");
        gROOT->ProcessLine("ht 11 colz");
        gROOT->ProcessLine("ht 13 colz");
        gROOT->ProcessLine("ht 15 colz");
        gROOT->ProcessLine("ht 17 colz");
        gROOT->ProcessLine("ht 20 colz");
        gROOT->ProcessLine("ht 22 colz");
        gROOT->ProcessLine("ht 24 colz");
        gROOT->ProcessLine("ht 26 colz");
        gROOT->ProcessLine("ht 29 colz");
        gROOT->ProcessLine("ht 31 colz");
        gROOT->ProcessLine("ht 33 colz");
        gROOT->ProcessLine("ht 35 colz");
        gROOT->ProcessLine("ht 38 colz");
        gROOT->ProcessLine("ht 40 colz");
        gROOT->ProcessLine("ht 42 colz");
        gROOT->ProcessLine("ht 44 colz");

        gROOT->ProcessLine(Form("artcanvas->Print(\"figure/beam/check/run%s_lowgain_raw.png\")", RUN.Data()));
    }

    if(debug == 2){
        artcanvas->SetCanvasSize(1200,1200);
        gROOT->ProcessLine("zone 4 4");
        gROOT->ProcessLine("ht 5 colz");
        gROOT->ProcessLine("ht 7 colz");
        gROOT->ProcessLine("ht 9 colz");
        gROOT->ProcessLine("ht 10 colz");
        gROOT->ProcessLine("ht 14 colz");
        gROOT->ProcessLine("ht 16 colz");
        gROOT->ProcessLine("ht 18 colz");
        gROOT->ProcessLine("ht 19 colz");
        gROOT->ProcessLine("ht 23 colz");
        gROOT->ProcessLine("ht 25 colz");
        gROOT->ProcessLine("ht 27 colz");
        gROOT->ProcessLine("ht 28 colz");
        gROOT->ProcessLine("ht 32 colz");
        gROOT->ProcessLine("ht 34 colz");
        gROOT->ProcessLine("ht 36 colz");
        gROOT->ProcessLine("ht 37 colz");

        gROOT->ProcessLine(Form("artcanvas->Print(\"figure/beam/check/run%s_lowgain_gate.png\")", RUN.Data()));


        artcanvas->SetCanvasSize(800,800);
        gROOT->ProcessLine("zone");
        gROOT->ProcessLine("ht 5 colz");
        gROOT->ProcessLine(Form("artcanvas->Print(\"figure/beam/fit/%s/lowgain0_si26.png\")", RUN.Data()));
        gROOT->ProcessLine("ht 7 colz");
        gROOT->ProcessLine(Form("artcanvas->Print(\"figure/beam/fit/%s/lowgain0_al25.png\")", RUN.Data()));
        gROOT->ProcessLine("ht 9 colz");
        gROOT->ProcessLine(Form("artcanvas->Print(\"figure/beam/fit/%s/lowgain0_mg24.png\")", RUN.Data()));
        gROOT->ProcessLine("ht 10 colz");
        gROOT->ProcessLine(Form("artcanvas->Print(\"figure/beam/fit/%s/lowgain0_si26_2.png\")", RUN.Data()));

        gROOT->ProcessLine("ht 14 colz");
        gROOT->ProcessLine(Form("artcanvas->Print(\"figure/beam/fit/%s/lowgain1_si26.png\")", RUN.Data()));
        gROOT->ProcessLine("ht 16 colz");
        gROOT->ProcessLine(Form("artcanvas->Print(\"figure/beam/fit/%s/lowgain1_al25.png\")", RUN.Data()));
        gROOT->ProcessLine("ht 18 colz");
        gROOT->ProcessLine(Form("artcanvas->Print(\"figure/beam/fit/%s/lowgain1_mg24.png\")", RUN.Data()));
        gROOT->ProcessLine("ht 19 colz");
        gROOT->ProcessLine(Form("artcanvas->Print(\"figure/beam/fit/%s/lowgain1_si26_2.png\")", RUN.Data()));

        gROOT->ProcessLine("ht 23 colz");
        gROOT->ProcessLine(Form("artcanvas->Print(\"figure/beam/fit/%s/lowgain2_si26.png\")", RUN.Data()));
        gROOT->ProcessLine("ht 25 colz");
        gROOT->ProcessLine(Form("artcanvas->Print(\"figure/beam/fit/%s/lowgain2_al25.png\")", RUN.Data()));
        gROOT->ProcessLine("ht 27 colz");
        gROOT->ProcessLine(Form("artcanvas->Print(\"figure/beam/fit/%s/lowgain2_mg24.png\")", RUN.Data()));
        gROOT->ProcessLine("ht 28 colz");
        gROOT->ProcessLine(Form("artcanvas->Print(\"figure/beam/fit/%s/lowgain2_si26_2.png\")", RUN.Data()));

        gROOT->ProcessLine("ht 32 colz");
        gROOT->ProcessLine(Form("artcanvas->Print(\"figure/beam/fit/%s/lowgain3_si26.png\")", RUN.Data()));
        gROOT->ProcessLine("ht 34 colz");
        gROOT->ProcessLine(Form("artcanvas->Print(\"figure/beam/fit/%s/lowgain3_al25.png\")", RUN.Data()));
        gROOT->ProcessLine("ht 36 colz");
        gROOT->ProcessLine(Form("artcanvas->Print(\"figure/beam/fit/%s/lowgain3_mg24.png\")", RUN.Data()));
        gROOT->ProcessLine("ht 37 colz");
        gROOT->ProcessLine(Form("artcanvas->Print(\"figure/beam/fit/%s/lowgain3_si26_2.png\")", RUN.Data()));

        gROOT->ProcessLine("zone");
    }

    // return to default
    artcanvas->SetCanvasSize(800,800);
    gROOT->ProcessLine("zone");

}