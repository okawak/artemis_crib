// K.Okawa created <okawa@cns.s.u-tokyo.ac.jp>

#ifndef _TTELESCOPEDATA_H_
#define _TTELESCOPEDATA_H_

#include "TArtTypes.h"
#include <TDataObject.h>
#include <constant.h>
#include <TVector3.h>

namespace art {
   class TTelescopeData;
}

class art::TTelescopeData : public TDataObject {
public:
   typedef enum {kID, kTiming} ESortType;
   typedef enum {kASC, kDESC} ESortOrder;

   TTelescopeData();
   virtual ~TTelescopeData();
   TTelescopeData(const TTelescopeData& rhs);
   TTelescopeData& operator=(const TTelescopeData& rhs);

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

   virtual void Copy(TObject& dest) const;
   virtual void Clear(Option_t *opt="");

   void Init(Int_t nE);

   static const Int_t kMAXNPARAMETER = 3;

protected:
   TVector3 fPos;

   Int_t fXID;
   Int_t fYID;
   Int_t fNE;

   Double_t fdEX;
   Double_t fdEY;
   Double_t fdEXTiming;
   Double_t fdEYTiming;

   Double_t fEvec[kMAXNPARAMETER];
   Double_t fETimingvec[kMAXNPARAMETER];

   Double_t fdE;
   Double_t fE;
   Double_t fEtotal;

   DoubleVec_t fEnergyArray;

   ClassDef(TTelescopeData,2)
};

#endif // _TTELESCOPEDATA_H_
