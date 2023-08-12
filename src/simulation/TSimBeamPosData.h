// K.Okawa created <okawa@cns.s.u-tokyo.ac.jp>

#ifndef _TSIMBEAMPOSDATA_H_
#define _TSIMBEAMPOSDATA_H_

#include "TDataObject.h"
#include "constant.h"

namespace art {
   class TSimBeamPosData;
}

class art::TSimBeamPosData : public TDataObject {
public:
   typedef enum {kID, kTiming} ESortType;
   typedef enum {kASC, kDESC} ESortOrder;

   TSimBeamPosData();
   virtual ~TSimBeamPosData();
   TSimBeamPosData(const TSimBeamPosData& rhs);
   TSimBeamPosData& operator=(const TSimBeamPosData& rhs);

   Int_t GetXID() const {return fXID;}
   void SetXID(Double_t arg) { fXID = arg; }
   Int_t GetYID() const {return fYID;}
   void SetYID(Double_t arg) { fYID = arg; }
   Double_t GetDistance() const {return fDistance;}
   void SetDistance(Double_t arg) { fDistance = arg; }

   virtual void Copy(TObject& dest) const;
   virtual void Clear(Option_t *opt="");

   void Init();

protected:
   Int_t fXID;
   Int_t fYID;

   Double_t fDistance;

   ClassDef(TSimBeamPosData,1)
};

#endif // _TSIMBEAMPOSEDATA_H_
