// K.Okawa created <okawa@cns.s.u-tokyo.ac.jp>

#ifndef _TSIMTIMING_H_
#define _TSIMTIMING_H_

#include "TSimGeometry.h"

#include <TProcessor.h>
#include <TSpline.h>

namespace art {
	class TSimTiming;
}

class TClonesArray;

class art::TSimTiming : public TProcessor {
public:
	TSimTiming();
	virtual ~TSimTiming();
	
	void Init(TEventCollection*);
	void Process();
	
	Float_t get_Etotal(Float_t elab, Double_t L_angle);

protected:
	TString fInputColName;
	TString fOutputColName;

	TClonesArray **fInData; //!
	TClonesArray  *fOutData; //!

	Bool_t fInputHasData;


	//Char_t char_mylar[34] = "MYLAR";
	Char_t char_he[34] = "HE";
	Float_t fIniEnergy = 55.5f;

	TSpline3 *sp_time;
   	//Double_t gamma = 25.992333818/1.007825031898; // si26/proton 


	// general
	Double_t ALPHA = 1.0/137.036;
	Double_t HBARC = 197.327e-13; // MeV cm
	Double_t esquare = ALPHA * HBARC; // e^2
	Double_t amu2MeV = 931.494;
	Double_t C = 299.792458; // mm/ns
	Long_t count;
	Long_t total_count;

	// particle
	Float_t fMSi = 25.992333818f;
	Float_t fMp = 1.007825031898f;
	Float_t fMrin_base = 28.981800368f;
	Float_t fMrin = fMrin_base + 1.383f/(Float_t)amu2MeV;
	Float_t fMalpha = 4.00260325413f;
	Double_t Q_value_base = 4.95; //MeV
	Double_t Q_value = Q_value_base - 1.383; //MeV
	Int_t fZSi = 14;
	Int_t fZp = 1;

	// experimental parameter
	Double_t beam_sigma = 1.53; // MeV
	Double_t SSD_sigma = 0.1; // MeV
	Double_t TDC_sigma = 5.0; // ns

private:
	// Copy constructor (prohibited)
	TSimTiming(const TSimTiming& rhs);
	// Assignment operator (prohibited)
	TSimTiming& operator=(const TSimTiming& rhs);
	
	
	ClassDef(TSimTiming,1)
};	
#endif // _TSIMTIMING_H_