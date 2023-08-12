// K.Okawa created <okawa@cns.s.u-tokyo.ac.jp>

#include "TSimGeometry.h"
#include "TSimUtil.h"

// for figure
#include <TCanvas.h>
#include <TView3D.h>
#include <TSystem.h>

#include <iostream>

using art::TSimGeometry;

ClassImp(TSimGeometry)

TSimGeometry::TSimGeometry()
{
}

TSimGeometry::~TSimGeometry()
{
}




void TSimGeometry::GeometrySet(Int_t layer, Bool_t make_fig)
{
   if(layer != 1 && layer != 2 && layer != 3){
      std::cout << "[Error] in TSimGeometry input the layer number" << std::endl;
      return;
   }

   sc = new TGeoManager("scatcham", "Scattering Chamber");

   matVacuum = new TGeoMaterial("Vacuum", 0.0, 0, 0.0);
   matSi = new TGeoMaterial("Si", 28.086, 14, 2.321);

   Vacuum = new TGeoMedium("Vacuum", 1, matVacuum);
   Si = new TGeoMedium("Root Material", 2, matSi);

   top = sc->MakeBox("TOP", Vacuum, wtar/2.0, htar/2.0, ltar/2.0);
   sc->SetTopVolume(top);

   Double_t theta_rad[DETECTORNUM], ldet[DETECTORNUM];
   for(Int_t idet=0; idet<DETECTORNUM; idet++){
      theta_rad[idet] = thdet[idet] * art::Sim::deg_to_rad;
      if(layer == 1) ldet[idet] = ldet_1st[idet];
      else if(layer == 2) ldet[idet] = ldet_2nd[idet];
      else if(layer == 3) ldet[idet] = ldet_3rd[idet];
      else return;
   }

   for(Int_t idet=0; idet<DETECTORNUM; idet++){
      psd[idet] = sc->MakeBox("PSD", Si, wpsd_size[idet], hpsd_size[idet], lpsd_size[idet]);
      vdet[idet].SetXYZ(x_off[idet] + (ldet[idet] + zdet_off[idet])*TMath::Sin(theta_rad[idet]) + xdet_off[idet]*TMath::Cos(theta_rad[idet]),
		                   y_off[idet],
		                   z_off[idet] + (ldet[idet] + zdet_off[idet])*TMath::Cos(theta_rad[idet]) - xdet_off[idet]*TMath::Sin(theta_rad[idet]) );

      // ????????????
      posdet[idet] = new TGeoCombiTrans(vdet[idet].X(), vdet[idet].Y(), vdet[idet].Z(), new TGeoRotation(Form("rot%d",idet),90,thdet[idet],0));
      top->AddNode(psd[idet], idet, posdet[idet]);
   }

   gGeoManager->CloseGeometry();
   gGeoManager->SetTopVisible();
   top->SetLineColor(kRed);

   if(make_fig){
      TCanvas *c0 = new TCanvas("c0","c0", 0, 0, 1000, 1000);
      c0->Divide(2,2);

      c0->cd(1);
      TView3D *vw1 = (TView3D*)TView::CreateView(1);
      vw1->SetRange(-ltar/2.,-ltar/2.,-ltar/2.,ltar/2.,ltar/2.,ltar/2.);
      vw1->SetPerspective();
      vw1->ShowAxis();
      top->Draw("same");

      c0->cd(2);
      TView3D *vw2 = (TView3D*)TView::CreateView(1);
      vw2->SetRange(-ltar/2.,-ltar/2.,-ltar/2.,ltar/2.,ltar/2.,ltar/2.);
      vw2->Front();
      vw2->ShowAxis();
      vw2->SetPerspective();
      top->Draw("same");

      c0->cd(3);
      TView3D *vw3 = (TView3D*)TView::CreateView(1);
      vw3->SetRange(-ltar/2.,-ltar/2.,-ltar/2.,ltar/2.,ltar/2.,ltar/2.);
      vw3->Top();
      vw3->ShowAxis();    
      vw3->SetPerspective();
      top->Draw("same");
  
      c0->cd(4);
      TView3D *vw4 = (TView3D*)TView::CreateView(1);
      vw4->SetRange(-ltar/2.,-ltar/2.,-ltar/2.,ltar/2.,ltar/2.,ltar/2.);
      vw4->Side();
      vw4->ShowAxis();    
      vw4->SetPerspective();
      top->Draw("same");
  
      c0->Update(); 
      gSystem->ProcessEvents();
      c0->Print("c1.png");
   }

}
