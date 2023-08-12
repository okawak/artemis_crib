// K.Okawa created <okawa@cns.s.u-tokyo.ac.jp>

#ifndef _TSIMRESULTDATA_H_
#define _TSIMRESULTDATA_H_

#include "TDataObject.h"
#include "constant.h"

namespace art {
   class TSimResultData;
}

class art::TSimResultData : public TDataObject {
public:
   typedef enum {kID, kTiming} ESortType;
   typedef enum {kASC, kDESC} ESortOrder;

   TSimResultData();
   virtual ~TSimResultData();
   TSimResultData(const TSimResultData& rhs);
   TSimResultData& operator=(const TSimResultData& rhs);

   Double_t GetEtotal() const {return fEtotal;}
   void SetEtotal(Double_t arg) { fEtotal = arg; }
   Double_t GetTiming() const {return fTiming;}
   void SetTiming(Double_t arg) { fTiming = arg; }

   Double_t GetX() const {return fX;}
   void SetX(Double_t arg) { fX = arg; }
   Double_t GetY() const {return fY;}
   void SetY(Double_t arg) { fY = arg; }
   Double_t GetZ() const {return fZ;}
   void SetZ(Double_t arg) { fZ = arg; }

   Double_t GetTheta() const {return fTheta;}
   void SetTheta(Double_t arg) { fTheta = arg; }

   virtual void Copy(TObject& dest) const;
   virtual void Clear(Option_t *opt="");

   void Init();

protected:
   Double_t fEtotal;
   Double_t fTiming;

   Double_t fX;
   Double_t fY;
   Double_t fZ;

   Double_t fTheta;

   ClassDef(TSimResultData,1)
};

#endif // _TSIMRESLUTDATA_H_
