/**
 * @file    TCmdErase.h
 * @brief
 * @author
 * @date    2023-06-13 17:34:58
 * @note    last modified: 2024-08-14 22:22:20
 * @details
 */

#ifndef _TCMDERASE_H_
#define _TCMDERASE_H_

#include <TCatCmd.h>

namespace art {
class TCmdErase;
}

class TDirectory;
class TList;

class art::TCmdErase : public TCatCmd {

  public:
    TCmdErase();
    ~TCmdErase();

    // static TCmdErase* Instance();
    Long_t Cmd(vector<TString>) override;
    Long_t Run();

  protected:
    void EraseRecursive(TList *list);

  private:
    TCmdErase(const TCmdErase &) = delete;            // undefined
    TCmdErase &operator=(const TCmdErase &) = delete; // undefined

    ClassDefOverride(TCmdErase, 1);
};
#endif // end of #ifndef _TCMDERASE_H_
