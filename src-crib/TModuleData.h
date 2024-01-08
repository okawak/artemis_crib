/**
 * @file    TModuleData.h
 * @brief   inherit from TModuleInfo
 * @author  Kodai Okawa<okawa@cns.s.u-tokyo.ac.jp>
 * @date    2024-01-08 17:51:01
 * @note
 */

#ifndef _TMODULEDATA_H_
#define _TMODULEDATA_H_

#include <TModuleInfo.h>

namespace art {
class TModuleData;
} // namespace art

class art::TModuleData : public art::TModuleInfo {
  public:
    TModuleData(const art::TModuleInfo &info);
    virtual ~TModuleData();

    TModuleData(const TModuleData &rhs);
    TModuleData &operator=(const TModuleData &rhs);

  protected:
    Int_t fNCh;
    std::vector<Int_t> fData1D;
    std::vector<std::vector<Int_t>> fData2D;

  private:
    ClassDef(TModuleData, 1) // module information
};

#endif // _TMODULEDATA_H_