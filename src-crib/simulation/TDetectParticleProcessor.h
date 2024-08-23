/**
 * @file    TDetectParticleProcessor.h
 * @brief
 * @author  Kodai Okawa <okawa@cns.s.u-tokyo.ac.jp>
 * @date    2023-08-01 22:34:15
 * @note    last modified: 2024-08-23 21:12:51
 * @details
 */

#ifndef _CRIB_TDETECTPARTICLEPROCESSOR_H_
#define _CRIB_TDETECTPARTICLEPROCESSOR_H_

#include <TGeoManager.h>
#include <TProcessor.h>
#include <TSrim.h> // TSrim library

namespace art::crib {
class TDetectParticleProcessor;
} // namespace art::crib

class TClonesArray;

class art::crib::TDetectParticleProcessor : public TProcessor {
  public:
    TDetectParticleProcessor();
    ~TDetectParticleProcessor();

    void Init(TEventCollection *col) override;
    void Process() override;

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

    TDetectParticleProcessor(const TDetectParticleProcessor &rhs) = delete;
    TDetectParticleProcessor &operator=(const TDetectParticleProcessor &rhs) = delete;

    ClassDefOverride(TDetectParticleProcessor, 1)
};

#endif // end of #ifndef _TDETECTPARTICLEPROCESSOR_H_
