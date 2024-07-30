/**
 * @file    TMUXPositionValidator.h
 * @brief
 * @author  Kodai Okawa<okawa@cns.s.u-tokyo.ac.jp>
 * @date    2024-01-30 10:02:32
 * @note    last modified: 2024-07-30 10:11:47
 * @details
 */

#ifndef _TMUXPOSITIONVALIDATOR_H_
#define _TMUXPOSITIONVALIDATOR_H_

#include <TProcessor.h>

namespace art {
class TMUXPositionValidator;
}
class TClonesArray;

class art::TMUXPositionValidator : public TProcessor {
  public:
    TMUXPositionValidator();
    virtual ~TMUXPositionValidator();

    // TMUXPositionValidator(const TMUXPositionValidator &rhs);
    // TMUXPositionValidator &operator=(const TMUXPositionValidator &rhs);

  protected:
    virtual void Init(TEventCollection *col);
    virtual void Process();

  private:
    TString fInputName;    // name of input collection
    TString fOutputName;   // name of output collection
    TClonesArray **fInput; //! input
    TClonesArray *fOutput; //! output

    //   Int_t fTimeVariable; // 0 time 1 timestamp
    DoubleVec_t fValidPositionRange;
    Double_t fValidPositionMin;
    Double_t fValidPositionMax;

    ClassDef(TMUXPositionValidator, 1) // validate time in certain window
};

#endif // _TMUXPOSITIONVALIDATOR_H_
