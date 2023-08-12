// K.Okawa created <okawa@cns.s.u-tokyo.ac.jp>

#ifndef _TSIMESPROCESSOR_H_
#define _TSIMESPROCESSOR_H_

#include "TSimGeometry.h"

#include <TProcessor.h>

namespace art {
	class TSimESProcessor;
}

class TClonesArray;

class art::TSimESProcessor : public TProcessor {
public:
	TSimESProcessor();
	virtual ~TSimESProcessor();
	
	void Init(TEventCollection*);
	void Process();
	
	Double_t get_ReactionPos();
	Double_t get_ReactionAngle(); // cm_angle rad
	Double_t cm2lab_angle(Double_t angle);

protected:
	TString fInputColName;
	TString fOutputColName;

	TClonesArray **fInData; //!
	TClonesArray  *fOutData; //!

	Bool_t fInputHasData;


	Char_t char_mylar[34] = "MYLAR";
	Char_t char_he[34] = "HE";
	Float_t fIniEnergy = 54.47f;

   	//Double_t gamma = 25.992333818/1.007825031898; // si26/proton 
	Double_t p0, p1, p2;
	Double_t norm;

private:
	// Copy constructor (prohibited)
	TSimESProcessor(const TSimESProcessor& rhs);
	// Assignment operator (prohibited)
	TSimESProcessor& operator=(const TSimESProcessor& rhs);
	
	
	ClassDef(TSimESProcessor,1)
};	
#endif // _TSIMESPROCESSOR_H_