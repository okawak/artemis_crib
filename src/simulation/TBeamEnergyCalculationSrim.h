// K.Okawa created <okawa@cns.s.u-tokyo.ac.jp>

#ifndef _TBEAMENERGYCALCULATIONSRIM_H_
#define _TBEAMENERGYCALCULATIONSRIM_H_

#include <TProcessor.h>
#include <TSpline.h>

namespace art {
	class TBeamEnergyCalculationSrim;
}

class TClonesArray;

class art::TBeamEnergyCalculationSrim : public TProcessor {
public:
	TBeamEnergyCalculationSrim();
	virtual ~TBeamEnergyCalculationSrim();
	
	void Init(TEventCollection*);
	void Process();

	Double_t ObjFunc(Double_t ppaca, Double_t ppacb, Bool_t debug);
	Double_t Getchi2(Double_t ppaca, Double_t ppacb, Double_t distance, Int_t i, Bool_t debug);
	Double_t Brho2Energy(Double_t brho, Double_t m, Int_t z);
	void SrimInit();
	//void SetElossFuncion(TSpline3 *sp, TString name);
	void SetElossFuncion(Int_t ID, TString name);
	Double_t SrimEnewz(TSpline3 *sp, Double_t energy, Double_t length);
	//Double_t SrimEnewz(Int_t ID, Double_t energy, Double_t length);

protected:
	static const Int_t N = 17;
	Int_t fRunNumber[N]         = {195, 195, 196, 196, 196, 196, 199, 199, 199, 199, 201, 201, 201, 201, 202, 202, 203};

	Double_t fLowgain1[N]       = {1504.0, 1229.0, 2667.0, 2302.0, 1882.0, 1324.0, 2800.0, 2420.0, 2040.0, 1479.0, 2161.0, 1835.0, 1376.0, 672.2, 1425.0, 1151.0, 608.5};
	Double_t fLowgain2[N]       = {1434.0, 1170.0, 2570.0, 2219.0, 1810.0, 1262.0, 2692.0, 2320.0, 1946.0, 1398.0, 2068.0, 1749.0, 1302.0, 625.5, 1350.0, 1085.0, 539.2};
	Double_t fLowgain3[N]       = {1336.0, 1096.0, 2403.0, 2074.0, 1701.0, 1177.0, 2490.0, 2149.0, 1803.0, 1293.0, 1930.0, 1634.0, 1213.0, 586.0, 1258.0, 1011.0, 515.5};
	Double_t fLowgain4[N]       = {1325.0, 1094.0, 2398.0, 2077.0, 1703.0, 1190.0, 2485.0, 2144.0, 1800.0, 1297.0, 1920.0, 1631.0, 1217.0, 586.9, 1259.0, 1018.0, 527.5};

//	Double_t fLowgain1_gain[N]  = {1.0, 1.0, };
//	Double_t fLowgain2_gain[N]  = {1.0, 1.0, };
//	Double_t fLowgain3_gain[N]  = {1.0, 1.0, };
//	Double_t fLowgain4_gain[N]  = {1.0, 1.0, };

	Double_t fLowgain1_err[N]   = {2.7, 1.5, 4.2, 1.5, 3.6, 5.6, 2.2, 0.8, 1.4, 1.9, 3.7, 1.5, 2.5, 3.6, 4.6, 1.8, 2.7};
	Double_t fLowgain2_err[N]   = {2.0, 1.3, 2.9, 1.1, 3.6, 5.4, 1.7, 0.6, 1.3, 1.9, 2.6, 1.2, 2.4, 2.7, 2.5, 1.5, 2.6};
	Double_t fLowgain3_err[N]   = {1.5, 1.1, 1.9, 0.9, 3.9, 4.8, 1.2, 0.5, 1.3, 1.6, 2.0, 0.9, 2.2, 2.6, 1.9, 1.2, 1.4};
	Double_t fLowgain4_err[N]   = {1.3, 1.0, 1.6, 0.8, 4.7, 4.7, 1.0, 0.4, 1.5, 1.5, 1.5, 0.8, 2.3, 2.7, 1.6, 1.1, 1.1};

