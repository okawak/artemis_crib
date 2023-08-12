// K.Okawa created <okawa@cns.s.u-tokyo.ac.jp>

#ifndef _TSIMTREERANDOMBEAMGENERATOR_H_
#define _TSIMTREERANDOMBEAMGENERATOR_H_

#include <TProcessor.h>
#include <TSimpleData.h>

namespace art {
	class TSimTreeRandomBeamGenerator;
}

class TString;
class TFile;
class TTree;
//class TSimpleData;
class TClonesArray;

class art::TSimTreeRandomBeamGenerator : public TProcessor {
public:
	TSimTreeRandomBeamGenerator();
	virtual ~TSimTreeRandomBeamGenerator();
	
	void Init(TEventCollection*);
	void Process();
	
protected:
	TString fOutputColName;

	TClonesArray  *fBeamData; //!
	TClonesArray  *fOutData; //!

	TString  fFileName;
	TString  fTreeName;
	TString  fBeamBranchName;
	TFile   *fFile; //!
	TTree   *fTree; //!

	Long_t nEntry;
	Long_t iEntry;

private:
	// Copy constructor (prohibited)
	TSimTreeRandomBeamGenerator(const TSimTreeRandomBeamGenerator& rhs);
	// Assignment operator (prohibited)
	TSimTreeRandomBeamGenerator& operator=(const TSimTreeRandomBeamGenerator& rhs);
	
	
	ClassDef(TSimTreeRandomBeamGenerator,1)
};	
#endif // _TSIMTREERANDOMBEAMGENERATOR_H_