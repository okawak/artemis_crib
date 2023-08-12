// K.Okawa created <okawa@cns.s.u-tokyo.ac.jp>

#ifndef _TSIMGEOMETRY_H_ 
#define _TSIMGEOMETRY_H_ 

#include "TNamed.h"
#include "IPosition.h"
#include "TVector3.h"

#include <TGeoManager.h>
#include <TGeoMaterial.h>
#include <TGeoMedium.h>
#include <TGeoVolume.h>
//#include <TGeometry.h>
//#include <TGeoMatrix.h>
//#include <TGeoNode.h>
//#include <TGeoPatternFinder.h>
//#include <TGeoNavigator.h>

namespace art {
   class TSimGeometry;
}

class art::TSimGeometry : public TObject {
public:
   TSimGeometry();
   virtual ~TSimGeometry();

   void GeometrySet(Int_t layer, Bool_t make_fig);

   Double_t Getltar() const { return ltar; }

protected:
   // Number of Telescopes
   static const Int_t DETECTORNUM = 5;

   TGeoManager *sc;
   TGeoMaterial *matVacuum;
   TGeoMaterial *matSi;
   TGeoMedium *Vacuum;
   TGeoMedium *Si;
   TGeoVolume *top;
   TGeoVolume *psd[DETECTORNUM];
   TGeoCombiTrans *posdet[DETECTORNUM];
   TVector3 vdet[DETECTORNUM];
   TVector3 voff[DETECTORNUM];

private:
   // Scattering Chamber Size
   const Double_t wtar = 320.; // in mm xaxis
   const Double_t htar = 100.; // in mm yaxis
   const Double_t ltar = 644.; // in mm zaxis

   // Detector(psd) Size {tel1, tel2. tel3, tel4, tel5}
   const Double_t wpsd_size[DETECTORNUM] = {50., 50., 50., 50., 50.}; // in mm xaxis
   const Double_t hpsd_size[DETECTORNUM] = {50., 50., 50., 50., 50.}; // in mm yaxis
   const Double_t lpsd_size[DETECTORNUM] = {1., 1., 1., 1., 1.}; // in mm zaxis (no need)

   // Detector(psd) Position
   const Double_t thdet[DETECTORNUM] = {-4., 27., -48., 62., -73.}; // in deg
   const Double_t ldet_1st[DETECTORNUM] = {239.5, 149.5, 110., 113.5, 112.5}; // distance between the origin of the rotation and 1st layer positions (beam check)
   const Double_t ldet_2nd[DETECTORNUM] = {244., 154.5, 115., 117.5, 115.5}; // distance between the origin of the rotation and 2nd layer positions (for PI)
   const Double_t ldet_3rd[DETECTORNUM] = {252.5, 161.5, 122., 121., 122.}; // distance between the origin of the rotation and 2nd layer positions (for PI)
   const Double_t x_off[DETECTORNUM] = {0., 0., 0., 0., 0.}; // for origin of the rotation
   const Double_t y_off[DETECTORNUM] = {0., 0., 0., 0., 0.}; // for origin of the rotation
   const Double_t z_off[DETECTORNUM] = {999., 999., 999., 949., 899.}; // for origin of the rotation
   const Double_t xdet_off[DETECTORNUM] = {0., 0., -0.3, 0.4, 0.}; // along the detector surface
   const Double_t ydet_off[DETECTORNUM] = {0., 0., 0., 0., 0.}; // along the detector surface
   const Double_t zdet_off[DETECTORNUM] = {0., 0., 0., 0., 0.}; // along ldet direction



   ClassDef(TSimGeometry,1) // ppac parameter holder
};

#endif // _TSIMGEOMETRY_H_
