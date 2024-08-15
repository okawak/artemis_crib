/**
 * @file    TUserGeoInitializer.h
 * @brief
 * @author  Kodai Okawa<okawa@cns.s.u-tokyo.ac.jp>
 * @date    2024-01-17 21:30:15
 * @note    last modified: 2024-08-15 14:31:43
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
    /**
     * @fn constructor
     * @brief constructor
     * @detail in the steering file, we set two parameters,
     *
     * "FileName": geometry file, like prm/geo/expname.yaml
     * "Visible": make detector geometry figure
     *
     * in the source code, the geometry parameter objects
     * can be used by the name of "prm_detector" or "prm_target"
     * in the constructor of other processor, you can get this
     * object by
     *
     * RegisterOptionalInputInfo("DetectorParameter", "name of telescope parameter", fDetectorParameterName,
     *                            TString("prm_detectors"), &fDetectorPrm, "TClonesArray", "art::TDetectorParameter");
     *
     */
    TUserGeoInitializer();
    /**
     * @fn destructor
     * @brief destructor
     */
    ~TUserGeoInitializer();

    void Init(TEventCollection *col) override;
    void Process() override;

  protected:
    /// @brief It is used for TGeoManager process
    TGeoManager *fGeom;

    /// @brief Input geometry file name. You can define in steering file.
    TString fFileName;
    /// @brief It should be "prm_detector"
    TString fDetPrmName;
    /// @brief It should be "prm_target"
    TString fTargetPrmName;

    /// @brief Make figure of Detectors of not.
    Bool_t fIsVisible;

    /// @brief Detector parameter object (art::TDetectorParameter array)
    TClonesArray *fDetParameterArray;
    /// @brief Target parameter object (art::TTargetParameter array)
    TClonesArray *fTargetParameterArray;

    /// @brief angle converter, degree to radian
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
