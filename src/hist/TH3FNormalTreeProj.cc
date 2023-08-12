/**
 * @file   TH3FNormalTreeProj.cc
 * @brief  Tree projection 3-D histogram
 *
 * @date   Created       : 2014-03-07 14:29:56 JST
 *         Last Modified : 2019-11-25 18:00:43 JST (ota)
 * @author Shinsuke OTA <ota@cns.s.u-tokyo.ac.jp>
 *
 *    (C) 2014 Shinsuke OTA
 */

#include "TH3FNormalTreeProj.h"

using art::TH3FNormalTreeProj;

ClassImp(TH3FNormalTreeProj)

TH3FNormalTreeProj::TH3FNormalTreeProj()
{
}

TH3FNormalTreeProj::TH3FNormalTreeProj(const char *name, const char *title, const char *cut)
   : TH3F(name,title,100,0.,100.,100,0.,100.,100,0.,100), TNormalAttTreeProj(this,cut)
{
}

TH3FNormalTreeProj::~TH3FNormalTreeProj()
{
}

TH3FNormalTreeProj::TH3FNormalTreeProj(const TH3FNormalTreeProj& rhs)
{
}

TH3FNormalTreeProj& TH3FNormalTreeProj::operator=(const TH3FNormalTreeProj& rhs)
{
   if (this != &rhs) {

   }
   return *this;
}


void TH3FNormalTreeProj::Copy(TObject& obj) const
{
   TH3F* h2 = dynamic_cast<TH3F*>(&obj);
   TH3F::Copy(*h2);
   TNormalAttTreeProj* proj = dynamic_cast<TNormalAttTreeProj*>(&obj);
   if (proj) {
      TNormalAttTreeProj::Copy(*proj);
   }
}
