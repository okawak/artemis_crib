/**
 * @file   TNormalAttTreeProj.h
 * @brief  Attribute to fill the tree projection histogram
 *
 * @date   Created       : 2014-03-03 23:29:51 JST
 *         Last Modified : 2023-01-28 20:28:39 JST (ota)
 * @author Shinsuke OTA <ota@cns.s.u-tokyo.ac.jp>
 *
 *    (C) 2014 Shinsuke OTA
 */

#ifndef _TNORMALATTTREEPROJ_J_
#define _TNORMALATTTREEPROJ_J_

#include "TAttCut.h"
#include <TH1.h>

namespace art {
   class TNormalAttTreeProj;
   class TAxisTreeProj;
}

class TH2;
class TH3;
class TTreeFormulaManager;


class art::TNormalAttTreeProj : public TAttCut {
public:
   TNormalAttTreeProj();
   TNormalAttTreeProj(TH1 *hist, const char* cut = "");
   virtual ~TNormalAttTreeProj();

   // copy this object
   virtual void Copy(TAttCut &newatt) const;
   
   // fill each histogram
   inline virtual void FillProjection();
   
   // get axis definition
   virtual TAxisTreeProj* GetAxisDef(int i) { return fAxes[i]; }
      
   // get flag for async
   virtual Bool_t GetAxisAsync() { return fAxisAsync; }

   virtual void SetAxisAsync(Bool_t async) { fAxisAsync = async; }

   // set axis definition 
   virtual void SetAxisDef(UInt_t i, TAxisTreeProj* axis);

   // set title of projection
   virtual void SetProjTitle(const char *title) { fH->SetTitle(title); }

   // set name of projection
   virtual void SetProjName(const char *name) { fH->SetName(name); }

   // prepare managers and synchronize variables, this should be called before fill
   virtual void Sync();


protected:

   virtual void FillTo(TH1* hist);
   virtual void FillTo(TH2* hist);
   virtual void FillTo(TH3* hist);

   TNormalAttTreeProj(const TNormalAttTreeProj& rhs);
   virtual TNormalAttTreeProj& operator=(const TNormalAttTreeProj& rhs);
   
private:
   TH1*   fH; //! histgram owned by the outer object
   Bool_t               fAxisAsync;
   Bool_t fNeedSync; //
   std::vector<TTreeFormulaManager*> fManagers; //!
   std::vector<TAxisTreeProj*> fAxes;

   ClassDef(TNormalAttTreeProj,1) // Attribute to fill the tree projection histogram
};

void art::TNormalAttTreeProj::FillProjection()
{
   switch(fH->GetDimension()) {
   case 1:
      FillTo(fH);
      break;
   case 2:
      FillTo((TH2*) fH);
      break;
   case 3:
      FillTo((TH3*) fH);
      break;
   }
}

#endif // end of #ifndef _TNORMALATTTREEPROJ_H_
