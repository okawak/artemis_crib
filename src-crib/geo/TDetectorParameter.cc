/**
 * @file    TDetectorParameter.cc
 * @brief
 * @author  Kodai Okawa<okawa@cns.s.u-tokyo.ac.jp>
 * @date    2024-01-18 14:43:02
 * @note    last modified: 2024-07-19 16:54:40
 * @details
 */

#include "TDetectorParameter.h"

using art::TDetectorParameter;

ClassImp(TDetectorParameter);

TDetectorParameter::TDetectorParameter() {}

TDetectorParameter::~TDetectorParameter() {}

TDetectorParameter::TDetectorParameter(const TDetectorParameter &rhs) {}

TDetectorParameter &TDetectorParameter::operator=(const TDetectorParameter &rhs) {
    if (this != &rhs) {
    }
    return *this;
}
