/**
 * @file    TCatCmdLoopStop.h
 * @brief
 * @author  Kodai Okawa <okawa@cns.s.u-tokyo.ac.jp>
 * @date    2023-06-13 17:28:09
 * @note    last modified: 2024-08-14 22:10:26
 * @details
 */

#ifndef _TCATCMDLOOPSTOP_H_
#define _TCATCMDLOOPSTOP_H_

#include <TCatCmd.h>

class TCatCmdLoopStop : public TCatCmd {
  protected:
    TCatCmdLoopStop();

  public:
    ~TCatCmdLoopStop();

    static TCatCmdLoopStop *Instance();

    Long_t Cmd(vector<TString> args) override;

    void Help() override;

    ClassDefOverride(TCatCmdLoopStop, 1);
};

#endif // end of #ifndef _TCATCMDLOOPSTOP_H_
