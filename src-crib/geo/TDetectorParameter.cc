/**
 * @file    TDetectorParameter.cc
 * @brief
 * @author  Kodai Okawa<okawa@cns.s.u-tokyo.ac.jp>
 * @date    2024-01-18 14:43:02
 * @note    last modified: 2024-08-14 18:53:03
 * @details
 */

#include "TDetectorParameter.h"

using art::TDetectorParameter;

ClassImp(TDetectorParameter);

TDetectorParameter::TDetectorParameter() {}

TDetectorParameter::~TDetectorParameter() {}

TDetectorParameter::TDetectorParameter(const TDetectorParameter &) {}

TDetectorParameter &TDetectorParameter::operator=(const TDetectorParameter &rhs) {
    if (this != &rhs) {
    }
    return *this;
}
