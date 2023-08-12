/*
   @File name     : TDetectorParameter.h
   @description   :
   @Author        : Kodai Okawa<okawa@cns.s.u-tokyo.ac.jp>
   @Created date  : 2023-08-01 11:01:52
   @Last modified : 2023-08-01 11:02:13
*/

#ifndef _TDETECTORPARAMETER_H_
#define _TDETECTORPARAMETER_H_

#include <TParameterObject.h>

namespace art {
class TDetectorParameter;
}

class art::TDetectorParameter : public TParameterObject {
public:
   TDetectorParameter();
   virtual ~TDetectorParameter();

   TDetectorParameter(const TDetectorParameter &rhs);
   TDetectorParameter &operator=(const TDetectorParameter &rhs);

   TString GetMaterial(Int_t id) const { return fMaterial[id]; }
   StringVec_t GetMaterial() const { return fMaterial; }
   void SetMaterial(StringVec_t vec) { fMaterial = vec; }
   Double_t GetThickness(Int_t id) const { return fThickness[id]; }
   void SetThickness(DoubleVec_t vec) { fThickness = vec; }

   Double_t GetCenterRotPos(Int_t id) const { return fCenterRot[id]; }
   void SetCenterRotPos(DoubleVec_t vec) { fCenterRot = vec; }
   Double_t GetOffset(Int_t id) const { return fOffset[id]; }
   void SetOffset(DoubleVec_t vec) { fOffset = vec; }

   Double_t GetSize(Int_t id) const { return fSize[id]; }
   void SetSize(DoubleVec_t vec) { fSize = vec; }
   Int_t GetStripNum(Int_t id) const { return fStrip[id]; }
   void SetStripNum(IntVec_t vec) { fStrip = vec; }

   Double_t GetDistance() const { return fDistance; }
   void SetDistance(Double_t val) { fDistance = val; }
   Double_t GetAngle() const { return fAngle; }
   void SetAngle(Double_t val) { fAngle = val; }
   Double_t GetMaxRadius() const { return fMaxRadius; }
   void SetMaxRadius(Double_t val) { fMaxRadius = val; }

protected:
   StringVec_t fMaterial;  //!
   DoubleVec_t fThickness; //!

   DoubleVec_t fCenterRot; //!
   DoubleVec_t fOffset;    //!

   DoubleVec_t fSize;      //!
   IntVec_t fStrip;        //!

   Double_t fDistance;
   Double_t fAngle; // radian
   Double_t fMaxRadius;

private:
   ClassDef(TDetectorParameter, 1) // ppac parameter holder
};

#endif // end of #ifndef _TDETECTORPARAMETER_H_
