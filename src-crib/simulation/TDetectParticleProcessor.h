/**
 * @file    TDetectParticleProcessor.h
 * @brief
 * @author  Kodai Okawa<okawa@cns.s.u-tokyo.ac.jp>
 * @date    2023-08-01 22:34:15
 * @note    last modified: 2024-07-30 15:05:42
 * @details
 */

#ifndef _TDETECTPARTICLEPROCESSOR_H_
#define _TDETECTPARTICLEPROCESSOR_H_

#include "TArtTypes.h"
#include <TGeoManager.h>
#include <TLorentzVector.h>
#include <TSrim.h> // TSrim library

#include <TProcessor.h>

namespace art {
class TDetectParticleProcessor;
}

class TClonesArray;

class art::TDetectParticleProcessor : public TProcessor {
  public:
    TDetectParticleProcessor();
    virtual ~TDetectParticleProcessor();

    virtual void Init(TEventCollection *col);
    virtual void Process();

  protected:
    TString fInputColName;
    TString fInputTrackColName;
    TString fOutputColName;
    TString fDetectorParameterName;
    TString fTargetParameterName;
    TClonesArray **fInData;      //!
    TClonesArray **fInTrackData; //!
    TClonesArray *fOutData;      //!
    TGeoManager **fInGeom;       //!

    TClonesArray **fDetectorPrm; //!
    TClonesArray **fTargetPrm;   //!

    Bool_t fTargetIsGas;
    TString fTargetName;
    Double_t fTargetPressure;

    DoubleVec_t fResolution; //! x 100 = %, index=telescope id

    TSrim *srim;

    const Double_t c = 299.792458; // mm/ns

  private:
    std::vector<TString> GetUniqueElements(const std::vector<TString> &input);
    Int_t GetStripID(Double_t pos, Int_t max_strip, Double_t size);

    // TDetectParticleProcessor(const TDetectParticleProcessor &rhs);
    // TDetectParticleProcessor &operator=(const TDetectParticleProcessor &rhs);

    ClassDef(TDetectParticleProcessor, 1)
};

#endif // end of #ifndef _TDETECTPARTICLEPROCESSOR_H_
