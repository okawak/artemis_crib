/**
 * @file    TMUXCalibrationProcessor.h
 * @brief
 * @author  Kodai Okawa<okawa@cns.s.u-tokyo.ac.jp>
 * @date    2022-01-30 11:08:53
 * @note    last modified: 2024-07-30 11:19:30
 * @details if no valid converter given, this processor does nothing.
 */

#ifndef _TMUXCALIBRATIONPROCESSOR_H
#define _TMUXCALIBRATIONPROCESSOR_H

#include <TProcessor.h>

#include <vector>

namespace art {
class TMUXCalibrationProcessor;
class TConverterBase;
} // namespace art

class TClonesArray;

class art::TMUXCalibrationProcessor : public TProcessor {
  public:
    // Default constructor
    TMUXCalibrationProcessor();
    virtual ~TMUXCalibrationProcessor();

    virtual void Init(TEventCollection *col);
    virtual void Process();

  protected:
    TString fInputColName;
    TString fOutputColName;
    TClonesArray **fInData; //!
    TClonesArray *fOutData; //!

    TString fTimingConverterArrayName;
    TString fChargeConverterArrayName;
    TString fPositionConverterArrayName;
    std::vector<TConverterBase *> *fTimingConverterArray;   //!
    std::vector<TConverterBase *> *fChargeConverterArray;   //!
    std::vector<TConverterBase *> *fPositionConverterArray; //!
    Bool_t fInputHasMUXData;
    Bool_t fHasReflection;
    Bool_t fInputIsDigital;

    Bool_t fIsSparse;

  private:
    // Copy constructor (prohibited)
    // TMUXCalibrationProcessor(const TMUXCalibrationProcessor &rhs);
    // Assignment operator (prohibited)
    // TMUXCalibrationProcessor &operator=(const TMUXCalibrationProcessor &rhs);

    ClassDef(TMUXCalibrationProcessor, 1) // processor for calibration of timing and charge data
};

#endif // _TMUXCALIBRATIONPROCESSOR_H
