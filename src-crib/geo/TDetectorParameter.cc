/*
   @File name     : TDetectorParameter.cc
   @description   :
   @Author        : Kodai Okawa<okawa@cns.s.u-tokyo.ac.jp>
   @Created date  : 2023-08-01 11:01:10
   @Last modified : 2023-08-01 11:05:35
*/

#include "TDetectorParameter.h"

using art::TDetectorParameter;

ClassImp(TDetectorParameter);

TDetectorParameter::TDetectorParameter() {}

TDetectorParameter::~TDetectorParameter() {}

TDetectorParameter::TDetectorParameter(const TDetectorParameter &rhs) {}

TDetectorParameter &TDetectorParameter::operator=(const TDetectorParameter &rhs)
{
   if (this != &rhs) {
   }
   return *this;
}
