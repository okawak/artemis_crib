// K.Okawa created <okawa@cns.s.u-tokyo.ac.jp>

#ifndef _TTELESCOPEPARAMETER_H_ 
#define _TTELESCOPEPARAMETER_H_ 

#include "TParameterObject.h"
namespace art {
   class TTelescopeParameter;
}

namespace YAML {
   class Node;
}

class art::TTelescopeParameter : public TParameterObject {
public:
   TTelescopeParameter();
   virtual ~TTelescopeParameter();

   TTelescopeParameter(const TTelescopeParameter& rhs);
   TTelescopeParameter& operator=(const TTelescopeParameter& rhs);

   Int_t GetTelescopeID() { return fTelescopeID; }
   Int_t GetEdetNum() { return fEdetNum; }
   //.Float_t GetdESize(Int_t idx) { return fdESize[idx]; }
   //Int_t GetdEStripNum(Int_t idx) { return fdEStripNum[idx]; }
   Bool_t GetdEIsDSSD() { return fdEIsDSSD; }
   Double_t GetdEXEnergyThreshold() { return fdEXEnergyThreshold; }
   Double_t GetdEYEnergyThreshold() { return fdEYEnergyThreshold; }
   //Float_t GetGeometry(Int_t idx) { return fGeometry[idx]; }
   //Float_t GetdE_dE_TimeRange(Int_t idx) { return fdE_dE_TimeRange[idx]; }
   //Float_t GetdE_E_TimeRange(Int_t idx) { return fdE_E_TimeRange[idx]; }

   //Bool_t IsInsideTime_dE_dE(Double_t val) { return (fdE_dE_TimeRange[0] < val && val < fdE_dE_TimeRange[1]); }
   //Bool_t IsInsideTime_dE_E(Double_t val) { return (fdE_E_TimeRange[0] < val && val < fdE_E_TimeRange[1]); }
   
protected:
   Int_t fTelescopeID;
   Int_t fEdetNum;
   //FloatVec_t fdESize; //!
   //IntVec_t fdEStripNum; //!
   Bool_t fdEIsDSSD;
   Double_t fdEXEnergyThreshold;
   Double_t fdEYEnergyThreshold;
   //FloatVec_t fGeometry; //!
   //FloatVec_t fdE_dE_TimeRange; //!
   //FloatVec_t fdE_E_TimeRange; //!
   

//// to be exported to TParameterObject
//public:
////   Bool_t LoadYAMLNode(const YAML::Node& node);
//protected:
   
   
   
private:

   ClassDef(TTelescopeParameter,1) // ppac parameter holder
};

#endif // _TTELESCOPEPARAMETER_H_
