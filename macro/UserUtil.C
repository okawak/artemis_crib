/**
 * @file    UserUtil.C
 * @brief
 * @author  Kodai Okawa<okawa@cns.s.u-tokyo.ac.jp>
 * @date    2024-01-19 00:06:24
 * @note
 */

#include <glob.h>

/////////////////////////////////////////////////////////////////////////////
// TCutG Object
/////////////////////////////////////////////////////////////////////////////

TCutG *getTCutObject(TString filepath, TString tcutname) {
    FileStat_t info;
    if (gSystem->GetPathInfo(filepath, info) != 0) {
        std::cerr << "Error in <userlogon.C>: cannot open: " << filepath << std::endl;
        return NULL;
    }
    TFile *file = new TFile(filepath, "read");

    TCutG *cut = (TCutG *)file->Get(tcutname);
    if (!cut) {
        std::cerr << "Error in <userlogon.C>: cannot find TCutG object: " << tcutname << std::endl;
        return NULL;
    }

    file->Close();
    std::cout << "[Info] TCutG object \"" << cut->GetName() << "\" is loaded \t(VarX:" << cut->GetVarX()
              << " VarY:" << cut->GetVarY() << ")" << std::endl;
    return cut;
}

void getAllTCutObject() {
    glob_t globbuf;
    glob("gate/*.root", 0, NULL, &globbuf);
    for (Int_t i = 0; i < globbuf.gl_pathc; i++) {
        TString filepath = (globbuf.gl_pathv[i]);
        TString file = filepath(filepath.First("/") + 1, filepath.Length());
        TString gate = file(0, file.First("."));
        getTCutObject(filepath, gate);
    }
    globfree(&globbuf);
}

/////////////////////////////////////////////////////////////////////////////
// kinematic TGraph object (like LISE calculator)
// A(a,b)B reaction
// input:
//    Ebeam                  : beam energy (MeV)
//    beam_z, beam_a         : (Z, A) for particle "a"
//    target_z, target_a     : (Z, A) for particle "A"
//    fragment_z, fragment_a : (Z, A) for particle "b"
//    residual_z, residual_a : (Z, A) for particle "B"
//    particle               : 0: reaction particle, 1: residual particle
/////////////////////////////////////////////////////////////////////////////

// angle lab vs. angle cm
TGraph *GetALabACM(Double_t Ebeam,
                   Int_t beam_z, Int_t beam_a, Int_t target_z, Int_t target_a,
                   Int_t fragment_z, Int_t fragment_a, Int_t residual_z, Int_t residual_a,
                   UShort_t particle = 0) {
    // get mass MeV unit
    Double_t Ma = gAtomicMassTable->GetNucleusMass(beam_z, beam_a);
    Double_t MA = gAtomicMassTable->GetNucleusMass(target_z, target_a);
    Double_t Mb = gAtomicMassTable->GetNucleusMass(fragment_z, fragment_a);
    Double_t MB = gAtomicMassTable->GetNucleusMass(residual_z, residual_a);

    TGraph *gr = new TGraph();
    for (Int_t i = 0; i <= 180; i++) {
        Double_t theta_cm = (Double_t)i;
    }

    return gr;
}

// energy lab vs. angle cm
TGraph *GetELabACM(Double_t Ebeam,
                   Int_t beam_z, Int_t beam_a, Int_t target_z, Int_t target_a,
                   Int_t fragment_z, Int_t fragment_a, Int_t residual_z, Int_t residual_a,
                   UShort_t particle = 0) {
    // get mass MeV unit
    Double_t Ma = gAtomicMassTable->GetNucleusMass(beam_z, beam_a);
    Double_t MA = gAtomicMassTable->GetNucleusMass(target_z, target_a);
    Double_t Mb = gAtomicMassTable->GetNucleusMass(fragment_z, fragment_a);
    Double_t MB = gAtomicMassTable->GetNucleusMass(residual_z, residual_a);

    TGraph *gr = new TGraph();
    for (Int_t i = 0; i <= 180; i++) {
        Double_t theta_cm = (Double_t)i;
    }

    return gr;
}

// angle lab of "B" vs. angle lab of "b"
TGraph *GetALabALab(Double_t Ebeam,
                    Int_t beam_z, Int_t beam_a, Int_t target_z, Int_t target_a,
                    Int_t fragment_z, Int_t fragment_a, Int_t residual_z, Int_t residual_a) {
    // get mass MeV unit
    Double_t Ma = gAtomicMassTable->GetNucleusMass(beam_z, beam_a);
    Double_t MA = gAtomicMassTable->GetNucleusMass(target_z, target_a);
    Double_t Mb = gAtomicMassTable->GetNucleusMass(fragment_z, fragment_a);
    Double_t MB = gAtomicMassTable->GetNucleusMass(residual_z, residual_a);

    TGraph *gr = new TGraph();
    for (Int_t i = 0; i <= 180; i++) {
        Double_t theta_cm = (Double_t)i;
    }

    return gr;
}

// energy lab vs. angle lab
TGraph *GetELabALab(Double_t Ebeam,
                    Int_t beam_z, Int_t beam_a, Int_t target_z, Int_t target_a,
                    Int_t fragment_z, Int_t fragment_a, Int_t residual_z, Int_t residual_a,
                    UShort_t particle = 0) {
    // get mass MeV unit
    Double_t Ma = gAtomicMassTable->GetNucleusMass(beam_z, beam_a);
    Double_t MA = gAtomicMassTable->GetNucleusMass(target_z, target_a);
    Double_t Mb = gAtomicMassTable->GetNucleusMass(fragment_z, fragment_a);
    Double_t MB = gAtomicMassTable->GetNucleusMass(residual_z, residual_a);

    TGraph *gr = new TGraph();
    for (Int_t i = 0; i <= 180; i++) {
        Double_t theta_cm = (Double_t)i;
    }

    return gr;
}
