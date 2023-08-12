// K.Okawa created <okawa@cns.s.u-tokyo.ac.jp>

#ifndef _TENERGYLOSSCHECK_H_
#define _TENERGYLOSSCHECK_H_

#include <TProcessor.h>

namespace art {
	class TEnergyLossCheck;
}

class TClonesArray;

class art::TEnergyLossCheck : public TProcessor {
public:
	TEnergyLossCheck();
	virtual ~TEnergyLossCheck();
	
	void Init(TEventCollection*);
	void Process();

protected:
	static const Int_t N = 4;

    Double_t he_pressure[N] = {0.0, 50.0, 100.0, 150.0};
    Double_t ar_pressure[N] = {0.0, 8.8, 18.0, 27.5};

    Double_t he_adc[N] = {2485.0, 1920.0, 1259.0, 527.5};
    Double_t ar_adc[N] = {2465.0, 1953.0, 1387.0, 760.6};

    Double_t he_adc_err[N] = {1.0, 1.5, 1.6, 1.1};
    Double_t ar_adc_err[N] = {1.1, 1.6, 1.5, 1.2};

    Double_t he_adc_sigma[N] = {73.80, 86.91, 100.3, 64.3};
    Double_t ar_adc_sigma[N] = {75.35, 78.48, 83.70, 92.24};


	Float_t ini_energy = 55.5f;
	Float_t distance = 562.6f;
	Float_t dead = 0.0005f;
	Float_t temparature = 300.0f;

	Int_t si_Z = 14;
	Float_t si_M = 25.992333818f;

	Char_t char_mylar[34] = "MYLAR";
	Char_t char_he[34] = "HE";
	Char_t char_ar[34] = "AR";
	Char_t char_al[34] = "AL";
	Char_t char_si[34] = "SI";

	Double_t he_offset = 3.229;
	Double_t he_gain = 0.02016;

	Double_t ar_offset = 3.229;
	Double_t ar_gain = 0.02016;
	Float_t factor = 205.0f/179.0f;


private:
	// Copy constructor (prohibited)
	TEnergyLossCheck(const TEnergyLossCheck& rhs);
	// Assignment operator (prohibited)
	TEnergyLossCheck& operator=(const TEnergyLossCheck& rhs);
	
	
	ClassDef(TEnergyLossCheck,1)
};	
#endif // _TENERGYLOSSCHECK_H_