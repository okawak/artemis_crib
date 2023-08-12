// K.Okawa created <okawa@cns.s.u-tokyo.ac.jp>

#ifndef _TSIMYIELDPROCESSOR_H_
#define _TSIMYIELDPROCESSOR_H_

#include <TProcessor.h>
#include <TSpline.h>

namespace art {
	class TSimYieldProcessor;
}

class TClonesArray;

class art::TSimYieldProcessor : public TProcessor {
public:
	TSimYieldProcessor();
	virtual ~TSimYieldProcessor();
	
	void Init(TEventCollection*);
	void Process();

	Float_t get_Elab(Float_t energy){
		return ( (25.992333818 + 4.00260325413)/4.00260325413 ) * energy;
	}
	
protected:
	TString fInputTxtName;
	TString fOutputColName;

	TClonesArray  *fOutData; //!

	Double_t fSolidAngle;
	Long_t fEventNumber;
	Char_t char_he[34] = "HE";
	Double_t Na = 6.02e+23;
	Double_t he_A = 4.0;

	TSpline3 *cs; //!

private:
	// Copy constructor (prohibited)
	TSimYieldProcessor(const TSimYieldProcessor& rhs);
	// Assignment operator (prohibited)
	TSimYieldProcessor& operator=(const TSimYieldProcessor& rhs);
	
	
	ClassDef(TSimYieldProcessor,1)
};	
#endif // _TSIMYIELDPROCESSOR_H_