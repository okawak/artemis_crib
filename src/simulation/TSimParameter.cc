// K.Okawa created <okawa@cns.s.u-tokyo.ac.jp>

#include "TSimParameter.h"


using art::TSimParameter;

ClassImp(TSimParameter)

TSimParameter::TSimParameter()
{
   RegisterParameter("TelescopeID","number of a telescope", fTelescopeID, 0, 1);
   RegisterParameter("EdetNum","number of E SSD detectors", fEdetNum, 0, 1);
//   FloatVec_t defval;
//   defval.resize(2,0.);
//   RegisterParameter("dESize","dE SSD detector size (X x Y)",fdESize,defval,2);
//   IntVec_t intval;
//   intval.resize(2,0);
//   RegisterParameter("dEStripNum","number of the dE DSSD strip (X x Y)",fdEStripNum,intval,2);
   RegisterParameter("dEIsDSSD","dE detector is DSSD (not double SSSD)",fdEIsDSSD,kFALSE,1);
   RegisterParameter("dEXEnergyThreshold","dEX energy threshold", fdEXEnergyThreshold, 0.0, 1);
   RegisterParameter("dEYEnergyThreshold","dEY energy threshold", fdEYEnergyThreshold, 0.0, 1);
//   defval.clear(); defval.resize(3,0);
//   RegisterParameter("Geometry","geometry (z_ref, distance, angle(degree))",fGeometry,defval,3);
//   defval.clear(); defval.resize(2,0.);
//   RegisterParameter("dE_dE_TimeRange","valid time range between dE and dE (for double SSSD)",fdE_dE_TimeRange,defval,2);
//   RegisterParameter("dE_E_TimeRange","valid time range between dE and E",fdE_E_TimeRange,defval,2);
//   defval.clear();
//   intval.clear();
}

TSimParameter::~TSimParameter()
{
}

TSimParameter::TSimParameter(const TSimParameter& rhs)
{
}

TSimParameter& TSimParameter::operator=(const TSimParameter& rhs)
{
   if (this != &rhs) {

   }
   return *this;
}
