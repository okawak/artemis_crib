// K.Okawa created <okawa@cns.s.u-tokyo.ac.jp>

#ifndef _TEFFTHICKNESSCALCULATION_H_
#define _TEFFTHICKNESSCALCULATION_H_

#include <TProcessor.h>

namespace art {
	class TEffThicknessCalculation;
}

class TClonesArray;

class art::TEffThicknessCalculation : public TProcessor {
public:
	TEffThicknessCalculation();
	virtual ~TEffThicknessCalculation();
	
	void Init(TEventCollection*);
	void Process();

	Float_t get_Ecm(Float_t energy){
		return ( fTargetM/(fM + fTargetM) ) * energy;
	}
	Float_t get_Elab(Float_t energy){
		return ( (fM + fTargetM)/fTargetM ) * energy;
	}


protected:
	Float_t fEnergy;
	Int_t fZ;
	Float_t fM;
	Float_t fTargetM;
	Float_t fPressure;
	Float_t fTemperature;
	Float_t fEnergyRange;
	TString fMaterial;
	Float_t fMaterialWeight;

	Char_t char_material[34];

private:
	// Copy constructor (prohibited)
	TEffThicknessCalculation(const TEffThicknessCalculation& rhs);
	// Assignment operator (prohibited)
	TEffThicknessCalculation& operator=(const TEffThicknessCalculation& rhs);
	
	
	ClassDef(TEffThicknessCalculation,1)
};	
#endif // _TEEFFTHICKNESSCALCULATION_H_