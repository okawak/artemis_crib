// K.Okawa created <okawa@cns.s.u-tokyo.ac.jp>

#ifndef _TSIMESPROCESSOR2_H_
#define _TSIMESPROCESSOR2_H_

#include "TSimGeometry.h"

#include <TProcessor.h>
#include <TVector3.h>

namespace art {
	class TSimESProcessor2;
}

class TClonesArray;

class art::TSimESProcessor2 : public TProcessor {
public:
	TSimESProcessor2();
	virtual ~TSimESProcessor2();
	
	void Init(TEventCollection*);
	void Process();
	
	Double_t energy_inv_square(Double_t z)
	{
		return p0 + p1*z + p2*z*z;
	};
	Double_t Integral_energy_inv_square(Double_t z)
	{
		return p0*z + p1*z*z/2.0 + p2*z*z*z/3.0;
	};

	Double_t Integral_angle_depend(Double_t a_stop);
	Double_t get_ReactionPos();
	Double_t get_ReactionAngle(); // cm_angle rad

	Double_t cm2lab_angle(Double_t angle);
	TVector3 get_proton_direction(Double_t beam_xdir, Double_t beam_ydir, Double_t beam_zdir, Double_t theta, Double_t phi);

protected:
	TString fInputColName;
	TString fOutputColName;

	TClonesArray **fInData; //!
	TClonesArray  *fOutData; //!

	Float_t fWindowZpos;
	Float_t fWindowThickness;
	Bool_t fInputHasData;


	Char_t char_mylar[34] = "MYLAR";
	Char_t char_he[34] = "HE";
	Float_t fIniEnergy = 55.5f; // energy after window

	// general
	Double_t ALPHA = 1.0/137.036;
	Double_t HBARC = 197.327e-13; // MeV cm
	Double_t esquare = ALPHA * HBARC; // e^2
	Double_t amu2MeV = 931.494;
	Double_t C = 299.792458; // mm/ns
	Long_t count;
	Long_t total_count;

	// target
	Double_t mylar_rho = 1.397; // g/cm3
	Double_t mylar_A = 192.0; // moleculer mass
	Double_t NA = 6.0221408e+23; // avogadro number
	Float_t mylar_thickness = 0.013f; // um

	// particle
	Float_t fMa = 25.992333818f;
	Float_t fMA = 1.007825031898f;
	Int_t fZa = 14;
	Int_t fZA = 1;

	// ratheford
	Double_t angle_start = 10.0 * (TMath::Pi()/180.0);
	Double_t angle_end = 180.0 * (TMath::Pi()/180.0);
	Double_t d_angle = 0.1 * (TMath::Pi()/180.0);

   	// calculation value
	Double_t p0, p1, p2;
	Double_t norm;
	Double_t norm_angle;
	Double_t prob;

	// experimental parameter
	Double_t beam_sigma = 1.53; // MeV
	Double_t SSD_sigma = 0.1; // MeV
	Double_t TDC_sigma = 5.0; // ns


private:
	// Copy constructor (prohibited)
	TSimESProcessor2(const TSimESProcessor2& rhs);
	// Assignment operator (prohibited)
	TSimESProcessor2& operator=(const TSimESProcessor2& rhs);
	
	
	ClassDef(TSimESProcessor2,1)
};	
#endif // _TSIMESPROCESSOR2_H_