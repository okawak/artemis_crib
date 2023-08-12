/*
   @File name     : TSolidAngleProcessor.h
   @description   :
   @Author        : Kodai Okawa<okawa@cns.s.u-tokyo.ac.jp>
   @Created date  : 2023-08-01 11:08:17
   @Last modified : 2023-08-01 11:08:32
*/

#ifndef _TSOLIDANGLEPROCESSOR_H_
#define _TSOLIDANGLEPROCESSOR_H_

#include <TProcessor.h>

#include <TH1.h>
#include <TH2.h>

namespace art {
class TSolidAngleProcessor;
}

class TClonesArray;

class art::TSolidAngleProcessor : public TProcessor {
public:
   TSolidAngleProcessor();
   virtual ~TSolidAngleProcessor();

   virtual void Init(TEventCollection *col);
   virtual void Process();
   virtual void PostLoop();

protected:
   TString fInputColName_cm;
   TString fInputColName_det;
   TClonesArray **fInData_cm;  //!
   TClonesArray **fInData_det; //!

   Int_t fNbin_angle;
   DoubleVec_t fRange_angle;
   Int_t fNbin_energy;
   DoubleVec_t fRange_energy;
   TString fFileName;
   Bool_t fIsIK;

   TH1D *h1;     // solid angle (x: Ecm)
   TH1D *h1_all; // for normalize (x: Ecm)
   TH2D *h2;     // solid angle (x: Ecm, y: Thetacm)
   TH2D *h2_all; // for normalize (x: Ecm, y: Thetacm)

private:
   TSolidAngleProcessor(const TSolidAngleProcessor &rhs);
   TSolidAngleProcessor &operator=(const TSolidAngleProcessor &rhs);

   ClassDef(TSolidAngleProcessor, 1)
};

#endif // end of #ifndef _TSOLIDANGLEPROCESSOR_H_
