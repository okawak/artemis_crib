/**
 * @file    TMUXDataMappingProcessor.h
 * @brief
 * @author  Kodai Okawa<okawa@cns.s.u-tokyo.ac.jp>
 * @date    2022-01-30 09:46:45
 * @note    last modified: 2024-08-14 19:09:16
 * @details
 */

#ifndef _TMUXDATAMAPPINGPROCESSOR_H_
#define _TMUXDATAMAPPINGPROCESSOR_H_

#include <TProcessor.h>

namespace art {
class TMUXDataMappingProcessor;
class TCategorizedData;
} // namespace art

class art::TMUXDataMappingProcessor : public TProcessor {
  public:
    TMUXDataMappingProcessor();
    ~TMUXDataMappingProcessor();

    void Init(TEventCollection *) override;
    void Process() override;

  protected:
    TString fInputColName;
    TString fOutputColName;
    TCategorizedData **fCategorizedData;
    TClonesArray *fOutputArray;

    Int_t fCatID; // category id

  private:
    TMUXDataMappingProcessor(const TMUXDataMappingProcessor &) = delete;
    TMUXDataMappingProcessor &operator=(const TMUXDataMappingProcessor &) = delete;

    ClassDefOverride(TMUXDataMappingProcessor, 0) // simple data mapper
};

#endif // _TMUXDATAMAPPINGPROCESSOR_H_
