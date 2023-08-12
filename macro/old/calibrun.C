{
    const TString ARTEMIS_WORKDIR = "/home/okawa/art_analysis/user/okawa";

    const TString RUN = "test";
    Bool_t debug = true;

    // for telescope 1,2,3
    //const Double_t proton_loss[4] = {0.10193, 2.68655, 12.76664, 3.43072};
    //const Double_t alpha_loss[4] = {1.19466, 17.67012, 0.0, 0.0};

    // for telescope 4,5
    const Double_t proton_loss[3] = {0.77892, 7.04208, 0.0};
    const Double_t alpha_loss[3] = {7.09628, 0.0, 0.0};


    gROOT->ProcessLine("fcd 0");
    gROOT->ProcessLine(".x macro/setalias.C");
    gROOT->ProcessLine("zone");


    //========================TEL 5===========================
    // proton
    //for(Int_t i=0; i<16; ++i){
    //    if(debug){
    //        gROOT->ProcessLine(Form("tree->Draw(\"tel5_dEX_cal_raw_%d.fCharge>>hx%d_p(100,0.,4000.)\",\"proton\")", i, i));
    //    }else{
    //        gROOT->ProcessLine(Form("tree->Draw(\"tel5_dEX_cal_raw_%d.fCharge>>hx%d_p(50,0.,500.)\",\"proton\")", i, i));
    //        gROOT->ProcessLine(Form(".x %s/macro/GausFit.C(hx%d_p, \"tel5/proton%s_dEX_%d\", %g, 0.0)", ARTEMIS_WORKDIR.Data(), i, RUN.Data(), i, proton_loss[0]));
    //    }
    //}

    //for(Int_t i=0; i<16; ++i){
    //    if(debug){
    //        gROOT->ProcessLine(Form("tree->Draw(\"tel5_dEY_cal_raw_%d.fCharge>>hy%d_p(100,100.,4000.)\",\"proton\")", i, i));
    //    }else{
    //        gROOT->ProcessLine(Form("tree->Draw(\"tel5_dEY_cal_raw_%d.fCharge>>hy%d_p(50,0.,500.)\",\"proton\")", i, i));
    //        gROOT->ProcessLine(Form(".x %s/macro/GausFit.C(hy%d_p, \"tel5/proton%s_dEY_%d\", %g, 0.0)", ARTEMIS_WORKDIR.Data(), i, RUN.Data(), i, proton_loss[0]));
    //    }
    //}

    //for(Int_t i=0; i<2; ++i){
    //    if(debug){
    //        gROOT->ProcessLine(Form("tree->Draw(\"tel5_E_raw_%d.fCharge>>h%d_p(100,0.,4000.)\",\"proton\")", i, i));
    //    }else{
    //        gROOT->ProcessLine(Form("tree->Draw(\"tel5_E_raw_%d.fCharge>>h%d_p(100,500.,1500.)\",\"proton\")", i, i));
    //        gROOT->ProcessLine(Form(".x %s/macro/GausFit.C(h%d_p, \"tel5/proton%s_E_%d\", %g, 0.0)", ARTEMIS_WORKDIR.Data(), i, RUN.Data(), i, proton_loss[i+1]));
    //    }
    //}

    //// alpha
    //for(Int_t i=0; i<16; ++i){
    //    if(debug){
    //        gROOT->ProcessLine(Form("tree->Draw(\"tel5_dEX_cal_raw_%d.fCharge>>hx%d_a(100,0.,4000.)\",\"alpha\")", i, i));
    //    }else{
    //        gROOT->ProcessLine(Form("tree->Draw(\"tel5_dEX_cal_raw_%d.fCharge>>hx%d_a(70,1000.,2000.)\",\"alpha\")", i, i));
    //        gROOT->ProcessLine(Form(".x %s/macro/GausFit.C(hx%d_a, \"tel5/alpha%s_dEX_%d\", %g, 0.0)", ARTEMIS_WORKDIR.Data(), i, RUN.Data(), i, alpha_loss[0]));
    //    }
    //}

    //for(Int_t i=0; i<16; ++i){
    //    if(debug){
    //        gROOT->ProcessLine(Form("tree->Draw(\"tel5_dEY_cal_raw_%d.fCharge>>hy%d_a(100,100.,4000.)\",\"alpha\")", i, i));
    //    }else{
    //        gROOT->ProcessLine(Form("tree->Draw(\"tel5_dEY_cal_raw_%d.fCharge>>hy%d_a(70,1000.,2000.)\",\"alpha\")", i, i));
    //        gROOT->ProcessLine(Form(".x %s/macro/GausFit.C(hy%d_a, \"tel5/alpha%s_dEY_%d\", %g, 0.0)", ARTEMIS_WORKDIR.Data(), i, RUN.Data(), i, alpha_loss[0]));
    //    }
    //}

    //for(Int_t i=0; i<2; ++i){
    //    if(debug){
    //        gROOT->ProcessLine(Form("tree->Draw(\"tel5_E_raw_%d.fCharge>>h%d_a(100,0.,4000.)\",\"alpha\")", i, i));
    //    }else{
    //        gROOT->ProcessLine(Form("tree->Draw(\"tel5_E_raw_%d.fCharge>>h%d_a(100,2000.,3000.)\",\"alpha\")", i, i));
    //        gROOT->ProcessLine(Form(".x %s/macro/GausFit.C(h%d_a, \"tel5/alpha%s_E_%d\", %g, 0.0)", ARTEMIS_WORKDIR.Data(), i, RUN.Data(), i, alpha_loss[i+1]));
    //    }
    //}


    //========================================================


    //========================TEL 4===========================
    // proton
    //for(Int_t i=0; i<16; ++i){
    //    if(debug){
    //        gROOT->ProcessLine(Form("tree->Draw(\"tel4_dEX_cal_raw_%d.fCharge>>hx%d_p(100,0.,4000.)\",\"proton\")", i, i));
    //    }else{
    //        gROOT->ProcessLine(Form("tree->Draw(\"tel4_dEX_cal_raw_%d.fCharge>>hx%d_p(25,0.,500.)\",\"proton\")", i, i));
    //        gROOT->ProcessLine(Form(".x %s/macro/GausFit.C(hx%d_p, \"tel4/proton%s_dEX_%d\", %g, 0.0)", ARTEMIS_WORKDIR.Data(), i, RUN.Data(), i, proton_loss[0]));
    //    }
    //}

    //for(Int_t i=0; i<16; ++i){
    //    if(debug){
    //        gROOT->ProcessLine(Form("tree->Draw(\"tel4_dEY_cal_raw_%d.fCharge>>hy%d_p(100,100.,4000.)\",\"proton\")", i, i));
    //    }else{
    //        gROOT->ProcessLine(Form("tree->Draw(\"tel4_dEY_cal_raw_%d.fCharge>>hy%d_p(50,0.,500.)\",\"proton\")", i, i));
    //        gROOT->ProcessLine(Form(".x %s/macro/GausFit.C(hy%d_p, \"tel4/proton%s_dEY_%d\", %g, 0.0)", ARTEMIS_WORKDIR.Data(), i, RUN.Data(), i, proton_loss[0]));
    //    }
    //}

    //for(Int_t i=0; i<2; ++i){
    //    if(debug){
    //        gROOT->ProcessLine(Form("tree->Draw(\"tel4_E_raw_%d.fCharge>>h%d_p(100,0.,4000.)\",\"proton\")", i, i));
    //    }else{
    //        gROOT->ProcessLine(Form("tree->Draw(\"tel4_E_raw_%d.fCharge>>h%d_p(100,500.,1500.)\",\"proton\")", i, i));
    //        gROOT->ProcessLine(Form(".x %s/macro/GausFit.C(h%d_p, \"tel4/proton%s_E_%d\", %g, 0.0)", ARTEMIS_WORKDIR.Data(), i, RUN.Data(), i, proton_loss[i+1]));
    //    }
    //}

    //// alpha
    //for(Int_t i=0; i<16; ++i){
    //    if(debug){
    //        gROOT->ProcessLine(Form("tree->Draw(\"tel4_dEX_cal_raw_%d.fCharge>>hx%d_a(100,0.,4000.)\",\"alpha\")", i, i));
    //    }else{
    //        gROOT->ProcessLine(Form("tree->Draw(\"tel4_dEX_cal_raw_%d.fCharge>>hx%d_a(70,1000.,2000.)\",\"alpha\")", i, i));
    //        gROOT->ProcessLine(Form(".x %s/macro/GausFit.C(hx%d_a, \"tel4/alpha%s_dEX_%d\", %g, 0.0)", ARTEMIS_WORKDIR.Data(), i, RUN.Data(), i, alpha_loss[0]));
    //    }
    //}

    //for(Int_t i=0; i<16; ++i){
    //    if(debug){
    //        gROOT->ProcessLine(Form("tree->Draw(\"tel4_dEY_cal_raw_%d.fCharge>>hy%d_a(100,100.,4000.)\",\"alpha\")", i, i));
    //    }else{
    //        gROOT->ProcessLine(Form("tree->Draw(\"tel4_dEY_cal_raw_%d.fCharge>>hy%d_a(50,500.,1500.)\",\"alpha\")", i, i));
    //        gROOT->ProcessLine(Form(".x %s/macro/GausFit.C(hy%d_a, \"tel4/alpha%s_dEY_%d\", %g, 0.0)", ARTEMIS_WORKDIR.Data(), i, RUN.Data(), i, alpha_loss[0]));
    //    }
    //}

    //for(Int_t i=0; i<2; ++i){
    //    if(debug){
    //        gROOT->ProcessLine(Form("tree->Draw(\"tel4_E_raw_%d.fCharge>>h%d_a(100,0.,4000.)\",\"alpha\")", i, i));
    //    }else{
    //        gROOT->ProcessLine(Form("tree->Draw(\"tel4_E_raw_%d.fCharge>>h%d_a(100,500.,1500.)\",\"alpha\")", i, i));
    //        gROOT->ProcessLine(Form(".x %s/macro/GausFit.C(h%d_a, \"tel4/alpha%s_E_%d\", %g, 0.0)", ARTEMIS_WORKDIR.Data(), i, RUN.Data(), i, alpha_loss[i+1]));
    //    }
    //}


    //========================================================


    //========================TEL 3===========================
    // proton
    //for(Int_t i=0; i<16; ++i){
    //    if(debug){
    //        gROOT->ProcessLine(Form("tree->Draw(\"tel3_dEX_cal_raw_%d.fCharge>>hx%d_p(100,0.,500.)\",\"proton\")", i, i));
    //    }else{
    //        gROOT->ProcessLine(Form("tree->Draw(\"tel3_dEX_cal_raw_%d.fCharge>>hx%d_p(100,0.,500.)\",\"proton\")", i, i));
    //        gROOT->ProcessLine(Form(".x %s/macro/GausFit.C(hx%d_p, \"tel3/proton%s_dEX_%d\", %g, 0.0)", ARTEMIS_WORKDIR.Data(), i, RUN.Data(), i, proton_loss[0]));
    //    }
    //}

    //for(Int_t i=0; i<16; ++i){
    //    if(debug){
    //        gROOT->ProcessLine(Form("tree->Draw(\"tel3_dEY_raw_%d.fCharge>>hy%d_p(100,100.,4000.)\",\"proton\")", i, i));
    //    }else{
    //        gROOT->ProcessLine(Form("tree->Draw(\"tel3_dEY_raw_%d.fCharge>>hy%d_p(50,200.,600.)\",\"proton\")", i, i));
    //        gROOT->ProcessLine(Form(".x %s/macro/GausFit.C(hy%d_p, \"tel3/proton%s_dEY_%d\", %g, 0.0)", ARTEMIS_WORKDIR.Data(), i, RUN.Data(), i, proton_loss[1]));
    //    }
    //}

    //for(Int_t i=0; i<2; ++i){
    //    if(debug){
    //        gROOT->ProcessLine(Form("tree->Draw(\"tel3_E_raw_%d.fCharge>>h%d_p(100,0.,4000.)\",\"proton\")", i, i));
    //    }else{
    //        gROOT->ProcessLine(Form("tree->Draw(\"tel3_E_raw_%d.fCharge>>h%d_p(200,500.,2000.)\",\"proton\")", i, i));
    //        gROOT->ProcessLine(Form(".x %s/macro/GausFit.C(h%d_p, \"tel3/proton%s_E_%d\", %g, 0.0)", ARTEMIS_WORKDIR.Data(), i, RUN.Data(), i, proton_loss[i+2]));
    //    }
    //}

    //// alpha
    //for(Int_t i=0; i<16; ++i){
    //    if(debug){
    //        gROOT->ProcessLine(Form("tree->Draw(\"tel3_dEX_cal_raw_%d.fCharge>>hx%d_a(100,0.,4000.)\",\"alpha\")", i, i));
    //    }else{
    //        gROOT->ProcessLine(Form("tree->Draw(\"tel3_dEX_cal_raw_%d.fCharge>>hx%d_a(50,0.,500.)\",\"alpha\")", i, i));
    //        gROOT->ProcessLine(Form(".x %s/macro/GausFit.C(hx%d_a, \"tel3/alpha%s_dEX_%d\", %g, 0.0)", ARTEMIS_WORKDIR.Data(), i, RUN.Data(), i, alpha_loss[0]));
    //    }
    //}

    //for(Int_t i=0; i<16; ++i){
    //    if(debug){
    //        gROOT->ProcessLine(Form("tree->Draw(\"tel3_dEY_raw_%d.fCharge>>hy%d_a(100,100.,4000.)\",\"alpha\")", i, i));
    //    }else{
    //        gROOT->ProcessLine(Form("tree->Draw(\"tel3_dEY_raw_%d.fCharge>>hy%d_a(100,2000.,3000.)\",\"alpha\")", i, i));
    //        gROOT->ProcessLine(Form(".x %s/macro/GausFit.C(hy%d_a, \"tel3/alpha%s_dEY_%d\", %g, 0.0)", ARTEMIS_WORKDIR.Data(), i, RUN.Data(), i, alpha_loss[1]));
    //    }
    //}

    //for(Int_t i=0; i<2; ++i){
    //    if(debug){
    //        gROOT->ProcessLine(Form("tree->Draw(\"tel3_E_raw_%d.fCharge>>h%d_a(100,0.,4000.)\",\"alpha\")", i, i));
    //    }else{
    //        gROOT->ProcessLine(Form("tree->Draw(\"tel3_E_raw_%d.fCharge>>h%d_a(100,10.,4000.)\",\"alpha\")", i, i));
    //        gROOT->ProcessLine(Form(".x %s/macro/GausFit.C(h%d_a, \"tel3/alpha%s_E_%d\", %g, 0.0)", ARTEMIS_WORKDIR.Data(), i, RUN.Data(), i, alpha_loss[i+2]));
    //    }
    //}


    //========================================================


    //========================TEL 2===========================
    // proton
    //for(Int_t i=0; i<16; ++i){
    //    if(debug){
    //        gROOT->ProcessLine(Form("tree->Draw(\"tel2_dEX_cal_raw_%d.fCharge>>hx%d_p(100,0.,500.)\",\"proton\")", i, i));
    //    }else{
    //        gROOT->ProcessLine(Form("tree->Draw(\"tel2_dEX_cal_raw_%d.fCharge>>hx%d_p(100,0.,500.)\",\"proton\")", i, i));
    //        gROOT->ProcessLine(Form(".x %s/macro/GausFit.C(hx%d_p, \"tel2/proton%s_dEX_%d\", %g, 0.0)", ARTEMIS_WORKDIR.Data(), i, RUN.Data(), i, proton_loss[0]));
    //    }
    //}

    //for(Int_t i=0; i<16; ++i){
    //    if(debug){
    //        gROOT->ProcessLine(Form("tree->Draw(\"tel2_dEY_raw_%d.fCharge>>hy%d_p(100,0.,4000.)\",\"proton\")", i, i));
    //    }else{
    //        gROOT->ProcessLine(Form("tree->Draw(\"tel2_dEY_raw_%d.fCharge>>hy%d_p(50,0.,500.)\",\"proton\")", i, i));
    //        gROOT->ProcessLine(Form(".x %s/macro/GausFit.C(hy%d_p, \"tel2/proton%s_dEY_%d\", %g, 0.0)", ARTEMIS_WORKDIR.Data(), i, RUN.Data(), i, proton_loss[1]));
    //    }
    //}

    //for(Int_t i=0; i<2; ++i){
    //    if(debug){
    //        gROOT->ProcessLine(Form("tree->Draw(\"tel2_E_raw_%d.fCharge>>h%d_p(100,0.,4000.)\",\"proton\")", i, i));
    //    }else{
    //        gROOT->ProcessLine(Form("tree->Draw(\"tel2_E_raw_%d.fCharge>>h%d_p(200,1000.,2500.)\",\"proton\")", i, i));
    //        gROOT->ProcessLine(Form(".x %s/macro/GausFit.C(h%d_p, \"tel2/proton%s_E_%d\", %g, 0.0)", ARTEMIS_WORKDIR.Data(), i, RUN.Data(), i, proton_loss[i+2]));
    //    }
    //}

    //// alpha
    //for(Int_t i=0; i<16; ++i){
    //    if(debug){
    //        gROOT->ProcessLine(Form("tree->Draw(\"tel2_dEX_cal_raw_%d.fCharge>>hx%d_a(100,0.,4000.)\",\"alpha\")", i, i));
    //    }else{
    //        gROOT->ProcessLine(Form("tree->Draw(\"tel2_dEX_cal_raw_%d.fCharge>>hx%d_a(100,0.,1000.)\",\"alpha\")", i, i));
    //        gROOT->ProcessLine(Form(".x %s/macro/GausFit.C(hx%d_a, \"tel2/alpha%s_dEX_%d\", %g, 0.0)", ARTEMIS_WORKDIR.Data(), i, RUN.Data(), i, alpha_loss[0]));
    //    }
    //}

    //for(Int_t i=0; i<16; ++i){
    //    if(debug){
    //        gROOT->ProcessLine(Form("tree->Draw(\"tel2_dEY_raw_%d.fCharge>>hy%d_a(100,0.,4000.)\",\"alpha\")", i, i));
    //    }else{
    //        gROOT->ProcessLine(Form("tree->Draw(\"tel2_dEY_raw_%d.fCharge>>hy%d_a(100,2000.,2500.)\",\"alpha\")", i, i));
    //        gROOT->ProcessLine(Form(".x %s/macro/GausFit.C(hy%d_a, \"tel2/alpha%s_dEY_%d\", %g, 0.0)", ARTEMIS_WORKDIR.Data(), i, RUN.Data(), i, alpha_loss[1]));
    //    }
    //}

    //for(Int_t i=0; i<2; ++i){
    //    if(debug){
    //        gROOT->ProcessLine(Form("tree->Draw(\"tel2_E_raw_%d.fCharge>>h%d_a(100,0.,4000.)\",\"alpha\")", i, i));
    //    }else{
    //        gROOT->ProcessLine(Form("tree->Draw(\"tel2_E_raw_%d.fCharge>>h%d_a(100,10.,4000.)\",\"alpha\")", i, i));
    //        gROOT->ProcessLine(Form(".x %s/macro/GausFit.C(h%d_a, \"tel2/alpha%s_E_%d\", %g, 0.0)", ARTEMIS_WORKDIR.Data(), i, RUN.Data(), i, alpha_loss[i+2]));
    //    }
    //}


    //========================================================


    //========================TEL 1===========================
    // proton
    for(Int_t i=0; i<16; ++i){
        if(debug){
            gROOT->ProcessLine(Form("tree->Draw(\"tel1_dEX_raw_%d.fCharge>>hx%d_p(100,0.,500.)\",\"proton\")", i, i));
        }else{
            gROOT->ProcessLine(Form("tree->Draw(\"tel1_dEX_raw_%d.fCharge>>hx%d_p(100,0.,500.)\",\"proton\")", i, i));
            gROOT->ProcessLine(Form(".x %s/macro/GausFit.C(hx%d_p, \"tel1/proton%s_dEX_%d\", %g, 0.0)", ARTEMIS_WORKDIR.Data(), i, RUN.Data(), i, proton_loss[0]));
        }
    }

    for(Int_t i=0; i<16; ++i){
        if(debug){
            gROOT->ProcessLine(Form("tree->Draw(\"tel1_dEY_raw_%d.fCharge>>hy%d_p(100,0.,4000.)\",\"proton\")", i, i));
        }else{
            gROOT->ProcessLine(Form("tree->Draw(\"tel1_dEY_raw_%d.fCharge>>hy%d_p(50,500.,1000.)\",\"proton\")", i, i));
            gROOT->ProcessLine(Form(".x %s/macro/GausFit.C(hy%d_p, \"tel1/proton%s_dEY_%d\", %g, 0.0)", ARTEMIS_WORKDIR.Data(), i, RUN.Data(), i, proton_loss[1]));
        }
    }

    for(Int_t i=0; i<2; ++i){
        if(debug){
            gROOT->ProcessLine(Form("tree->Draw(\"tel1_E_raw_%d.fCharge>>h%d_p(100,0.,4000.)\",\"proton\")", i, i));
        }else{
            gROOT->ProcessLine(Form("tree->Draw(\"tel1_E_raw_%d.fCharge>>h%d_p(100,1000.,2500.)\",\"proton\")", i, i));
            gROOT->ProcessLine(Form(".x %s/macro/GausFit.C(h%d_p, \"tel1/proton%s_E_%d\", %g, 0.0)", ARTEMIS_WORKDIR.Data(), i, RUN.Data(), i, proton_loss[i+2]));
        }
    }

    // alpha
    for(Int_t i=0; i<16; ++i){
        if(debug){
            gROOT->ProcessLine(Form("tree->Draw(\"tel1_dEX_raw_%d.fCharge>>hx%d_a(100,0.,4000.)\",\"alpha\")", i, i));
        }else{
            gROOT->ProcessLine(Form("tree->Draw(\"tel1_dEX_raw_%d.fCharge>>hx%d_a(50,0.,1000.)\",\"alpha\")", i, i));
            gROOT->ProcessLine(Form(".x %s/macro/GausFit.C(hx%d_a, \"tel1/alpha%s_dEX_%d\", %g, 0.0)", ARTEMIS_WORKDIR.Data(), i, RUN.Data(), i, alpha_loss[0]));
        }
    }

    for(Int_t i=0; i<16; ++i){
        if(debug){
            gROOT->ProcessLine(Form("tree->Draw(\"tel1_dEY_raw_%d.fCharge>>hy%d_a(100,0.,4000.)\",\"alpha\")", i, i));
        }else{
            gROOT->ProcessLine(Form("tree->Draw(\"tel1_dEY_raw_%d.fCharge>>hy%d_a(100,2000.,3000.)\",\"alpha\")", i, i));
            gROOT->ProcessLine(Form(".x %s/macro/GausFit.C(hy%d_a, \"tel1/alpha%s_dEY_%d\", %g, 0.0)", ARTEMIS_WORKDIR.Data(), i, RUN.Data(), i, alpha_loss[1]));
        }
    }

    for(Int_t i=0; i<2; ++i){
        if(debug){
            gROOT->ProcessLine(Form("tree->Draw(\"tel1_E_raw_%d.fCharge>>h%d_a(100,0.,4000.)\",\"alpha\")", i, i));
        }else{
            gROOT->ProcessLine(Form("tree->Draw(\"tel1_E_raw_%d.fCharge>>h%d_a(100,10.,4000.)\",\"alpha\")", i, i));
            gROOT->ProcessLine(Form(".x %s/macro/GausFit.C(h%d_a, \"tel1/alpha%s_E_%d\", %g, 0.0)", ARTEMIS_WORKDIR.Data(), i, RUN.Data(), i, alpha_loss[i+2]));
        }
    }


    //========================================================

}