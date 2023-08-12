// K.Okawa created <okawa@cns.s.u-tokyo.ac.jp>

#include "TSimBeamData.h"

using art::TSimBeamData;

ClassImp(art::TSimBeamData)

TSimBeamData::TSimBeamData()
   :  fTheta(kInvalidD), fPhi(kInvalidD)
{
   TDataObject::SetID(kInvalidI);
}

TSimBeamData::~TSimBeamData()
{
}

TSimBeamData::TSimBeamData(const TSimBeamData& rhs)
   : TTrack(rhs),
     fTheta(rhs.fTheta),
     fPhi(rhs.fPhi)
{ 
}

TSimBeamData& TSimBeamData::operator=(const TSimBeamData& rhs)
{
   if (this != &rhs) {
      ((TSimBeamData&)rhs).Copy(*this);
   }
   return *this;
}

void TSimBeamData::Init()
{
   Clear();
}


void TSimBeamData::Copy(TObject& dest) const
{
   TTrack::Copy(dest);
   TSimBeamData &cobj = *(TSimBeamData*)&dest;

   cobj.fTheta = this->GetTheta();
   cobj.fPhi = this->GetPhi();
}

void TSimBeamData::Clear(Option_t *opt)
{
   TTrack::Clear(opt);
   TDataObject::SetID(kInvalidI);

   fTheta = kInvalidD;
   fPhi = kInvalidD;
}
