/**
 * @file    TCmdXstatus.h
 * @brief
 * @author  Kodai Okawa <okawa@cns.s.u-tokyo.ac.jp>
 * @date    2023-06-13 10:56:18
 * @note    last modified: 2024-08-14 22:31:27
 * @details
 */

#ifndef _TCMDXSTATUS_H_
#define _TCMDXSTATUS_H_

#include <TCatCmd.h>

namespace art {
class TCmdXstatus;
}

class TF1;

class art::TCmdXstatus : public TCatCmd {
  public:
    TCmdXstatus();
    ~TCmdXstatus();

    static const char *kFuncNameBase;
    static const char *kLabelNameBase;
    Long_t Cmd(vector<TString>) override;
    void Help() override;

  private:
    TCmdXstatus(const TCmdXstatus &) = delete;            // undefined
    TCmdXstatus &operator=(const TCmdXstatus &) = delete; // undefined

    ClassDefOverride(TCmdXstatus, 1);
};

#endif // end of #ifndef _TCMDXSTATUS_H_
