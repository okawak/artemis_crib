/**
 * @file    TMUXDataMappingProcessor.h
 * @brief
 * @author  Kodai Okawa<okawa@cns.s.u-tokyo.ac.jp>
 * @date    2022-01-30 09:46:45
 * @note    last modified: 2024-07-30 10:12:45
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
    virtual ~TMUXDataMappingProcessor();

    virtual void Init();
    virtual void Process();

  protected:
    TString fInputColName;
    TString fOutputColName;
    TCategorizedData **fCategorizedData;
    TClonesArray *fOutputArray;

    Int_t fCatID; // category id

  private:
    // TMUXDataMappingProcessor(const TMUXDataMappingProcessor &);
    // TMUXDataMappingProcessor &operator=(const TMUXDataMappingProcessor &);

    ClassDef(TMUXDataMappingProcessor, 0) // simple data mapper
};

#endif // _TMUXDATAMAPPINGPROCESSOR_H_
