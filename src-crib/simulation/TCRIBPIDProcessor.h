/**
 * @file    TCRIBPIDProcessor.h
 * @brief   Beam PID at F2 and F3 of CRIB
 * @author  Kodai Okawa <okawa@cns.s.u-tokyo.ac.jp>
 * @date    2023-12-19 15:30:55
 * @note    last modified: 2024-08-23 21:08:29
 * @details
 */

#ifndef _CRIB_TCRIBPIDPROCESSOR_H_
#define _CRIB_TCRIBPIDPROCESSOR_H_

#include <TProcessor.h>
#include <TSrim.h> // TSrim library

namespace art::crib {
class TCRIBPIDProcessor;
} // namespace art::crib

class TClonesArray;

class art::crib::TCRIBPIDProcessor : public TProcessor {
  public:
    TCRIBPIDProcessor();
    ~TCRIBPIDProcessor();

    void Init(TEventCollection *) override;
    void Process() override;

    const Double_t kAmu2MeV = 931.49432;         // amu -> MeV/c^2
    const Double_t kLightSpeed = 299792458.0;    // m/s
    const Double_t kJ2MeV = 6.2415064e+12;       // J -> MeV
    const Double_t kUnitCharge = 1.60217663e-19; // C (A s)
    const Double_t kLengthF0F2 = 7.8;            // m
    const Double_t kLengthF0F3 = 12.97;          // m

    Double_t E2m_s(Double_t Ekin, Double_t mass) { // Ekin: MeV, mass: MeV/c^2
        return kLightSpeed * TMath::Sqrt(1.0 - TMath::Power(1.0 / (Ekin / mass + 1.0), 2.0));
    };

  protected:
    TString fFileName;
    Bool_t fIsBatch;

    TSrim *srim;

  private:
    std::vector<std::string> ion_names;
    IntVec_t ion_massnum;
    IntVec_t ion_charges;
    DoubleVec_t ion_masses; // MeV/c^2
    IntVec_t ion_colors;

    Double_t f1_brho; // Tm
    std::string degrader_mat;
    Double_t degrader_thick; // mm
    Double_t rf_period;      // ns

    Double_t f2_ppac_thickness; // mm, mylar
    Double_t f2_ssd_thickness;  // mm

    Double_t a_thickness; // mm, mylar, PPACa/MWDCa
    Double_t b_thickness; // mm, mylar, PPACb/MWDCb
    Double_t distance;    // mm, between two tracking detectors
    UShort_t trigger;     // 0: PPACa/MWDCa, 1: PPACb/MWDCn

    Double_t f2_rf_offset;    // ns
    Double_t f3_rf_offset;    // ns
    Double_t tof_offset;      // ns
    DoubleVec_t f2_rf_range;  // ns
    DoubleVec_t f3_rf_range;  // ns
    DoubleVec_t tof_range;    // ns
    DoubleVec_t energy_range; // MeV

    void LoadPIDyaml();
    void SetSRIMObject();

    TCRIBPIDProcessor(const TCRIBPIDProcessor &rhs) = delete;
    TCRIBPIDProcessor &operator=(const TCRIBPIDProcessor &rhs) = delete;

    ClassDefOverride(TCRIBPIDProcessor, 1)
};

#endif // end of #ifndef _TCRIBPIDPROCESSOR_H_
