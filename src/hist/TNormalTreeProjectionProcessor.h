/**
 * @file   TNormalTreeProjectionProcessor.h
 * @brief  processor for tree projection
 *
 * @date   Created       : 2014-03-05 22:22:59 JST
 *         Last Modified : 2019-05-14 17:37:20 JST (ota)
 * @author Shinsuke OTA <ota@cns.s.u-tokyo.ac.jp>
 *
 *    (C) 2014 Shinsuke OTA
 */

#ifndef _TNORMALTREEPROJECTIONPROCESSOR_H_
#define _TNORMALTREEPROJECTIONPROCESSOR_H_

#include "TParameterLoader.h"

namespace art {
   class TNormalTreeProjectionProcessor;
   class TNormalTreeProjection;
}

class TTree;
class TDirectory;

class art::TNormalTreeProjectionProcessor : public TParameterLoader {
public:
   TNormalTreeProjectionProcessor();
   virtual ~TNormalTreeProjectionProcessor();

   TNormalTreeProjectionProcessor(const TNormalTreeProjectionProcessor& rhs);
   TNormalTreeProjectionProcessor& operator=(const TNormalTreeProjectionProcessor& rhs);

   virtual void Init(TEventCollection *col);
   virtual void Process();
   virtual void PostLoop();


protected:
   TTree *fTree; //! ttree for projection
   TNormalTreeProjection *fTreeProj; // tree projection definition

   TString fOutputFilename; // output filename
   TDirectory *fDirectory; //!

   TString fReplacement; //
   
private:

   ClassDef(TNormalTreeProjectionProcessor,1) // processor for tree projection
};

#endif // end of #ifndef _TNORMALTREEPROJECTIONPROCESSOR_H_
