/**
 * @file   TH3FNormalTreeProj.h
 * @brief  Tree projection 3-D histogram
 *
 * @date   Created       : 2014-03-07 14:29:37 JST
 *         Last Modified : 2023-01-28 23:41:53 JST (ota)
 * @author Shinsuke OTA <ota@cns.s.u-tokyo.ac.jp>
 *
 *    (C) 2014 Shinsuke OTA
 */

#ifndef _TH3FNORMALTREEPROJ_H_ 
#define _TH3FNORMALTREEPROJ_H_ 

#include "TH3F.h"
#include "TNormalAttTreeProj.h"

namespace art {
   class TH3FNormalTreeProj;
}

class art::TH3FNormalTreeProj : public TH3F, public TNormalAttTreeProj {
public:
   TH3FNormalTreeProj();
   TH3FNormalTreeProj(const char *name, const char *title, const char *cut);
   virtual ~TH3FNormalTreeProj();

   TH3FNormalTreeProj(const TH3FNormalTreeProj& rhs);
   TH3FNormalTreeProj& operator=(const TH3FNormalTreeProj& rhs);

   virtual void Copy(TObject &obj) const;

   TH3F fHist;
   
protected:

private:

   
   ClassDef(TH3FNormalTreeProj,1) // Tree projection 3-D histogram
};

#endif // end of #ifndef _TH3FNORMALTREEPROJ_H_
