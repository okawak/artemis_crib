// K.Okawa modified <okawa@cns.s.u-tokyo.ac.jp>

#ifndef _TTSMAPPINGPROCESSOR_H_
#define _TTSMAPPINGPROCESSOR_H_

#include <TProcessor.h>

namespace art {
class TTSMappingProcessor;
class TCategorizedData;
} // namespace art

class art::TTSMappingProcessor : public TProcessor {
  public:
    TTSMappingProcessor();
    ~TTSMappingProcessor();

    void Init(TEventCollection *) override;
    void Process() override;

  protected:
    TString fInputColName;
    TString fOutputColName;
    TCategorizedData **fCategorizedData;
    TClonesArray *fOutputArray;

    Int_t fCatID;      // category id
    Int_t fDataTypeID; // typeid for data

  private:
    TTSMappingProcessor(const TTSMappingProcessor &) = delete;
    TTSMappingProcessor &operator=(const TTSMappingProcessor &) = delete;

    ClassDefOverride(TTSMappingProcessor, 0) // simple data mapper
};

#endif // _TTSMAPPINGPROCESSOR_H_
