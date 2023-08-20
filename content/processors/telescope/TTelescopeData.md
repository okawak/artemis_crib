---
title: "TTelescopeData"
date: 2023-08-18T16:25:33+09:00
draft: false
author: "Kodai Okawa"
weight: 1
tags: ["data_class"]
---

{{% badge %}}{{< signature >}}{{% /badge %}}

under develop (possibly we will update this data class)

## TTelescopeData

- Data members
```cpp
TVector3 fPos; // detected position (x, y, z)
// simulation: actual position
// from data: calculated from strip ID

Int_t fXID; // X strip ID
Int_t fYID; // Y strip ID

Double_t fdE; // total energy deposit of dE detector
Double_t fE; // total energy deposit of E detector
Double_t fEtotal; // total energy deposit of the telescope

DoubleVec_t fEnergyArray; // energy array of all the telescope
// DoubleVec_t fTimingArray; // not impremented

//===============================================================
// no need??
// kMAXNPARAMETER = 4 (can be settable)
Int_t fNE; // number of thick E detector
Double_t fdEX; // energy of the first dE detector
Double_t fdEY; // energy of the seconde dE detector
Double_t fdEXTiming; // timing of the first dE detector
Double_t fdEYTiming; // timing of the second dE detector

Double_t fEvec[kMAXNPARAMETER]; // energy array of the E detector
Double_t fETimingvec[kMAXNPARAMETER]; // timing array of the E detector
```

- Methods
```cpp
TVector3 GetPosition() const { return fPos; }
void SetPosition(TVector3 vec) { fPos = vec; }
void SetPosition(Double_t x, Double_t y, Double_t z) { fPos.SetXYZ(x, y, z); }

Int_t GetXID() const {return fXID;}
void SetXID(Int_t arg) { fXID = arg; }
Int_t GetYID() const {return fYID;}
void SetYID(Int_t arg) { fYID = arg; }

Double_t GetdEX() const {return fdEX;}
void SetdEX(Double_t arg) { fdEX = arg; }
Double_t GetdEY() const {return fdEY;}
void SetdEY(Double_t arg) { fdEY = arg; }

Double_t GetdEXTiming() const {return fdEXTiming;}
void SetdEXTiming(Double_t arg) { fdEXTiming = arg; }
Double_t GetdEYTiming() const {return fdEYTiming;}
void SetdEYTiming(Double_t arg) { fdEYTiming = arg; }

Double_t GetEvec(Int_t idx) const { return fEvec[idx]; }
void SetEvec(Int_t idx, Double_t val) { fEvec[idx] = val; }
Int_t GetEvecSize() { return fNE; }
Double_t GetETimingvec(Int_t idx) const { return fETimingvec[idx]; }
void SetETimingvec(Int_t idx, Double_t val) { fETimingvec[idx] = val; }


Double_t GetdE() const {return fdE;}
void SetdE(Double_t arg) { fdE = arg; }
Double_t GetE() const {return fE;}
void SetE(Double_t arg) { fE = arg; }
Double_t GetEtotal() const {return fEtotal;}
void SetEtotal(Double_t arg) { fEtotal = arg; }

DoubleVec_t GetEnergyArray() const {return fEnergyArray;}
void SetEnergyArray(Double_t arg) { fEnergyArray.emplace_back(arg); }
```
