/**
 * @file   TH1FNormalTreeProj.h
 * @brief  Tree projection histogram
 *
 * @date   Created       : 2014-03-04 13:11:54 JST
 *         Last Modified : 2023-01-28 23:40:22 JST (ota)
 * @author Shinsuke OTA <ota@cns.s.u-tokyo.ac.jp>
 *
 *    (C) 2014 Shinsuke OTA
 */

#ifndef _TH1FNORMALTREEPROJ_H_
#define _TH1FNORMALTREEPROJ_H_

#include "TH1F.h"
#include "TNormalAttTreeProj.h"

namespace art {
   class TH1FNormalTreeProj;
}

class art::TH1FNormalTreeProj : public TH1F, public TNormalAttTreeProj {
//class art::TH1FNormalTreeProj : public TNormalAttTreeProj {
public:
   TH1FNormalTreeProj();
   TH1FNormalTreeProj(const char* name, const char *title, const char *cut = "");
   virtual ~TH1FNormalTreeProj();

   TH1FNormalTreeProj(const TH1FNormalTreeProj& rhs);
   TH1FNormalTreeProj& operator=(const TH1FNormalTreeProj& rhs);

   //virtual void Copy(TObject &obj) const;
   virtual void Copy(TObject &obj);

   TH1F* fHist; //!

   
protected:

private:


   ClassDef(TH1FNormalTreeProj,1) // Tree projection histogram
};

#endif // end of #ifndef _TH1FNORMALTREEPROJ_H_
