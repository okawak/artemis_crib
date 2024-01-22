---
title: "Telescope"
date: 2023-12-13T15:08:02+09:00
draft: false
author: "Kodai Okawa"
weight: 6
tags: []
---

{{% badge %}}{{< signature >}}{{% /badge %}}

In the CRIB experiment, we often use a "telescope" consisting of DSSSD (Double-Sided SSD) and SSD (Single-Pad SSD).
The combination of these multiple Si detectors as a dE-E detector is called a `telescope`.

To analyze the data as telescope data rather than individual detectors, I created a data class called TTelescopeData.
This section describes its data structure and usage.

- [src-crib/telescope/TTelescopeData.h](https://github.com/okawak/artemis_crib/blob/main/src-crib/telescope/TTelescopeData.h)


Please assume that one of the name of TTelescopeData object is "tel1"
```shell { wrap="false" } 
# after some process
artemis [*] br tel1

 art::TTelescopeData

 Data Members

                 TVector3   fPos                   detected position (X, Y, Z)
                      int   fXID                   X strip number
                      int   fYID                   Y strip number
                      int   fNE                    number of all SSDs
                   double   fdE                    energy at first layor
                   double   fdEX                   X side energy (=~ fdEY)
                   double   fdEY                   Y side energy (=~ fdEX)
                   double   fE                     added energy at thick SSDs
                   double   fEtotal                all energy deposit in the telescope
                   double   fTiming                timing information at the first layor (X side)
                   double   fYTiming               for case that X side have trouble (Y side)
                   double   fTheta_L               reaction angle in LAB system
           vector<double>   fEnergyArray           energy array for each SSD
           vector<double>   fTimingArray           timing array for each SSD
                ESortType   kID
                ESortType   kTiming
               ESortOrder   kASC
               ESortOrder   kDESC

# snip for Method as for now
```
These are the all data members of the "TTelescopeData".
The most commonly used variables are "fXID", "fYID", "fdE" and "fE".
Other variables are accessed by using methods (explain later).
The meaning of these variables are written the upper code block.

We use them like,
```shell { wrap="false" }
artemis [*] tree->Draw("tel1.fYID:tel1.fXID>>strip(16,-0.5,15.5, 16,-0.5,15.5)","","colz")
artemis [*] tree->Draw("tel1.fdE:tel1.fE","","")
```
or we can use in histogram definition file of course.

The following are the methods of the TTelescopeData object:
```shell { wrap="false" }
# after some process
artemis [*] br tel1

# snip for Data Members

 Methods

          TTelescopeData&   operator=
                 TVector3   GetPosition
                 Double_t   X
                 Double_t   Y
                 Double_t   Z
                     void   SetPosition
                     void   SetPosition
                    Int_t   GetN
                     void   SetN
                    Int_t   GetXID
                     void   SetXID
                    Int_t   GetYID
                     void   SetYID
                 Double_t   GetdE
                     void   SetdE
                 Double_t   GetdEX
                     void   SetdEX
                 Double_t   GetdEY
                     void   SetdEY
                 Double_t   GetE
                     void   SetE
                 Double_t   GetEtotal
                     void   SetEtotal
                 Double_t   GetTelTiming
                     void   SetTelTiming
                 Double_t   GetTelYTiming
                     void   SetTelYTiming
                 Double_t   GetTheta_L
                     void   SetTheta_L
                 Double_t   A
              DoubleVec_t   GetEnergyArray
                 Double_t   GetEnergyArray
                     void   PushEnergyArray
              DoubleVec_t   GetTimingArray
                 Double_t   GetTimingArray
                     void   PushTimingArray
                 Double_t   E
                 Double_t   T
                     void   Copy
                     void   Clear
                   Bool_t   CheckTObjectHashConsistency

 See also

     art::TDataObject       base class for data object
```

The most commonly used methods are "X()", "Y()", "Z()", "E()", "T()" and "A()".
There are also longer name methods, but it is troublesome to write long methods, so I prepared short name methods.
The longer name methods are mainly used in the source processor to make it more readable.

- `X()`: return fPos.X(), detected X position
- `Y()`: return fPos.Y(), detected Y position
- `Z()`: return fPos.Z(), detected Z position
- `E()`: return fEtotal, total energy deposit in the telescope
- `E(id: int)`: return fEnergyArray[id], energy deposit of each Si layer, id=0 means dE, id=1 means second layer
- `T()`: return fTiming, detected timing at first layer
- `T(id: int)`: return fTimingArray[id], timing at the "id" th Si detector
- `A()`: return fTheta_L, the angle of the event, deg unit

We use them like:
```shell { wrap="false" }
artemis [*] tree->Draw("tel1.Y():tel1.X()","","colz")
artemis [*] tree->Draw("tel1.E(0):tel1.E()","","colz")
artemis [*] tree->Draw("tel1.E():tel1.A()","","colz")
```


