/**
 * @file    TReactionInfo.h
 * @brief
 * @author  Kodai Okawa<okawa@cns.s.u-tokyo.ac.jp>
 * @date    2023-08-01 22:27:43
 * @note    last modified: 2024-07-18 17:36:23
 * @details
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

    Double_t GetExEnergy() const { return fExEnergy; }
    void SetExEnergy(Double_t arg) { fExEnergy = arg; }

    virtual void Copy(TObject &dest) const;
    virtual void Clear(Option_t *opt = "");

  protected:
    Double_t fEnergy; /// Ecm of the reaction
    Double_t fTheta;  /// Thetacm of the reaction

    Double_t fX; /// reaction position at LAB system, x
    Double_t fY; /// reaction position at LAB system, y
    Double_t fZ; /// reaction position at LAB system, z

    Double_t fExEnergy; /// excited energy of residual nucleus

    ClassDef(TReactionInfo, 1)
};

#endif // end of #ifndef _TREACTIONINFO_H_
