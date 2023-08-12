{
   Bool_t debug=true;


   for(Int_t i=0; i<16; ++i){
      if(debug){
         gROOT->ProcessLine(Form("tree->Draw(\"tel1_dEX_raw_%d.fCharge>>hx%d(100,0.,500.)\",\"single.fID==0\")", i, i));
      }else{
         gROOT->ProcessLine(Form("tree->Draw(\"tel1_dEX_raw_%d.fCharge>>hx%d(100,0.,500.)\",\"single.fID==0\")", i, i));
      }
   }

   for(Int_t i=0; i<16; ++i){
      if(debug){
         gROOT->ProcessLine(Form("tree->Draw(\"tel1_dEY_raw_%d.fCharge>>hy%d(100,0.,500.)\",\"single.fID==0\")", i, i));
      }else{
         gROOT->ProcessLine(Form("tree->Draw(\"tel1_dEY_raw_%d.fCharge>>hy%d(100,0.,500.)\",\"single.fID==0\")", i, i));
      }
   }

   for(Int_t i=0; i<2; ++i){
      if(debug){
         gROOT->ProcessLine(Form("tree->Draw(\"tel1_E_raw_%d.fCharge>>h%d(100,0.,500.)\",\"single.fID==0\")", i, i));
      }else{
         gROOT->ProcessLine(Form("tree->Draw(\"tel1_E_raw_%d.fCharge>>h%d(100,0.,500.)\",\"single.fID==0\")", i, i));
      }
   }

}
