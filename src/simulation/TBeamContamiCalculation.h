// K.Okawa created <okawa@cns.s.u-tokyo.ac.jp>

#ifndef _TBEAMCONTAMICALCULATION_H_
#define _TBEAMCONTAMICALCULATION_H_

#include <TProcessor.h>

namespace art {
	class TBeamContamiCalculation;
}

class TClonesArray;

class art::TBeamContamiCalculation : public TProcessor {
public:
	TBeamContamiCalculation();
	virtual ~TBeamContamiCalculation();
	
	void Init(TEventCollection*);
	void Process();

	Double_t ObjFunc(Float_t ratio, Bool_t debug);
	Double_t Getchi2(Float_t ratio, Float_t distance, Int_t i, Bool_t debug);
	Float_t Brho2Energy(Float_t brho, Float_t m, Int_t z);

protected:
	static const Int_t N = 12;
	Int_t fRunNumber[N]         = {244, 244, 244, 244, 245, 245, 245, 245, 246, 246, 247, 247};

	Double_t fLowgain1[N]       = {2572.0, 2224.0, 1873.0, 1366.0, 2055.0, 1759.0, 1358.0, 762.6, 1470.0, 1229.0, 820.9, 756.5};
	Double_t fLowgain2[N]       = {2580.0, 2226.0, 1866.0, 1348.0, 2049.0, 1751.0, 1342.0, 732.4, 1456.0, 1214.0, 797.9, 589.3};
	Double_t fLowgain3[N]       = {2447.0, 2111.0, 1771.0, 1280.0, 1939.0, 1659.0, 1281.0, 697.2, 1377.0, 1151.0, 755.0, 557.2};
	Double_t fLowgain4[N]       = {2465.0, 2129.0, 1787.0, 1292.0, 1953.0, 1675.0, 1285.0, 708.8, 1387.0, 1157.0, 760.6, 561.5};

	Double_t fLowgain1_err[N]   = {1.8, 0.9, 2.3, 3.1, 2.5, 1.3, 3.6, 4.0, 2.4, 1.9, 1.8, 1.4};
	Double_t fLowgain2_err[N]   = {1.5, 0.8, 2.3, 3.1, 2.2, 1.3, 3.5, 5.0, 2.2, 1.6, 1.6, 1.3};
	Double_t fLowgain3_err[N]   = {1.2, 0.7, 2.1, 3.0, 1.7, 1.1, 3.5, 4.4, 1.7, 1.4, 1.2, 1.1};
	Double_t fLowgain4_err[N]   = {1.1, 0.6, 2.2, 2.8, 1.6, 1.1, 3.1, 4.4, 1.5, 1.3, 1.2, 1.1};

	Double_t fLowgain1_sigma[N] = {78.95, 77.51, 73.00, 83.96, 81.43, 82.67, 78.50, 72.70, 88.06, 106.9, 94.08, 110.9};
	Double_t fLowgain2_sigma[N] = {79.39, 78.46, 76.62, 84.44, 86.76, 82.37, 77.02, 90.92, 92.20, 104.3, 94.21, 110.3};
	Double_t fLowgain3_sigma[N] = {78.04, 71.77, 70.90, 81.72, 80.33, 79.32, 77.84, 82.32, 84.25, 98.17, 90.05, 103.9};
	Double_t fLowgain4_sigma[N] = {75.35, 70.24, 88.89, 77.67, 78.48, 78.89, 71.17, 82.58, 83.70, 97.35, 92.24, 106.6};

	//Int_t fPPACCondition[N]     = {}; // 0: no ppac 1: ppaca 2: ppacb 3: ppacs
	//Int_t fWindowCondition[N]   = {}; // 0: no window 1: 20um 2:10um
	//Int_t fGasCondition[N]      = {}; // 0: he 1: ar
	Float_t fPressure[N]        = {0.0f, 0.0f, 0.0f, 0.0f, 8.8f, 8.8f, 8.8f, 8.8f, 18.0f, 18.0f, 27.5f, 27.5f};
	Int_t fIonZCondition[N]     = {14, 13, 12, 14, 14, 13, 12, 14, 14, 13, 14, 13};
	Float_t fIonMCondition[N]   = {25.992333818f, 24.990428308f, 23.985041689f, 25.992333818f, 25.992333818f, 24.990428308f, 23.985041689f, 25.992333818f, 25.992333818f, 24.990428308f, 25.992333818f, 24.990428308f};
	Int_t fIonCondition[N]      = {0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 0, 1}; // 0: si14+ 1: al13+ 2: mg12+ 3: si13+

	Float_t brho = 0.577935f;
	Float_t dead = 0.0005f;
	Float_t temparature = 300.0f;

	Int_t si_Z = 14;
	Int_t si2_Z = 13;
	Int_t al_Z = 13;
	Int_t mg_Z = 12;
	Float_t si_M = 25.992333818f;
	Float_t al_M = 24.990428308f;
	Float_t mg_M = 23.985041689f;

	Char_t char_mylar[34] = "MYLAR";
	Char_t char_he[34] = "HE";
	Char_t char_ar[34] = "AR";
	Char_t char_al[34] = "AL";
	Char_t char_si[34] = "SI";

	Double_t gain[4]   = {0.01844, 0.01894, 0.02051, 0.02067};
	Double_t offset[4] = {1.007, 1.653, 1.417, 1.137};

	Float_t ppaca_thick = 0.0122f;
	Float_t ppacb_thick = 0.0119f;


private:
	// Copy constructor (prohibited)
	TBeamContamiCalculation(const TBeamContamiCalculation& rhs);
	// Assignment operator (prohibited)
	TBeamContamiCalculation& operator=(const TBeamContamiCalculation& rhs);
	
	
	ClassDef(TBeamContamiCalculation,1)
};	
#endif // _TBEAMCONTAMICALCULATION_H_