/**
 * @file    TDetectParticleProcessor.h
 * @brief
 * @author  Kodai Okawa<okawa@cns.s.u-tokyo.ac.jp>
 * @date    2023-08-01 22:34:15
 * @note
 */

#ifndef _TDETECTPARTICLEPROCESSOR_H_
#define _TDETECTPARTICLEPROCESSOR_H_

#include "TArtTypes.h"
#include <TGeoManager.h>
#include <TLorentzVector.h>

#include <SRIMData.h>
#include <SRIMtable.h>
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
    TString fOutputColName;
    TString fParameterName;
    TGeoManager **fInGeom;  //!
    TClonesArray **fInData; //!
    TClonesArray *fOutData; //!

    TClonesArray **fDetectorPrm; //!

    StringVec_t fReacPartName; //!
    DoubleVec_t fResolution;   //!
    Bool_t fTargetisGas;
    Bool_t fDoOnlyLightPart;
    TString fTargetName;
    Double_t fMaxRadius;

    SRIMData *fElossTable;                                           //!
    std::vector<std::vector<std::vector<SRIMtable *>>> fEloss_vvvec; //! [particle_id][telescope_id][layer_id]
    std::vector<SRIMtable *> fTargetEloss_vec;                       //! [particle_id]

  private:
    Int_t GetStripID(Double_t pos, Int_t max_strip, Double_t size);

    TDetectParticleProcessor(const TDetectParticleProcessor &rhs);
    TDetectParticleProcessor &operator=(const TDetectParticleProcessor &rhs);

    ClassDef(TDetectParticleProcessor, 1)
};

#endif // end of #ifndef _TDETECTPARTICLEPROCESSOR_H_
