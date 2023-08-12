// K.Okawa created <okawa@cns.s.u-tokyo.ac.jp>

#ifndef _TSIMTRACKBEAMGENERATOR_H_
#define _TSIMTRACKBEAMGENERATOR_H_

#include <TGeoManager.h>
#include <TGeoMaterial.h>
#include <TGeoMedium.h>

#include <TProcessor.h>

namespace art {
	class TSimTrackBeamGenerator;
}

class TClonesArray;

class art::TSimTrackBeamGenerator : public TProcessor {
public:
	TSimTrackBeamGenerator();
	virtual ~TSimTrackBeamGenerator();
	
	void Init(TEventCollection*);
	void Process();
	
protected:
	TString fInputColName1;
	TString fInputColName2;
	TString fOutputColName;

	TClonesArray **fInData1; //!
	TClonesArray **fInData2; //!
	TClonesArray  *fOutData; //!

	Double_t fWindowZ;

	Bool_t fInputHasData;

private:
	// Copy constructor (prohibited)
	TSimTrackBeamGenerator(const TSimTrackBeamGenerator& rhs);
	// Assignment operator (prohibited)
	TSimTrackBeamGenerator& operator=(const TSimTrackBeamGenerator& rhs);
	
	
	ClassDef(TSimTrackBeamGenerator,1)
};	
#endif // _TSIMTRACKBEAMGENERATOR_H_