/**
 * @file    TTGTIKProcessor.h
 * @brief
 * @author  Kodai Okawa <okawa@cns.s.u-tokyo.ac.jp>
 * @date    2023-08-01 11:11:02
 * @note    last modified: 2024-08-15 16:25:57
 * @details
 */

#ifndef _TTGTIKPROCESSOR_H_
#define _TTGTIKPROCESSOR_H_

#include <TProcessor.h>
#include <TSrim.h>
#include <TTrack.h>

namespace art {
class TTGTIKProcessor;
}

class TClonesArray;

class art::TTGTIKProcessor : public TProcessor {
  public:
    /// @brief constructor
    TTGTIKProcessor();
    /// @brief destructor
    ~TTGTIKProcessor();

    /// @brief init
    void Init(TEventCollection *col) override;
    /// @brief process
    void Process() override;

    const Double_t kEpsilon = 1.0e-3;
    const Int_t kMaxIteration = 1000;
    const Double_t kWindowUncertainty = 250.0;

  protected:
    /// @brief input telescope collection name (art::TTelescopeData)
    TString fInputColName;
    /// @brief input tracking collection name (art::TTrack)
    TString fInputTrackColName;
    /// @brief output collection name (art::TReactionInfo)
    TString fOutputColName;
    /// @brief detector parameter name (art::TDetectorParameter)
    TString fDetectorParameterName;
    /// @brief target parameter name (art::TTargetParameter)
    TString fTargetParameterName;

    /// @brief telescope input object (TClonesArray(art::TTelescopeData))
    TClonesArray **fInData; //!
    /// @brief tracking input object (TClonesArray(art::TTrack))
    TClonesArray **fInTrackData; //!
    /// @brief output object (TClonesArray(art::TReactionInfo))
    TClonesArray *fOutData;

    /// @brief detector parameter object (TClonesArray(art::TDetectorParameter))
    TClonesArray **fDetectorPrm; //!
    /// @brief target parameter obejct (TClonesArray(art::TTargetParameter))
    TClonesArray **fTargetPrm; //!

    /// @brief initial (after window) beam energy (MeV)
    Double_t fInitialBeamEnergy;
    /// @brief gas target name used in TSrim calculation
    TString fTargetName;
    /// @brief gas pressure in Torr unit
    Double_t fPressure;
    /// @brief gas temperature in K unit
    Double_t fTemperature;
    /// @brief reaction particles Atomic num array
    IntVec_t fParticleZArray;
    /// @brief reaction particles Mass num array
    IntVec_t fParticleAArray;

    /// @brief TSrim object to calculate energy loss
    TSrim *srim;

  private:
    // Double_t GetReactionPosition(const TTrack *track, const TTelescopeData *data);
    // Double_t newton(const TTrack *track, const TTelescopeData *data);
    // Double_t bisection(const TTrack *track, const TTelescopeData *data);
    // Double_t TargetFunction(Double_t z, const TTrack *track, const TTelescopeData *data);

    // Double_t GetEcmFromBeam(Double_t z, const TTrack *track);

    // Double_t GetEcmFromDetectParticle(Double_t z, const TTrack *track, const TTelescopeData *data);
    // Double_t GetEcm_kinematics(Double_t energy, Double_t theta, Double_t low_e, Double_t high_e);
    // Double_t GetEcm_classic_kinematics(Double_t energy, Double_t theta);
    // Double_t GetLabAngle(Double_t energy, Double_t energy_cm);

    // Copy constructor (prohibited)
    TTGTIKProcessor(const TTGTIKProcessor &rhs) = delete;
    // Assignment operator (prohibited)
    TTGTIKProcessor &operator=(const TTGTIKProcessor &rhs) = delete;

    ClassDefOverride(TTGTIKProcessor, 1)
};

#endif // end of #ifndef _TTGTIKPROCESSOR_H_
