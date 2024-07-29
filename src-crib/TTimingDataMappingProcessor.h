/**
 * @file    TTimingDataMappingProcessor.h
 * @brief
 * @author  Kodai Okawa<okawa@cns.s.u-tokyo.ac.jp>
 * @date    2022-07-19 20:20:07
 * @note    last modified: 2024-07-29 20:21:49
 * @details
 */

#ifndef _TTIMINGDATAMAPPINGPROCESSOR_H_
#define _TTIMINGDATAMAPPINGPROCESSOR_H_

#include <TProcessor.h>

namespace art {
class TTimingDataMappingProcessor;
class TCategorizedData;
} // namespace art

class art::TTimingDataMappingProcessor : public TProcessor {
  public:
    TTimingDataMappingProcessor();
    virtual ~TTimingDataMappingProcessor();

    virtual void Init(TEventCollection *col);
    virtual void Process();

  protected:
    TString fInputColName;
    TString fOutputColName;
    TCategorizedData **fCategorizedData;
    TClonesArray *fOutputArray;

    Int_t fCatID;      // category id
    Int_t fDataTypeID; // typeid for data

    Bool_t fIsSparse;

  private:
    TTimingDataMappingProcessor(const TTimingDataMappingProcessor &);
    TTimingDataMappingProcessor &operator=(const TTimingDataMappingProcessor &);

    ClassDef(TTimingDataMappingProcessor, 0) // simple data mapper
};

#endif // _TTIMINGDATAMAPPINGPROCESSOR_H_
