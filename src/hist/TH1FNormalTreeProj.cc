/**
 * @file   TH1FNormalTreeProj.cc
 * @brief  Tree projection
 *
 * @date   Created       : 2014-03-04 13:21:56 JST
 *         Last Modified : 2019-11-25 17:59:37 JST (ota)
 * @author Shinsuke OTA <ota@cns.s.u-tokyo.ac.jp>
 *
 *    (C) 2014 Shinsuke OTA
 */

#include "TH1FNormalTreeProj.h"

using art::TH1FNormalTreeProj;

ClassImp(TH1FNormalTreeProj)

TH1FNormalTreeProj::TH1FNormalTreeProj()
: TNormalAttTreeProj(this)
//: TNormalAttTreeProj(&fHist)
//: TNormalAttTreeProj(fHist)
{
}

TH1FNormalTreeProj::TH1FNormalTreeProj(const char *name, const char *title, const char *cut)
   : TH1F(name,title,100,0.,100.), TNormalAttTreeProj(this,cut)
//   : fHist(name,title,100,0.,100.), TNormalAttTreeProj(&fHist,cut)
//   : TH1F(name,title,100,0.,100.), TNormalAttTreeProj(fHist,cut)
{
}

TH1FNormalTreeProj::~TH1FNormalTreeProj()
{
}

TH1FNormalTreeProj::TH1FNormalTreeProj(const TH1FNormalTreeProj& rhs)
{
}

TH1FNormalTreeProj& TH1FNormalTreeProj::operator=(const TH1FNormalTreeProj& rhs)
{
   if (this != &rhs) {

   }
   return *this;
}
//void TH1FNormalTreeProj::Copy(TObject& obj) const
void TH1FNormalTreeProj::Copy(TObject& obj)
{
   TH1F* h2 = dynamic_cast<TH1F*>(&obj);
   TH1F::Copy(*h2);
   //add
   //TH1F* htmp = dynamic_cast<TH1FNormalTreeProj*>(&obj)->fHist;
   //fHist = (TH1F*)htmp->Clone();
   //end
   TNormalAttTreeProj* proj = dynamic_cast<TNormalAttTreeProj*>(&obj);
   if (proj) {
      TNormalAttTreeProj::Copy(*proj);
   }
}
