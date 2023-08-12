/*
   @File name     : TUserGeoInitializer.h
   @description   :
   @Author        : Kodai Okawa<okawa@cns.s.u-tokyo.ac.jp>
   @Created date  : 2023-08-01 11:02:44
   @Last modified : 2023-08-01 11:03:06
*/

#ifndef _TUSERGEOINITIALIZER_H_
#define _TUSERGEOINITIALIZER_H_

#include <TClonesArray.h>
#include <TMath.h>
#include <TProcessor.h>
#include <TGeoManager.h>

namespace art {
class TUserGeoInitializer;
}

class TClonesArray;

class art::TUserGeoInitializer : public TProcessor {
public:
   // Default constructor
   TUserGeoInitializer();
   virtual ~TUserGeoInitializer();

   virtual void Init(TEventCollection *col);
   virtual void Process();

protected:
   TGeoManager *fGeom; //!

   TString fFileName;
   TString fPrmName;

   TClonesArray *fParameterArray; //!->

   Double_t deg2rad = TMath::DegToRad();

private:
   void GeometryFromYaml(TString yamlfile);

   // Copy constructor (prohibited)
   TUserGeoInitializer(const TUserGeoInitializer &);
   // Assignment operator (prohibited)
   TUserGeoInitializer &operator=(const TUserGeoInitializer &);

   ClassDef(TUserGeoInitializer, 0)
};

#endif // end of #ifndef _TUSERGEOINITIALIZER_H_
