/**
 * @file    TReactionInfo.cc
 * @brief
 * @author  Kodai Okawa <okawa@cns.s.u-tokyo.ac.jp>
 * @date    2023-08-01 22:28:15
 * @note    last modified: 2024-08-21 17:55:56
 * @details
 */

#include "TReactionInfo.h"
#include <TConverterBase.h>
#include <constant.h>

using art::crib::TReactionInfo;

ClassImp(TReactionInfo);

TReactionInfo::TReactionInfo()
    : fEnergy(kInvalidD),
      fTheta(kInvalidD),
      fX(kInvalidD),
      fY(kInvalidD),
      fZ(kInvalidD),
      fExEnergy(kInvalidD) {
    TDataObject::SetID(kInvalidI);
}

TReactionInfo::~TReactionInfo() {}

TReactionInfo::TReactionInfo(const TReactionInfo &rhs)
    : TDataObject(rhs),
      fEnergy(rhs.fEnergy),
      fTheta(rhs.fTheta),
      fX(rhs.fX),
      fY(rhs.fY),
      fZ(rhs.fZ),
      fExEnergy(rhs.fExEnergy) {
}

TReactionInfo &TReactionInfo::operator=(const TReactionInfo &rhs) {
    if (this != &rhs) {
        ((TReactionInfo &)rhs).Copy(*this);
    }
    return *this;
}

void TReactionInfo::Copy(TObject &dest) const {
    TDataObject::Copy(dest);
    TReactionInfo &cobj = *(TReactionInfo *)&dest;
    cobj.fEnergy = this->GetEnergy();
    cobj.fTheta = this->GetTheta();
    cobj.fX = this->GetX();
    cobj.fY = this->GetY();
    cobj.fZ = this->GetZ();
    cobj.fExEnergy = this->GetExEnergy();
}

void TReactionInfo::Clear(Option_t *opt) {
    TDataObject::Clear(opt);
    TDataObject::SetID(kInvalidI);
    fEnergy = kInvalidD;
    fTheta = kInvalidD;
    fX = kInvalidD;
    fY = kInvalidD;
    fZ = kInvalidD;
    fExEnergy = kInvalidD;
}
