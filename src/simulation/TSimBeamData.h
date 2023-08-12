// K.Okawa created <okawa@cns.s.u-tokyo.ac.jp>

#ifndef _TSIMBEAMDATA_H_
#define _TSIMBEAMDATA_H_

#include "TDataObject.h"
#include "TTrack.h"
#include "constant.h"

namespace art {
   class TSimBeamData;
}

class art::TSimBeamData : public TTrack {
public:
   typedef enum {kID, kTiming} ESortType;
   typedef enum {kASC, kDESC} ESortOrder;

   TSimBeamData();
   virtual ~TSimBeamData();
   TSimBeamData(const TSimBeamData& rhs);
   TSimBeamData& operator=(const TSimBeamData& rhs);

   Double_t GetTheta() const {return fTheta; }
   void SetTheta(Double_t arg) { fTheta = arg; }
   Double_t GetPhi() const {return fPhi; }
   void SetPhi(Double_t arg) { fPhi = arg; }

   void SetTrack(Double_t x, Double_t y, Double_t z,
		 Double_t a, Double_t b) {
      SetPos(x,y,z); SetAngle(a,b);
   }
   TTrack* GetTrack() { return this; } // obsolete. left for compatibility
   const TTrack* GetTrack() const { return this; } // obsolete. left for compatibility


   virtual void Copy(TObject& dest) const;
   virtual void Clear(Option_t *opt="");

   void Init();

protected:
   Double_t fTheta; // rad
   Double_t fPhi; // rad

   ClassDef(TSimBeamData,2)
};

#endif // _TSIMBEAMEDATA_H_