	Double_t fLowgain1_sigma[N] = {133.9, 144.9, 100.7, 102.4, 102.3, 122.7, 84.50, 77.29, 68.82, 76.33, 98.64, 96.86, 83.54, 90.45, 120.4, 117.6, 92.28};
	Double_t fLowgain2_sigma[N] = {121.5, 142.4, 99.02, 96.50, 103.1, 123.3, 81.81, 74.24, 66.51, 74.77, 95.00, 94.97, 83.11, 81.84, 103.2, 114.8, 110.9};
	Double_t fLowgain3_sigma[N] = {114.4, 134.4, 90.91, 89.96, 82.90, 114.4, 76.01, 67.51, 56.74, 71.12, 89.38, 85.00, 79.83, 76.53, 97.59, 109.5, 89.23};
	Double_t fLowgain4_sigma[N] = {117.5, 131.1, 94.47, 87.83, 90.08, 112.9, 73.80, 66.66, 60.76, 66.53, 86.91, 83.13, 81.15, 80.38, 100.3, 108.0, 64.3};

	Int_t fPPACCondition[N]     = {3, 3, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3}; // 0: no ppac 1: ppaca 2: ppacb 3: ppacs
	Int_t fWindowCondition[N]   = {1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2}; // 0: no window 1: 20um 2:10um
	Int_t fGasCondition[N]      = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // 0: he 1: ar
	Double_t fPressure[N]        = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 50.0, 50.0, 50.0, 50.0, 100.0, 100.0, 150.0};
	Int_t fIonZCondition[N]     = {14, 13, 14, 13, 12, 14, 14, 13, 12, 14, 14, 13, 12, 14, 14, 13, 14};
	Double_t fIonMCondition[N]   = {25.992333818, 24.990428308, 25.992333818, 24.990428308, 23.985041689, 25.992333818, 25.992333818, 24.990428308, 23.985041689, 25.992333818, 25.992333818, 24.990428308, 23.985041689, 25.992333818, 25.992333818, 24.990428308, 25.992333818};
	Int_t fIonCondition[N]      = {0, 1, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 0}; // 0: si14+ 1: al13+ 2: mg12+ 3: si13+

	Double_t brho = 0.577935;
	Double_t dead = 0.0005;
	Double_t temparature = 300.0;

	Int_t si_Z = 14;
	Int_t si2_Z = 13;
	Int_t al_Z = 13;
	Int_t mg_Z = 12;
	Double_t si_M = 25.9847;
	Double_t al_M = 24.9833;
	Double_t mg_M = 23.9785;

	TSpline3 *si14mylar;      // ID == 0
	TSpline3 *si14he50torr;   // ID == 1
	TSpline3 *si14he100torr;  // ID == 2
	TSpline3 *si14he150torr;  // ID == 3
	TSpline3 *si14al;         // ID == 4

	TSpline3 *si13mylar;      // ID == 5
	TSpline3 *si13he50torr;   // ID == 6
	TSpline3 *si13he100torr;  // ID == 7
	TSpline3 *si13he150torr;  // ID == 8
	TSpline3 *si13al;         // ID == 9

	TSpline3 *al13mylar;      // ID == 10
	TSpline3 *al13he50torr;   // ID == 11
	TSpline3 *al13he100torr;  // ID == 12
	TSpline3 *al13he150torr;  // ID == 13
	TSpline3 *al13al;         // ID == 14

	TSpline3 *mg12mylar;      // ID == 15
	TSpline3 *mg12he50torr;   // ID == 16
	TSpline3 *mg12he100torr;  // ID == 17
	TSpline3 *mg12he150torr;  // ID == 18
	TSpline3 *mg12al;         // ID == 19

private:
	// Copy constructor (prohibited)
	TBeamEnergyCalculationSrim(const TBeamEnergyCalculationSrim& rhs);
	// Assignment operator (prohibited)
	TBeamEnergyCalculationSrim& operator=(const TBeamEnergyCalculationSrim& rhs);
	
	
	ClassDef(TBeamEnergyCalculationSrim,1)
};	
#endif // _TBEAMENERGYCALCULATIONSRIM_H_