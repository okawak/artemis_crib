/**
 * @file    TNBodyReactionProcessor.h
 * @brief
 * @author  Kodai Okawa<okawa@cns.s.u-tokyo.ac.jp>
 * @date    2023-08-01 13:11:23
 * @note
 */

#ifndef _TNBODYREACTIONPROCESSOR_H_
#define _TNBODYREACTIONPROCESSOR_H_

#include <TGenPhaseSpace.h>
#include <TLorentzVector.h>
#include <TMath.h>

#include <SRIMData.h>
#include <SRIMtable.h>
#include <TProcessor.h>

namespace art {
class TNBodyReactionProcessor;
}

class TClonesArray;

class art::TNBodyReactionProcessor : public TProcessor {
  public:
    TNBodyReactionProcessor();
    virtual ~TNBodyReactionProcessor();

    virtual void Init(TEventCollection *col);
    virtual void Process();

  protected:
    TString fInputColName;
    TString fOutputColName;
    TString fOutputReacColName;
    TClonesArray **fInData;     //!
    TClonesArray *fOutData;     //!
    TClonesArray *fOutReacData; //!

    TString fBeamName;

    Int_t fTargetMassNum;
    Int_t fTargetAtmNum;
    TString fTargetName;
    Double_t fTargetThickness;
    Double_t fMinusPosition;
    Bool_t fTargetisGas;

    Int_t fDecayNum;
    IntVec_t fReacMassNum;
    IntVec_t fReacAtmNum;
    IntVec_t fReacChargeNum;
    DoubleVec_t fExciteLevel;
    StringVec_t fReacPartName;

    SRIMData *fElossTable;                   //!
    SRIMtable *fElossTarget;                 //!
    std::vector<SRIMtable *> fElossProducts; //!

    TGenPhaseSpace event;

    const Double_t deg2rad = TMath::DegToRad();
    const Double_t c = 299.792458; // mm/ns

  private:
    TLorentzVector GetLossEnergyVector(TLorentzVector vec, Double_t eloss);

    TNBodyReactionProcessor(const TNBodyReactionProcessor &rhs);
    TNBodyReactionProcessor &operator=(const TNBodyReactionProcessor &rhs);

    ClassDef(TNBodyReactionProcessor, 1)
};

#endif // end of #ifndef _TNBODYREACTIONPROCESSOR_H_
