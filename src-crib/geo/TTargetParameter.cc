/**
 * @file    TTargetParameter.cc
 * @brief
 * @author  Kodai Okawa<okawa@cns.s.u-tokyo.ac.jp>
 * @date    2024-01-17 22:14:38
 * @note    last modified: 2024-08-14 18:52:30
 * @details
 */

#include "TTargetParameter.h"

using art::TTargetParameter;

ClassImp(TTargetParameter);

TTargetParameter::TTargetParameter() {}

TTargetParameter::~TTargetParameter() {}

TTargetParameter::TTargetParameter(const TTargetParameter &) {}

TTargetParameter &TTargetParameter::operator=(const TTargetParameter &rhs) {
    if (this != &rhs) {
    }
    return *this;
}
