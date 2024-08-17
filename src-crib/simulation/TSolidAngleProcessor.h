/**
 * @file    TSolidAngleProcessor.h
 * @brief
 * @author  Kodai Okawa <okawa@cns.s.u-tokyo.ac.jp>
 * @date    2023-08-01 11:08:17
 * @note    last modified: 2024-08-17 16:12:57
 * @details
 */

#ifndef _TSOLIDANGLEPROCESSOR_H_
#define _TSOLIDANGLEPROCESSOR_H_

#include <TProcessor.h>

#include <TH1.h>
#include <TH2.h>

namespace art {
class TSolidAngleProcessor;
}

class TClonesArray;

class art::TSolidAngleProcessor : public TProcessor {
  public:
    /// @brief default constructor
    TSolidAngleProcessor();
    /// @brief default destructor
    ~TSolidAngleProcessor();

    /// @brief Init (override)
    /// @param col
    void Init(TEventCollection *col) override;

    /// @brief Process (override)
    void Process() override;
    /// @brief EndOfRun process (override)
    void EndOfRun() override;

  protected:
    /// @brief Input detected particle object name
    TString fInputColName;
    /// @brief Input reaction object name
    TString fInputReacColName;
    /// @brief Input detected particle object
    TClonesArray **fInData; //!
    /// @brief Input reaction object
    TClonesArray **fInReacData; //!

    /// @brief Histogram bin number
    Int_t fNbin_angle;
    /// @brief Histogram range (min, max)
    DoubleVec_t fRange_angle;
    /// @brief Histogram bin number
    Int_t fNbin_energy;
    /// @brief Histogram range (min, max)
    DoubleVec_t fRange_energy;

    /// @brief Output histogram ROOT file name
    TString fFileName;

    /// @brief solid angle (x: angle_cm)
    TH1D *h1_a;
    /// @brief for normalize (x: angle_cm)
    TH1D *h1_a_all;
    /// @brief solid angle (x: Ecm)
    TH1D *h1_e;
    /// @brief for normalize (x: Ecm)
    TH1D *h1_e_all;
    /// @brief solid angle (x: Ecm, y: angle_cm)
    TH2D *h2;
    /// @brief for normalie (x: Ecm, y: angle_cm)
    TH2D *h2_all;

  private:
    TSolidAngleProcessor(const TSolidAngleProcessor &rhs) = delete;
    TSolidAngleProcessor &operator=(const TSolidAngleProcessor &rhs) = delete;

    ClassDefOverride(TSolidAngleProcessor, 1)
};

#endif // end of #ifndef _TSOLIDANGLEPROCESSOR_H_
