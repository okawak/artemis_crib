/*
   @File name     : TCRIBPIDProcessor.h
   @description   :
   @Author        : Kodai Okawa<okawa@cns.s.u-tokyo.ac.jp>
   @Created date  : 2023-08-01 11:04:20
   @Last modified : 2023-12-17 14:53:15
*/

#ifndef _TCRIBPIDPROCESSOR_H_
#define _TCRIBPIDPROCESSOR_H_

#include "TArtTypes.h"
#include <TLorentzVector.h>
#include <TGeoManager.h>

#include <TProcessor.h>
#include <SRIMData.h>
#include <SRIMtable.h>

namespace art
{
   class TCRIBPIDProcessor;
}

class TClonesArray;

class art::TCRIBPIDProcessor : public TProcessor
{
public:
   TCRIBPIDProcessor();
   virtual ~TCRIBPIDProcessor();

   virtual void Init(TEventCollection *col);
   virtual void Process();

protected:
   TString fFileName;

   SRIMData *fElossTable;                                           //!
   std::vector<std::vector<std::vector<SRIMtable *>>> fEloss_vvvec; //! [particle_id][telescope_id][layer_id]
   std::vector<SRIMtable *> fTargetEloss_vec;                       //! [particle_id]

private:
   Int_t GetStripID(Double_t pos, Int_t max_strip, Double_t size);

   TCRIBPIDProcessor(const TCRIBPIDProcessor &rhs);
   TCRIBPIDProcessor &operator=(const TCRIBPIDProcessor &rhs);

   ClassDef(TCRIBPIDProcessor, 1)
};

#endif // end of #ifndef _TCRIBPIDPROCESSOR_H_
