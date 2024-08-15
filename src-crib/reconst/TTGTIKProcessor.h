/**
 * @file    TTGTIKProcessor.h
 * @brief
 * @author  Kodai Okawa <okawa@cns.s.u-tokyo.ac.jp>
 * @date    2023-08-01 11:11:02
 * @note    last modified: 2024-08-15 22:45:00
 * @details
 */

#ifndef _TTGTIKPROCESSOR_H_
#define _TTGTIKPROCESSOR_H_

#include "../telescope/TTelescopeData.h"
#include <TProcessor.h>
#include <TSrim.h> // TSrim library
#include <TTrack.h>

namespace art {
class TTGTIKProcessor;
}

class TClonesArray;

class art::TTGTIKProcessor : public TProcessor {
  public:
    /// @brief Default constructor.
    TTGTIKProcessor();
    /// @brief Default destructor.
    ~TTGTIKProcessor();

    /// @brief Initialization
    void Init(TEventCollection *col) override;
    /// @brief Main process
    void Process() override;

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
    /// @brief Flag of custom processor
    Bool_t fDoCustom;

    /// @brief TSrim object to calculate energy loss
    TSrim *srim;

    /// @brief initial minimum value of bisection method
    const Double_t kInitialMin = -250.0;
    /// @brief initial maximum value of bisection method
    const Double_t kInitialMax = 1000.0;
    /// @brief Accuracy of the bisection method
    const Double_t kEpsilon = 1.0e-3;
    /// @brief Max iteration number of the bisection method
    const Int_t kMaxIteration = 1000;

  private:
    /// @brief Calculate reaction Z position
    /// @param track (art::TTrack)
    /// @param data (art::TTelescopeData)
    /// @return Z position (mm)
    Double_t GetReactionPosition(const TTrack *track, const TTelescopeData *data);

    /// @brief Newtom method (unavalable)
    /// @param track (art::TTrack)
    /// @param data (art::TTelescopeData)
    /// @return Z position (mm)
    Double_t newton(const TTrack *, const TTelescopeData *);

    /// @brief Bisection method
    /// @param track (art::TTrack)
    /// @param data (art::TTelescopeData)
    /// @return Z position (mm)
    Double_t bisection(const TTrack *track, const TTelescopeData *data);

    /// @brief Target function to be set to 0 by bisection (newton) method
    /// @param z (mm)
    /// @param track (art::TTrack)
    /// @param data (art::TTelescopeData)
    /// @return Ecm (beam) - Ecm (data)
    Double_t TargetFunction(Double_t z, const TTrack *track, const TTelescopeData *data);

    /// @brief Get Ecm from beam information
    /// @param z (mm)
    /// @param track (art::TTrack)
    /// @return Ecm (MeV)
    Double_t GetEcmFromBeam(Double_t z, const TTrack *track);

    /// @brief Get Ecm from detected particle information
    /// @param z (mm)
    /// @param track (art::TTrack)
    /// @param data (art::TTelescopeData)
    /// @return Ecm (MeV)
    Double_t GetEcmFromDetectParticle(Double_t z, const TTrack *track, const TTelescopeData *data);

    /// @brief Get Ecm from detected particle information (relativity kinematics)
    /// @param energy (MeV)
    /// @param theta (radian)
    /// @param low_e (minimum energy)
    /// @param high_e (maxmum energy)
    /// @return Ecm (MeV)
    Double_t GetEcm_kinematics(Double_t energy, Double_t theta, Double_t low_e, Double_t high_e);

    /// @brief Get Ecm from detected particle information (classic kinematics)
    /// @param energy (MeV)
    /// @param theta (radian)
    /// @return Ecm (MeV)
    Double_t GetEcm_classic_kinematics(Double_t energy, Double_t theta);

    /// @brief Get Lab Angle after reconstruction
    /// @param energy (MeV)
    /// @param energy_cm (MeV)
    /// @return angle (radian)
    Double_t GetLabAngle(Double_t energy, Double_t energy_cm);

    // Copy constructor (prohibited)
    TTGTIKProcessor(const TTGTIKProcessor &rhs) = delete;
    // Assignment operator (prohibited)
    TTGTIKProcessor &operator=(const TTGTIKProcessor &rhs) = delete;

    ClassDefOverride(TTGTIKProcessor, 1)
};

#endif // end of #ifndef _TTGTIKPROCESSOR_H_
