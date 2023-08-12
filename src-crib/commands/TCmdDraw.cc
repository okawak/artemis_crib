/*
   @File name     : TCmdDraw.cc
   @description   :
   @Author        : Kodai Okawa<okawa@cns.s.u-tokyo.ac.jp>
   @Created date  : 2023-06-13 17:51:08
   @Last modified : 2023-06-13 17:52:00
*/

#include "TCmdDraw.h"

#include <TCatPadManager.h>
#include <TCatHistManager.h>

#include <TPad.h>
#include <TF1.h>
#include <TROOT.h>
#include <TLine.h>
#include <TView3D.h>

#include <TH1.h>
#include <TH2.h>

using art::TCmdDraw;

ClassImp(TCmdDraw);

const char *TCmdDraw::kFuncNameBase = "f";
const char *TCmdDraw::kLabelNameBase = "l";

TCmdDraw::TCmdDraw()
{
   SetName("draw");
   SetTitle("drawing object");
}

TCmdDraw::~TCmdDraw() {}

Long_t TCmdDraw::Cmd(vector<TString> tokens)
{
   Int_t n = tokens.size();
   Int_t id;
   if (n==1) {
      id = TCatHistManager::Instance()->GetId();
   }else{
      id = tokens[1].Atoi();
   }

   TObject *obj = TCatHistManager::Instance()->GetObject(id);
   if(obj && (obj->InheritsFrom("TH1") || obj->InheritsFrom("TGraph"))){
      TCatHistManager::Instance()->DrawObject(id, tokens.size() > 2 ? tokens[2] : "");
      return 1; 
   }else if(obj && obj->InheritsFrom("TGeoVolume")){
      TCatPadManager::Instance()->GetCanvas();
      TView3D *vw1 = (TView3D*)TView::CreateView(1);
      vw1->SetRange(-500.,-500.,-500.,500.,500.,500.);
      vw1->SetPerspective();
      vw1->ShowAxis();
      TCatHistManager::Instance()->DrawObject(id, tokens.size() > 2 ? tokens[2] : "same");
      gPad->Update();
      return 1;
   }else{
      std::cout << "Invalid object" << std::endl;
   }


   return 1;
}

void TCmdDraw::Help()
{
   std::cout << "almost same with ht command"
             << "(to draw TGeo object)"
             << std::endl;
}
