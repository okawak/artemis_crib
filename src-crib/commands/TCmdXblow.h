/**
 * @file    TCmdXblow.h
 * @brief
 * @author  Kodai Okawa <okawa@cns.s.u-tokyo.ac.jp>
 * @date    2023-06-13 17:47:20
 * @note    last modified: 2024-08-14 22:27:04
 * @details
 */

#ifndef _TCMDXBLOW_H_
#define _TCMDXBLOW_H_

#include <TCatCmd.h>

namespace art {
class TCmdXblow;
}

class TH1;

class art::TCmdXblow : public TCatCmd {
  public:
    TCmdXblow();
    ~TCmdXblow();

    static const char *kFuncNameBase;
    static const char *kLabelNameBase;
    Long_t Cmd(vector<TString>) override;
    TH1 *Run(TH1 *h1);
    void Help() override;

  private:
    TCmdXblow(const TCmdXblow &) = delete;            // undefined
    TCmdXblow &operator=(const TCmdXblow &) = delete; // undefined

    ClassDefOverride(TCmdXblow, 1);
};

#endif // end of #ifndef _TCMDXBLOW_H_
