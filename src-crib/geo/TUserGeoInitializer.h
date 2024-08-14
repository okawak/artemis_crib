/**
 * @file    TUserGeoInitializer.h
 * @brief
 * @author  Kodai Okawa<okawa@cns.s.u-tokyo.ac.jp>
 * @date    2024-01-17 21:30:15
 * @note    last modified: 2024-08-14 18:48:33
 * @details
 */

#ifndef _TUSERGEOINITIALIZER_H_
#define _TUSERGEOINITIALIZER_H_

#include <TClonesArray.h>
#include <TGeoManager.h>
#include <TMath.h>
#include <TProcessor.h>

namespace art {
class TUserGeoInitializer;
}

class TClonesArray;

class art::TUserGeoInitializer : public TProcessor {
  public:
    // Default constructor
    TUserGeoInitializer();
    ~TUserGeoInitializer();

    void Init(TEventCollection *col) override;
    void Process() override;

  protected:
    TGeoManager *fGeom; //! it is used for TGeoManager process (like simulation)

    TString fFileName;
    TString fDetPrmName;
    TString fTargetPrmName;

    Bool_t fIsVisible;

    TClonesArray *fDetParameterArray;    //! art::TDetectorParameter array
    TClonesArray *fTargetParameterArray; //! art::TTargetParameter array

    Double_t deg2rad = TMath::DegToRad();

  private:
    void GeometryFromYaml(TString yamlfile);

    // Copy constructor (prohibited)
    TUserGeoInitializer(const TUserGeoInitializer &) = delete;
    // Assignment operator (prohibited)
    TUserGeoInitializer &operator=(const TUserGeoInitializer &) = delete;

    ClassDefOverride(TUserGeoInitializer, 1)
};

#endif // end of #ifndef _TUSERGEOINITIALIZER_H_
