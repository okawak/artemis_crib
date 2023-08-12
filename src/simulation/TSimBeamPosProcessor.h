// K.Okawa created <okawa@cns.s.u-tokyo.ac.jp>

#ifndef _TSIMBEAMPOSPROCESSOR_H_
#define _TSIMBEAMPOSPROCESSOR_H_

#include "TSimGeometry.h"

#include <TProcessor.h>

namespace art {
	class TSimBeamPosProcessor;
}

class TClonesArray;

class art::TSimBeamPosProcessor : public TProcessor {
public:
	TSimBeamPosProcessor();
	virtual ~TSimBeamPosProcessor();
	
	void Init(TEventCollection*);
	void Process();

	void ProcessUseGeoManager();
	void ProcessManual();
	
protected:
	TString fInputColName;
	TString fOutputColName;

	TClonesArray **fInData; //!
	TClonesArray  *fOutData; //!

	TSimGeometry *Geo;

	Int_t fLayerNum;
	Double_t fRotZpos;

	Bool_t fInputHasData;

private:
	// Copy constructor (prohibited)
	TSimBeamPosProcessor(const TSimBeamPosProcessor& rhs);
	// Assignment operator (prohibited)
	TSimBeamPosProcessor& operator=(const TSimBeamPosProcessor& rhs);
	
	
	ClassDef(TSimBeamPosProcessor,1)
};	
#endif // _TSIMBEAMPOSPROCESSOR_H_