// K.Okawa created <okawa@cns.s.u-tokyo.ac.jp>

#ifndef _TSIMUTIL_H_ 
#define _TSIMUTIL_H_ 

#include <Rtypes.h>
#include <TMath.h>

namespace art {
    namespace Sim {
        // Common constants
        const Double_t u = 931.49432/1000.; // GeV
        const Double_t c = 299.7924; // speed of light, mm/ns
        const Double_t deg_to_rad = TMath::Pi()/180.0; // angle: degree to radian
        const Double_t rad_to_deg = 180.0/TMath::Pi(); // angle: radian to degree

        ////extern "C" {
        ////    void enewzsub_etot_(int *z1, float *m1, float *bfr_ene, char matter1[33], 
        ////            int *unit_pressure, float *pressure, float *temperature, 
        ////            int *unit_thick, float *thick1, float *aft_ene);
        ////    void eoldzsub_etot_(int *z1, float *m1, float *aft_ene, char matter1[33], 
        ////            int *unit_pressure, float *pressure, float *temperature, 
        ////            int *unit_thick, float *thick1, float *bfr_ene);
        ////    void rangezsub_etot_(int *z1, float *m1, float *bfr_ene, char matter1[33], 
        ////            float *range);
        ////    void srhogas_(float *pressure, float *temperature, int *unit_pressure,
        ////    		int *unit_temperature, float *mol_weight, 
        ////    		float *density);
        ////}

    }
}


#endif // _TSIMUTIL_H_
