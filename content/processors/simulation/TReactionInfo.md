---
title: "TReactionInfo"
date: 2023-08-18T16:17:21+09:00
draft: false
author: "Kodai Okawa"
weight: 1
tags: ["data_class"]
---

{{% badge %}}{{< signature >}}{{% /badge %}}

## TReactionInfo

- Data member
```cpp
// center of the mass system
Double_t fEnergy; // kinetic energy 
Double_t fTheta; // theta
Double_t fPhi; // phi

// reaction position
Double_t fX;
Double_t fY;
Double_t fZ;

// if you define excited statas, the information stored this value
Int_t fExcitedID;
```

- Methods
```cpp
Double_t GetEnergy() const { return fEnergy; }
void SetEnergy(Double_t arg) { fEnergy = arg; }
Double_t GetTheta() const { return fTheta; }
void SetTheta(Double_t arg) { fTheta = arg; }
Double_t GetPhi() const { return fPhi; }
void SetPhi(Double_t arg) { fPhi = arg; }

Double_t GetX() const { return fX; }
Double_t GetY() const { return fY; }
Double_t GetZ() const { return fZ; }
void SetXYZ(Double_t x, Double_t y, Double_t z)
{
   fX = x;
   fY = y;
   fZ = z;
}

Int_t GetExID() const { return fExcitedID; }
void SetExID(Int_t arg) { fExcitedID = arg; }
```

