/**
 * @file    TTGTIKProcessor.h
 * @brief
 * @author  Kodai Okawa <okawa@cns.s.u-tokyo.ac.jp>
 * @date    2023-08-01 11:11:02
 * @note    last modified: 2024-08-14 18:25:17
 * @details
 */

#ifndef _TTGTIKPROCESSOR_H_
#define _TTGTIKPROCESSOR_H_

#include <SRIMData.h>
#include <SRIMtable.h>
#include <TProcessor.h>
#include <TTrack.h>

#include "../geo/TDetectorParameter.h"
#include "../telescope/TTelescopeData.h"

namespace art {
class TTGTIKProcessor;
}

class TClonesArray;

class art::TTGTIKProcessor : public TProcessor {
  public:
    // Default constructor
    TTGTIKProcessor();
    virtual ~TTGTIKProcessor();

    void Init(TEventCollection *col) override;
    void Process() override;

    const Double_t kEpsilon = 1.0e-3;
    const Int_t kMaxIteration = 1000;
    const Double_t kWindowUncertainty = 250.0;

  protected:
    TString fInputColName;
    TString fInputTrackColName;
    TString fOutputColName;
    TString fParameterName;

    TClonesArray **fInData;      //!
    TClonesArray **fInTrackData; //!
    TClonesArray *fOutData;      //!
    TClonesArray **fDetectorPrm; //!

    Double_t fInitialBeamEnergy;
    Double_t fEnergyThreshold;
    TString fTargetName;
    StringVec_t fParticleName;   //!
    DoubleVec_t fParticleMass;   //!
    IntVec_t fParticleAtomicNum; //!

    Double_t fMaxLength;

    SRIMData *fElossTable;           //!
    SRIMtable *fElossBeam;           //!
    SRIMtable *fElossDetectParticle; //!

  private:
    Double_t GetReactionPosition(const TTrack *track, const TTelescopeData *data);
    Double_t newton(const TTrack *track, const TTelescopeData *data);
    Double_t bisection(const TTrack *track, const TTelescopeData *data);
    Double_t TargetFunction(Double_t z, const TTrack *track, const TTelescopeData *data);

    Double_t GetEcmFromBeam(Double_t z, const TTrack *track);

    Double_t GetEcmFromDetectParticle(Double_t z, const TTrack *track, const TTelescopeData *data);
    Double_t GetEcm_kinematics(Double_t energy, Double_t theta, Double_t low_e, Double_t high_e);
    Double_t GetEcm_classic_kinematics(Double_t energy, Double_t theta);
    Double_t GetLabAngle(Double_t energy, Double_t energy_cm);

    // Copy constructor (prohibited)
    TTGTIKProcessor(const TTGTIKProcessor &rhs) = delete;
    // Assignment operator (prohibited)
    TTGTIKProcessor &operator=(const TTGTIKProcessor &rhs) = delete;

    ClassDefOverride(TTGTIKProcessor, 1)
};

#endif // end of #ifndef _TTGTIKPROCESSOR_H_
