// K.Okawa created <okawa@cns.s.u-tokyo.ac.jp>

#ifndef _TSIMTGTIKPREPPROCESSOR_H_
#define _TSIMTGTIKPREPPROCESSOR_H_

#include <TProcessor.h>

#include <TVector3.h>

#include <vector>

namespace art {
   class TSimTGTIKPrepProcessor;
}

class TClonesArray;

class art::TSimTGTIKPrepProcessor : public TProcessor {
public:
   // Default constructor
   TSimTGTIKPrepProcessor();
   virtual ~TSimTGTIKPrepProcessor();

   virtual void Init(TEventCollection *col);
   virtual void Process();

   TVector3 get_DetPosition(Int_t telID, Int_t XID, Int_t YID, TVector3 win_offset, TVector3 win_dir);
   TVector3 get_rawDetPosition(Int_t XID, Int_t YID, Double_t orig_rotate_z, Double_t distance, Double_t angle, Double_t offset, Bool_t x_reflection);

   Bool_t debug_flag;

protected:
   TString        fInputColName;
   TString        fOutputColName;

   TClonesArray **fInData; //!
   TClonesArray  *fOutData; //!

   Double_t fWindowpos;

   Bool_t fIsSparse;

private:
   // Copy constructor (prohibited)
   TSimTGTIKPrepProcessor(const TSimTGTIKPrepProcessor& rhs);
   // Assignment operator (prohibited)
   TSimTGTIKPrepProcessor& operator=(const TSimTGTIKPrepProcessor& rhs);

   ClassDef(TSimTGTIKPrepProcessor,1) // processor for calibration of timing and charge data
};

#endif // _TSIMTGTIKPREPPROCESSOR_H_
