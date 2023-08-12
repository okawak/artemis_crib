// K.Okawa created <okawa@cns.s.u-tokyo.ac.jp>

#include "TSimResultData.h"

using art::TSimResultData;

ClassImp(art::TSimResultData)

TSimResultData::TSimResultData()
   :  fEtotal(kInvalidD), fTiming(kInvalidD),
      fX(kInvalidD), fY(kInvalidD), fZ(kInvalidD), fTheta(kInvalidD)
{
   TDataObject::SetID(kInvalidI);
}

TSimResultData::~TSimResultData()
{
}

TSimResultData::TSimResultData(const TSimResultData& rhs)
   : TDataObject(rhs),
     fEtotal(rhs.fEtotal),
     fTiming(rhs.fTiming),
     fX(rhs.fX),
     fY(rhs.fY),
     fZ(rhs.fZ),
     fTheta(rhs.fTheta)
{
}

TSimResultData& TSimResultData::operator=(const TSimResultData& rhs)
{
   if (this != &rhs) {
      ((TSimResultData&)rhs).Copy(*this);
   }
   return *this;
}

void TSimResultData::Init()
{
   Clear();
}


void TSimResultData::Copy(TObject& dest) const
{
   TDataObject::Copy(dest);
   TSimResultData &cobj = *(TSimResultData*)&dest;

   cobj.fEtotal = this->GetEtotal();
   cobj.fTiming = this->GetTiming();
   cobj.fX = this->GetX();
   cobj.fY = this->GetY();
   cobj.fZ = this->GetZ();
   cobj.fTheta = this->GetTheta();
}

void TSimResultData::Clear(Option_t *opt)
{
   TDataObject::Clear(opt);
   TDataObject::SetID(kInvalidI);

   fEtotal = kInvalidD;
   fTiming = kInvalidD;
   fX = kInvalidD;
   fY = kInvalidD;
   fZ = kInvalidD;
   fTheta = kInvalidD;
}
