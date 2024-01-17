/**
 * @file    TTelescopeData.cc
 * @brief
 * @author  Kodai Okawa<okawa@cns.s.u-tokyo.ac.jp>
 * @date    2024-01-17 17:14:39
 * @note
 */

#include "TTelescopeData.h"
#include <TConverterBase.h>

using art::TTelescopeData;

ClassImp(art::TTelescopeData);

TTelescopeData::TTelescopeData()
    : fXID(kInvalidI), fYID(kInvalidI), fNE(0),
      fdEX(0.0), fdEY(0.0), fdEXTiming(kInvalidD), fdEYTiming(kInvalidD),
      fdE(0.0), fE(0.0), fEtotal(0.0) {
    TDataObject::SetID(kInvalidI);
    for (Int_t i = 0; i < kMAXNPARAMETER; ++i) {
        fEvec[i] = kInvalidD;
        fETimingvec[i] = kInvalidD;
    }
    fPos.SetXYZ(0., 0., 0.);
    fEnergyArray.clear();
}

TTelescopeData::~TTelescopeData() {
}

TTelescopeData::TTelescopeData(const TTelescopeData &rhs)
    : TDataObject(rhs),
      fPos(rhs.fPos),
      fXID(rhs.fXID),
      fYID(rhs.fYID),
      fNE(rhs.fNE),
      fdEX(rhs.fdEX),
      fdEY(rhs.fdEY),
      fdEXTiming(rhs.fdEXTiming),
      fdEYTiming(rhs.fdEYTiming),
      fdE(rhs.fdE),
      fE(rhs.fE),
      fEnergyArray(rhs.fEnergyArray),
      fEtotal(rhs.fEtotal) {
    for (Int_t i = 0; i < kMAXNPARAMETER; ++i) {
        fEvec[i] = rhs.fEvec[i];
        fETimingvec[i] = rhs.fEvec[i];
    }
}

TTelescopeData &TTelescopeData::operator=(const TTelescopeData &rhs) {
    if (this != &rhs) {
        ((TTelescopeData &)rhs).Copy(*this);
    }
    return *this;
}

void TTelescopeData::Init(const Int_t nE) {
    if (fNE != nE) {
        fNE = nE;
    }
    Clear();
}

void TTelescopeData::Copy(TObject &dest) const {
    TDataObject::Copy(dest);
    TTelescopeData &cobj = *(TTelescopeData *)&dest;

    if (fNE != cobj.fNE) {
        cobj.fNE = fNE;
    }

    cobj.fPos = this->GetPosition();
    cobj.fXID = this->GetXID();
    cobj.fYID = this->GetYID();

    cobj.fdEX = this->GetdEX();
    cobj.fdEY = this->GetdEY();
    cobj.fdEXTiming = this->GetdEXTiming();
    cobj.fdEYTiming = this->GetdEYTiming();

    memcpy(cobj.fEvec, fEvec, sizeof(fEvec));
    memcpy(cobj.fETimingvec, fETimingvec, sizeof(fETimingvec));

    cobj.fdE = this->GetdE();
    cobj.fE = this->GetE();
    cobj.fEtotal = this->GetEtotal();

    cobj.fEnergyArray = this->GetEnergyArray();
}

void TTelescopeData::Clear(Option_t *opt) {
    TDataObject::Clear(opt);
    TDataObject::SetID(kInvalidI);

    fPos.SetXYZ(0., 0., 0.);
    fXID = kInvalidI;
    fYID = kInvalidI;

    fdEX = 0.0;
    fdEY = 0.0;
    fdEXTiming = kInvalidD;
    fdEYTiming = kInvalidD;

    for (Int_t i = 0; i < kMAXNPARAMETER; ++i) {
        fEvec[i] = 0.0;
        fETimingvec[i] = kInvalidD;
    }

    fdE = 0.0;
    fE = 0.0;
    fEtotal = 0.0;
    fEnergyArray.clear();
}
