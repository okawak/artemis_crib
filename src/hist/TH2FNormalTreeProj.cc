/**
 * @file   TH2FNormalTreeProj.cc
 * @brief  Tree projection 2-D historgram
 *
 * @date   Created       : 2014-03-07 08:35:22 JST
 *         Last Modified : 2019-11-25 17:53:35 JST (ota)
 * @author Shinsuke OTA <ota@cns.s.u-tokyo.ac.jp>
 *
 *    (C) 2014 Shinsuke OTA
 */

#include "TH2FNormalTreeProj.h"

using art::TH2FNormalTreeProj;

ClassImp(TH2FNormalTreeProj)

TH2FNormalTreeProj::TH2FNormalTreeProj()
: TNormalAttTreeProj(this)
{
}

TH2FNormalTreeProj::TH2FNormalTreeProj(const char *name, const char *title, const char *cut)
   : TH2F(name,title,100,0.,100.,100,0.,100.), TNormalAttTreeProj(this,cut)
{
  fHist.SetName(name);
  fHist.SetTitle(title);
  //fHist.SetBinsLength(100);
  //fHist.SetAxisRange(0., 100.);
}

TH2FNormalTreeProj::~TH2FNormalTreeProj()
{
}

TH2FNormalTreeProj::TH2FNormalTreeProj(const TH2FNormalTreeProj& rhs)
{
}

TH2FNormalTreeProj& TH2FNormalTreeProj::operator=(const TH2FNormalTreeProj& rhs)
{
   if (this != &rhs) {

   }
   return *this;
}


void TH2FNormalTreeProj::Copy(TObject& obj) const
{
   TH2F* h2 = dynamic_cast<TH2F*>(&obj);
   TH2F::Copy(*h2);
   TNormalAttTreeProj* proj = dynamic_cast<TNormalAttTreeProj*>(&obj);
   if (proj) {
      TNormalAttTreeProj::Copy(*proj);
   }
}
