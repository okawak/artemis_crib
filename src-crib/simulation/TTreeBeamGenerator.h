/**
 * @file    TTreeBeamGenerator.h
 * @brief
 * @author  Kodai Okawa<okawa@cns.s.u-tokyo.ac.jp>
 * @date    2023-06-09 15:57:38
 * @note    last modified: 2024-07-16 16:52:52
 * @details
 */

#ifndef _TTREEBEAMGENERATOR_H_
#define _TTREEBEAMGENERATOR_H_

#include <TProcessor.h>

namespace art {
class TTreeBeamGenerator;
}

class TClonesArray;

class art::TTreeBeamGenerator : public TProcessor {
  public:
    TTreeBeamGenerator();
    virtual ~TTreeBeamGenerator();

    void Init(TEventCollection *);
    void Process();

  protected:
    TString fInputColName;
    TString fOutputColName;

    TClonesArray **fInData; //!
    TClonesArray *fOutData; //!

    Int_t fMassNum;
    Int_t fAtmNum;
    Int_t fChargeNum;
    Double_t fBeamEnergy;

    Double_t fEsigma;

  private:
    Double_t fMass;

    // Copy constructor (prohibited)
    TTreeBeamGenerator(const TTreeBeamGenerator &rhs);
    // Assignment operator (prohibited)
    TTreeBeamGenerator &operator=(const TTreeBeamGenerator &rhs);

    ClassDef(TTreeBeamGenerator, 1);
};

#endif // end of #ifndef _TTREEBEAMGENERATOR_H_
