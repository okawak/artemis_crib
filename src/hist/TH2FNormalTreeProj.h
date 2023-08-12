/**
 * @file   TH2FNormalTreeProj.h
 * @brief  Tree projection 2-D historgram
 *
 * @date   Created       : 2014-03-07 08:35:46 JST
 *         Last Modified : 2023-01-28 23:41:47 JST (ota)
 * @author Shinsuke OTA <ota@cns.s.u-tokyo.ac.jp>
 *
 *    (C) 2014 Shinsuke OTA
 */

#ifndef _TH2FNORMALTREEPROJ_H_ 
#define _TH2FNORMALTREEPROJ_H_ 

#include "TH2F.h"
#include "TNormalAttTreeProj.h"

namespace art {
   class TH2FNormalTreeProj;
}

class art::TH2FNormalTreeProj : public TH2F, public TNormalAttTreeProj {
public:
   TH2FNormalTreeProj();
   TH2FNormalTreeProj(const char *name, const char *title, const char *cut);
   virtual ~TH2FNormalTreeProj();

   TH2FNormalTreeProj(const TH2FNormalTreeProj& rhs);
   TH2FNormalTreeProj& operator=(const TH2FNormalTreeProj& rhs);

   virtual void Copy(TObject& obj) const;

   TH2F fHist;
   

protected:

private:

   
   ClassDef(TH2FNormalTreeProj,1) // Tree projection 2-D historgram
};

#endif // end of #ifndef _TH2FNORMALTREEPROJ_H_
