---
title: "TParticleInfo"
date: 2023-08-18T15:59:35+09:00
draft: false
author: "Kodai Okawa"
weight: 1
tags: ["data_class"]
---

## TParticleInfo

- Data member
```cpp { lineNos="true" wrap="true" title="TParticleInfo.cc" }
Int_t fMassNumber; // A: particle mass number
Int_t fAtomicNumber; // Z: particle atomic number
Int_t fCharge; // Q: particle charge

Double_t fCurrentZ; // particle z position
Double_t fEnergy; // particle "kinetic" energy

TTrack fTrack; // tracking information
TLorentzVector fVec; // relativistic momentum and energy
```

- Method (Getter and Setter)
```cpp { lineNos="true" wrap="true" title="TParticleInfo.cc" }
void SetMassNumber(Int_t val) { fMassNumber = val; }
Int_t GetMassNumber() const { return fMassNumber; }
void SetAtomicNumber(Int_t val) { fAtomicNumber = val; }
Int_t GetAtomicNumber() const { return fAtomicNumber; }
void SetCharge(Int_t val) { fCharge = val; }
Int_t GetCharge() const { return fCharge; }

void SetCurrentZ(Double_t val) { fCurrentZ = val; }
Double_t GetCurrentZ() const { return fCurrentZ; }
void SetEnergy(Double_t val) { fEnergy = val; }
Double_t GetEnergy() const { return fEnergy; }

void SetLorentzVector(Double_t x, Double_t y, Double_t z, Double_t t) { fVec.SetXYZT(x, y, z, t); }
void SetLorentzVector(TLorentzVector val) { fVec = val; }
TLorentzVector GetLorentzVector() const { return fVec; }

void SetTrack(Double_t x, Double_t y, Double_t z, Double_t a, Double_t b)
{
   fTrack.SetPos(x, y, z);
   fTrack.SetAngle(a, b);
}
TTrack GetTrack() const { return fTrack; }
```


