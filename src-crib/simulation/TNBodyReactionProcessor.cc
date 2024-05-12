/**
 * @file    TNBodyReactionProcessor.cc
 * @brief
 * @author  Kodai Okawa<okawa@cns.s.u-tokyo.ac.jp>
 * @date    2023-08-01 22:36:36
 * @note    for constant cross section
 */

#include "TNBodyReactionProcessor.h"
#include "../reconst/TReactionInfo.h"
#include "TParticleInfo.h"

#include <TArtAtomicMassTable.h>
#include <TDataObject.h>
#include <constant.h>

#include <TClass.h>
#include <TClonesArray.h>
#include <TLorentzVector.h>
#include <TRandom.h>

using art::TNBodyReactionProcessor;

ClassImp(TNBodyReactionProcessor);

TNBodyReactionProcessor::TNBodyReactionProcessor() : fInData(NULL), fOutData(NULL), fOutReacData(NULL) {
    RegisterInputCollection("InputCollection", "input branch (collection) name", fInputColName, TString("input"));
    RegisterOutputCollection("OutputCollection", "output branch (collection) name", fOutputColName,
                             TString("reaction_particles"));
    RegisterOutputCollection("OutputReactionCollection", "output branch (collection) name", fOutputReacColName,
                             TString("reaction"));

    // Beam information
    RegisterProcessorParameter("BeamName", "name of beam", fBeamName, TString(""));

    // Target information
    RegisterProcessorParameter("TargetMassNum", "Target mass number", fTargetMassNum, 0);
    RegisterProcessorParameter("TargetAtomicNum", "Target atomic number", fTargetAtmNum, 0);
    RegisterProcessorParameter("TargetName", "name of target material", fTargetName, TString(""));
    RegisterProcessorParameter("TargetThickness", "Target mass", fTargetThickness, 0.);
    RegisterProcessorParameter("TargetisGas", "Bool, target is targer or not", fTargetisGas, false);
    RegisterProcessorParameter("MinusPosition", "Allow minus position for energy spread effect", fMinusPosition, 0.);

    // reaction particles information
    IntVec_t init_i_vec;
    DoubleVec_t init_d_vec;
    StringVec_t init_s_vec;
    RegisterProcessorParameter("DecayParticleNum", "reaction particle number", fDecayNum, 1);
    RegisterProcessorParameter("ReactionMassNum", "reaction particles mass number", fReacMassNum, init_i_vec);
    RegisterProcessorParameter("ReactionAtomicNum", "reaction particles atomic number", fReacAtmNum, init_i_vec);
    RegisterProcessorParameter("ReactionChargeNum", "reaction particles charge number", fReacChargeNum, init_i_vec);
    RegisterProcessorParameter("ExciteLevel", "energy level for id=0 nucleus", fExciteLevel, init_d_vec);
    RegisterProcessorParameter("ReactionParticleName", "reaction particle names", fReacPartName, init_s_vec);
}

TNBodyReactionProcessor::~TNBodyReactionProcessor() {
    delete fOutData;
    delete fOutReacData;
    delete fElossTable;
    fOutData = NULL;
    fOutReacData = NULL;
    fElossTable = NULL;
}

void TNBodyReactionProcessor::Init(TEventCollection *col) {
    Info("Init", "\033[1mNOTE\033[m: this is constant cross section and uniform the reaction position");
    Info("Init", "%s => %s, decay num:%d, reaction info => %s", fInputColName.Data(), fOutputColName.Data(), fDecayNum, fOutputReacColName.Data());
    Info("Init", "%s beam => %s, target: (A=%d, Z=%d)", fBeamName.Data(), fTargetName.Data(), fTargetMassNum, fTargetAtmNum);

    if (fDecayNum != fReacMassNum.size() || fDecayNum != fReacAtmNum.size() || fDecayNum != fReacChargeNum.size()) {
        SetStateError("input yaml format is wrong");
        return;
    }

    for (Int_t i = 0; i < fDecayNum; i++) {
        Info("Init", "reaction products: id=%d %s(A=%d, Z=%d, q=%d)", i, fReacPartName[i].Data(),
             fReacMassNum[i], fReacAtmNum[i], fReacChargeNum[i]);
    }

    if (fMinusPosition > 0.01) {
        SetStateError("input yaml MinusPosition is invalid, need 0 or minus value");
        return;
    } else if (fMinusPosition < 0.01) {
        Info("Init", "reaction position allow up to %lf mm", fMinusPosition);
    }

    fInData = reinterpret_cast<TClonesArray **>(col->GetObjectRef(fInputColName.Data()));
    if (!fInData) {
        SetStateError(TString::Format("input not found: %s", fInputColName.Data()));
        return;
    }
    const TClass *const cl = (*fInData)->GetClass();
    if (!cl->InheritsFrom(art::TParticleInfo::Class())) {
        SetStateError("contents of input array must inherit from art::TParticleInfo");
    }

    fOutData = new TClonesArray("art::TParticleInfo");
    fOutData->SetName(fOutputColName);
    col->Add(fOutputColName, fOutData, fOutputIsTransparent);

    fOutReacData = new TClonesArray("art::TReactionInfo");
    fOutReacData->SetName(fOutputReacColName);
    col->Add(fOutputReacColName, fOutReacData, fOutputIsTransparent);

    if (fExciteLevel.size() == 0) {
        fExciteLevel.emplace_back(0.0);
    }

    fElossTable = new SRIMData();
    fElossTarget = fElossTable->GetTable(fBeamName, fTargetName);
    for (Int_t i = 0; i < fDecayNum; i++) {
        fElossProducts.emplace_back(fElossTable->GetTable(fReacPartName[i], fTargetName));
    }

    gRandom->SetSeed(time(NULL));
}

