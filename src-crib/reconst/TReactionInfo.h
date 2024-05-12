/**
 * @file    TReactionInfo.h
 * @brief
 * @author  Kodai Okawa<okawa@cns.s.u-tokyo.ac.jp>
 * @date    2024-08-01 22:27:43
 * @note
 */

#ifndef _TREACTIONINFO_H_
#define _TREACTIONINFO_H_

#include <TDataObject.h>
#include <constant.h>

namespace art {
class TReactionInfo;
}

class art::TReactionInfo : public TDataObject {
  public:
    typedef enum { kID,
                   kTiming } ESortType;
    typedef enum { kASC,
                   kDESC } ESortOrder;

    TReactionInfo();
    virtual ~TReactionInfo();
    TReactionInfo(const TReactionInfo &rhs);
    TReactionInfo &operator=(const TReactionInfo &rhs);

    Double_t GetEnergy() const { return fEnergy; }
    void SetEnergy(Double_t arg) { fEnergy = arg; }
    Double_t GetTheta() const { return fTheta; }
    void SetTheta(Double_t arg) { fTheta = arg; }

    Double_t GetX() const { return fX; }
    Double_t GetY() const { return fY; }
    Double_t GetZ() const { return fZ; }
    void SetXYZ(Double_t x, Double_t y, Double_t z) {
        fX = x;
        fY = y;
        fZ = z;
    }

    Int_t GetExID() const { return fExcitedID; }
    void SetExID(Int_t arg) { fExcitedID = arg; }

    virtual void Copy(TObject &dest) const;
    virtual void Clear(Option_t *opt = "");

  protected:
    Double_t fEnergy;
    Double_t fTheta;

    Double_t fX; // reaction position, x
    Double_t fY; // reaction position, y
    Double_t fZ; // reaction position, z

    Int_t fExcitedID;

    ClassDef(TReactionInfo, 1)
};

#endif // end of #ifndef _TREACTIONINFO_H_
