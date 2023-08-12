/**
 * @file   TNormalTreeProjection.h
 * @brief  Tree projection definition
 *
 * @date   Created       : 2014-03-05 10:07:22 JST
 *         Last Modified : Jun 15, 2014 11:29:15 JST
 * @author Shinsuke OTA <ota@cns.s.u-tokyo.ac.jp>
 *
 *    (C) 2014 Shinsuke OTA
 */

#ifndef _TNORMALTREEPROJECTION_H_
#define _TNORMALTREEPROJECTION_H_

#include "TParameterObject.h"
#include "TNormalAttTreeProj.h"
#include "TTreeProjGroup.h"
#include <vector>

namespace art {
   class TNormalTreeProjection;
}

class TTree;

class art::TNormalTreeProjection : public TParameterObject {
public:
   
   TNormalTreeProjection();
   virtual ~TNormalTreeProjection();

   TNormalTreeProjection(const TNormalTreeProjection& rhs);
   TNormalTreeProjection& operator=(const TNormalTreeProjection& rhs);

   // @override loading yaml node
   virtual Bool_t LoadYAMLNode(const YAML::Node& node);

   // fill all the projetion
   inline virtual void Project();

   // synchronize formula with tree
   virtual Bool_t Sync(TTree *tree);
protected:
   virtual Bool_t Sync(TTreeProjGroup *group, TTree *tree, TCut cut = "");


   TObjArray *fProjGroups;
   TObjArray *fIncludes;
   TObjArray *fAliases;
   std::vector<TNormalAttTreeProj*> fProjections;    //! helper container for fill the projections

   TString fBaseDir;

private:

   ClassDef(TNormalTreeProjection,1) // Tree projection definition
};

inline void art::TNormalTreeProjection::Project()
{
   std::vector<TNormalAttTreeProj*>::iterator it;
   std::vector<TNormalAttTreeProj*>::iterator itbegin = fProjections.begin();
   std::vector<TNormalAttTreeProj*>::iterator itend = fProjections.end();
   for (it = itbegin; it != itend; it++) {
      (*it)->FillProjection();
   }
}
#endif // end of #ifndef _TNORMALTREEPROJECTION_H_