void TNBodyReactionProcessor::Process() {
    fOutData->Clear("C");
    fOutReacData->Clear("C");

    if ((*fInData)->GetEntriesFast() != 1) {
        SetStateError("input branch entry is not 1");
        return;
    }

    const TDataObject *const inData = static_cast<TDataObject *>((*fInData)->At(0));
    const TParticleInfo *const Data = dynamic_cast<const TParticleInfo *>(inData);

    Double_t target_mass = gAtomicMassTable->GetNucleusMass(fTargetAtmNum, fTargetMassNum);
    TLorentzVector target_vec(0., 0., 0., target_mass);
    TLorentzVector beam_vec = Data->GetLorentzVector();
    Double_t beam_mass = gAtomicMassTable->GetNucleusMass(Data->GetAtomicNumber(), Data->GetMassNumber());
    Double_t beam_energy = Data->GetEnergy();
    Double_t init_posz = Data->GetCurrentZ();

    // target should be set at z=0
    Double_t reac_posz;
    if (fTargetisGas) {
        Double_t range = fElossTarget->GetRange(beam_energy);
        if (range < fTargetThickness) {
            reac_posz = (range - fMinusPosition) * gRandom->Uniform();
            reac_posz += fMinusPosition;
        } else {
            reac_posz = (fTargetThickness - fMinusPosition) * gRandom->Uniform();
            reac_posz += fMinusPosition;
        }
    } else {
        // reac_posz is almost 0
        reac_posz = (fTargetThickness - fMinusPosition) * gRandom->Uniform();
        reac_posz += fMinusPosition;
    }
    Double_t reac_posx = Data->GetTrack().GetX(reac_posz);
    Double_t reac_posy = Data->GetTrack().GetY(reac_posz);

    Double_t thickness =
        TVector3(reac_posx - Data->GetTrack().GetX(init_posz), reac_posy - Data->GetTrack().GetY(init_posz), reac_posz).Mag();
    if (reac_posz > 0) {
        beam_vec = GetLossEnergyVector(beam_vec, beam_energy - fElossTarget->GetNewE(beam_energy, thickness));
    } else {
        beam_vec = GetLossEnergyVector(beam_vec, beam_energy - fElossTarget->GetOldE(beam_energy, thickness));
    }

    // calculate tof (mean value)
    Double_t duration_beam = 0;
    if (fTargetisGas) {
        duration_beam += thickness / (TMath::Sqrt(1.0 - TMath::Power(beam_mass / beam_vec.E(), 2.0)) * c);
    } // if solid target, tof is almost zero

    DoubleVec_t reac_masses;
    for (Int_t iPart = 0; iPart < fDecayNum; iPart++) {
        reac_masses.emplace_back(gAtomicMassTable->GetNucleusMass(fReacAtmNum[iPart], fReacMassNum[iPart]));
    }

    TLorentzVector compound_vec = beam_vec + target_vec;

    TVector3 beta_vec = compound_vec.BoostVector();
    beam_vec.Boost(-beta_vec);
    target_vec.Boost(-beta_vec);
    Double_t energy_cm = (beam_vec.E() - beam_vec.M()) + (target_vec.E() - target_mass);

    // need to change MeV to GeV
    compound_vec *= 0.001;
    DoubleVec_t GeVMass;
    for (Int_t i = 0; i < reac_masses.size(); i++) {
        GeVMass.emplace_back(reac_masses[i] * 0.001);
    }

    UInt_t excited_level = gRandom->Integer(fExciteLevel.size());
    GeVMass[0] += fExciteLevel[excited_level] * 0.001; // excited treatment

    Bool_t isOkay = event.SetDecay(compound_vec, fDecayNum, GeVMass.data());
    if (!isOkay) {
        std::cerr << "forbidden kinematics" << std::endl;
    }
    event.Generate();

    Double_t theta_cm;
    for (Int_t iPart = 0; iPart < fDecayNum; ++iPart) {
        TLorentzVector reac_vec = *event.GetDecay(iPart);
        // need to change GeV to MeV
        reac_vec *= 1000.;

        TParticleInfo *outData = static_cast<TParticleInfo *>(fOutData->ConstructedAt(iPart));
        outData->SetID(iPart);
        outData->SetMassNumber(fReacMassNum[iPart]);
        outData->SetAtomicNumber(fReacAtmNum[iPart]);
        outData->SetCharge(fReacChargeNum[iPart]);
        outData->SetTrack(reac_posx, reac_posy, reac_posz, TMath::ATan(reac_vec.Px() / reac_vec.Pz()),
                          TMath::ATan(reac_vec.Py() / reac_vec.Pz()));
        if (fTargetisGas) {
            outData->SetLorentzVector(reac_vec);
            outData->SetEnergy(reac_vec.E() - reac_masses[iPart]);
            outData->SetCurrentZ(reac_posz);
            outData->SetZeroTime();
            outData->AddTime(duration_beam);
        } else {
            Double_t first_energy = reac_vec.E() - reac_masses[iPart];
            if (first_energy > 0.01) {
                Double_t posx = outData->GetTrack().GetX(fTargetThickness);
                Double_t posy = outData->GetTrack().GetY(fTargetThickness);

                Double_t outthick = TVector3(posx - outData->GetTrack().GetX(reac_posz),
                                             posy - outData->GetTrack().GetY(reac_posz), fTargetThickness)
                                        .Mag();
                TLorentzVector out_vec =
                    GetLossEnergyVector(reac_vec, first_energy - fElossProducts[iPart]->GetNewE(first_energy, outthick));

                outData->SetLorentzVector(out_vec);
                outData->SetEnergy(out_vec.E() - reac_masses[iPart]);
                outData->SetCurrentZ(fTargetThickness);
                outData->SetZeroTime();
            } else {
                // outData->SetLorentzVector(reac_vec);
                outData->SetLorentzVector(0.0, 0.0, 0.0, reac_masses[iPart]);
                outData->SetEnergy(0.0);
                outData->SetCurrentZ(reac_posz);
                outData->SetZeroTime();
            }
        }

        reac_vec.Boost(-beta_vec);
        outData->SetThetaCM(reac_vec.Theta() / deg2rad);
        outData->SetPhiCM(reac_vec.Phi() / deg2rad);
        if (iPart == 0) {
            theta_cm = (Data->GetLorentzVector()).Angle(reac_vec.Vect()) / deg2rad;
        }
    }

    TReactionInfo *outReacData = static_cast<TReactionInfo *>(fOutReacData->ConstructedAt(0));
    outReacData->SetID(0);
    outReacData->SetExID(excited_level);
    outReacData->SetEnergy(energy_cm);
    outReacData->SetTheta(theta_cm);
    outReacData->SetXYZ(reac_posx, reac_posy, reac_posz);
}

TLorentzVector TNBodyReactionProcessor::GetLossEnergyVector(TLorentzVector vec, Double_t eloss) {
    Double_t factor =
        ((vec.E() - eloss) * (vec.E() - eloss) - vec.M() * vec.M()) / (vec.E() * vec.E() - vec.M() * vec.M());
    factor = TMath::Sqrt(factor);
    TLorentzVector new_vec(factor * vec.Px(), factor * vec.Py(), factor * vec.Pz(), vec.E() - eloss);
    return new_vec;
}

// ===========================================
// kinematics
// lorentz invariant
// m^2 = (E - Eloss)^2 - (factor*p)^2
// factor*2 = ( (E - Eloss)^2 - m^2 )/p^2
// factor = sqrt( ((E - Eloss)^2 - m2)/(E^2 - m^2) )
//
// tof
// beta = v/c
// E = m/sqrt(1-beta^2)
// v = sqrt(1-(M/E)^2) c