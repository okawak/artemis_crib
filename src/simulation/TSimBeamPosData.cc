// K.Okawa created <okawa@cns.s.u-tokyo.ac.jp>

#include "TSimBeamPosData.h"

using art::TSimBeamPosData;

ClassImp(art::TSimBeamPosData)

TSimBeamPosData::TSimBeamPosData()
   :  fXID(kInvalidI), fYID(kInvalidI), fDistance(kInvalidD)
{
   TDataObject::SetID(kInvalidI);
}

TSimBeamPosData::~TSimBeamPosData()
{
}

TSimBeamPosData::TSimBeamPosData(const TSimBeamPosData& rhs)
   : TDataObject(rhs),
     fXID(rhs.fXID),
     fYID(rhs.fYID),
     fDistance(rhs.fDistance)
{
}

TSimBeamPosData& TSimBeamPosData::operator=(const TSimBeamPosData& rhs)
{
   if (this != &rhs) {
      ((TSimBeamPosData&)rhs).Copy(*this);
   }
   return *this;
}

void TSimBeamPosData::Init()
{
   Clear();
}


void TSimBeamPosData::Copy(TObject& dest) const
{
   TDataObject::Copy(dest);
   TSimBeamPosData &cobj = *(TSimBeamPosData*)&dest;

   cobj.fXID = this->GetXID();
   cobj.fYID = this->GetYID();
   cobj.fDistance = this->GetDistance();
}

void TSimBeamPosData::Clear(Option_t *opt)
{
   TDataObject::Clear(opt);
   TDataObject::SetID(kInvalidI);

   fXID = kInvalidD;
   fYID = kInvalidD;
   fDistance = kInvalidD;
}
