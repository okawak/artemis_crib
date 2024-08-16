/**
 * @file    TTGTIKProcessor.cc
 * @brief
 * @author  Kodai Okawa <okawa@cns.s.u-tokyo.ac.jp>
 * @date    2023-08-01 22:35:07
 * @note    last modified: 2024-08-16 10:48:14
 * @details bisection method (not Newton method)
 */

#include "TTGTIKProcessor.h"

#include "../geo/TDetectorParameter.h"
#include <ICharge.h>
#include <ITiming.h>
#include <Mass.h> // TSrim library
#include <TDataObject.h>
#include <constant.h>

#include "TReactionInfo.h"

#include <TClass.h>
#include <TClonesArray.h>
#include <TLorentzVector.h>
#include <TMath.h>
#include <TRandom.h>

using art::TTGTIKProcessor;

ClassImp(art::TTGTIKProcessor);

////////////////////////////////////////////////////////////////////////////////
/// From telescope object and beam (tracking) object, it calculate the
/// reaction position (event reconstruction) using Thick Gas Target method.
/// (Thick Gas Target Inverse Kinematics : TGTIK)
///
/// Need variables in the steering file:
/// - InputCollection: telescope object, inherit from art::TTelescopeData
/// - InputTrackCollection: tracking object, inherit from art::TTrack
/// - OutputCollection: name of output branch, inherit from art::TReactionInfo
/// - InitialBeamEnergy: beam energy in LAB system in MeV unit
/// - TargetName: target gas name for TSrim input
/// - TargetPressure: gas pressure in Torr unit
/// - TargetTemperature: gas emperature
/// - ParticleZArray: [Z1, Z2, Z3, Z4]
/// - ParticleAArray: [A1, A2, A3, A4]
///   - assuming two body reaction (NEED size 4 aray)
///   - [beam, target, fragment, residual]
///   - example: A(a,b)B reaction,
///   - the order is [a, A, b, B]
///   - this is "inverse kinematics", so we assume the detected particle is "B"
///
/// Option:
/// - ExcitedEnergy: if you want to treat excited state transition, input the
/// excited energy (MeV) of Z3 particles
/// - UseCustomFunction: if you need extra treatment, you can add the process.
///   - if it is "true", the custom treatment is on.
///   - this is for 26Si(a, p)29P analysis to treat the excited state effect.

TTGTIKProcessor::TTGTIKProcessor() : fInData(nullptr), fInTrackData(nullptr), fOutData(nullptr) {
    RegisterInputCollection("InputCollection", "telescope data inherit from TTelescopeData", fInputColName,
                            TString("tel"));
    RegisterInputCollection("InputTrackCollection", "tracking data inherit from TTrack", fInputTrackColName,
                            TString("track"));
    RegisterOutputCollection("OutputCollection", "reconstracted reaction information using TGTIK method", fOutputColName,
                             TString("result"));

    IntVec_t init_i_vec;
    RegisterProcessorParameter("InitialBeamEnergy", "beam energy just after the window", fInitialBeamEnergy, 0.0);
    RegisterProcessorParameter("TargetName", "target gas name", fTargetName, TString(""));
    RegisterProcessorParameter("TargetPressure", "target pressure (Torr)", fPressure, 0.0);
    RegisterProcessorParameter("TargetTemperature", "target temperature (K)", fTemperature, 0.0);

    RegisterProcessorParameter("ParticleZArray", "particle atomic numbers of the reaction", fParticleZArray, init_i_vec);
    RegisterProcessorParameter("ParticleAArray", "particle mass numbers of the reaction", fParticleAArray, init_i_vec);

    // custom function
    RegisterProcessorParameter("ExcitedEnergy", "excited energy", fExcitedEnergy, -1.0);
    RegisterProcessorParameter("UseCustomFunction", "custom process", fDoCustom, false);

    RegisterOptionalInputInfo("DetectorParameter", "name of telescope parameter", fDetectorParameterName,
                              TString("prm_detectors"), &fDetectorPrm, "TClonesArray", "art::TDetectorParameter");
    RegisterOptionalInputInfo("TargetParameter", "name of target parameter", fTargetParameterName,
                              TString("prm_targets"), &fTargetPrm, "TClonesArray", "art::TTargetParameter");
}

////////////////////////////////////////////////////////////////////////////////
/// free the memory

TTGTIKProcessor::~TTGTIKProcessor() {
    delete fOutData;
    fOutData = nullptr;
    delete srim;
    srim = nullptr;
}

////////////////////////////////////////////////////////////////////////////////
/// in this process, it prepares some variables

void TTGTIKProcessor::Init(TEventCollection *col) {
    Info("Init", "%s, %s => %s", fInputColName.Data(), fInputTrackColName.Data(), fOutputColName.Data());

    fInData = reinterpret_cast<TClonesArray **>(col->GetObjectRef(fInputColName.Data()));
    if (!fInData) {
        SetStateError(Form("input not found: %s", fInputColName.Data()));
        return;
    }

    fInTrackData = reinterpret_cast<TClonesArray **>(col->GetObjectRef(fInputTrackColName.Data()));
    if (!fInTrackData) {
        SetStateError(Form("input not found: %s", fInputTrackColName.Data()));
        return;
    }

    const TClass *const cl1 = (*fInData)->GetClass();
    const TClass *const cl2 = (*fInTrackData)->GetClass();
    if (!(cl1->InheritsFrom(art::TTelescopeData::Class()))) {
        SetStateError(Form("%s need to inherit from TTelescopeData", fInputColName.Data()));
        return;
    }
    if (!(cl2->InheritsFrom(art::TTrack::Class()))) {
        SetStateError(Form("%s need to inherit from TTrack", fInputTrackColName.Data()));
        return;
    }

    if (!fDetectorPrm) {
        SetStateError(Form("input not found: %s", fDetectorParameterName.Data()));
        return;
    }

    if (!fTargetPrm) {
        SetStateError(Form("input not found: %s", fTargetParameterName.Data()));
        return;
    }

    if (fParticleZArray.size() != 4 || fParticleAArray.size() != 4) {
        SetStateError("Particle array size should be 4 in the steering file");
        return;
    }

    // unit = mass (MeV)
    M1 = amdc::Mass(fParticleZArray[0], fParticleAArray[0]) * amdc::amu;
    M2 = amdc::Mass(fParticleZArray[1], fParticleAArray[1]) * amdc::amu;
    Double_t M3_default = amdc::Mass(fParticleZArray[2], fParticleAArray[2]) * amdc::amu;
    M4 = amdc::Mass(fParticleZArray[3], fParticleAArray[3]) * amdc::amu;

    if (!fDoCustom && fExcitedEnergy > 0)
        M3 = M3_default + fExcitedEnergy;
    else
        M3 = M3_default;

    Info("Init", "reconstract the reaction: %d%s + %d%s -> %d%s + %d%s <- detect",
         fParticleAArray[0], amdc::GetEl(fParticleZArray[0]).c_str(),
         fParticleAArray[1], amdc::GetEl(fParticleZArray[1]).c_str(),
         fParticleAArray[2], amdc::GetEl(fParticleZArray[2]).c_str(),
         fParticleAArray[3], amdc::GetEl(fParticleZArray[3]).c_str());

    Info("Init", "\tQ-value: %lf MeV", (M1 + M2) - (M3 + M4));

    // TSrim object
    const char *tsrim_path = std::getenv("TSRIM_DATA_HOME");
    if (!tsrim_path) {
        SetStateError("TSRIM_DATA_HOME environment variable is not defined");
        return;
    }
    srim = new TSrim();
    srim->AddElement("srim", 16, Form("%s/%s/range_fit_pol16_%s.txt", tsrim_path, fTargetName.Data(), fTargetName.Data()));

    // prepare output collection
    fOutData = new TClonesArray("art::TReactionInfo");
    fOutData->SetName(fOutputColName);
    col->Add(fOutputColName, fOutData, fOutputIsTransparent);

    gRandom->SetSeed(time(nullptr));
}

////////////////////////////////////////////////////////////////////////////////
/// Main process

void TTGTIKProcessor::Process() {
    fOutData->Clear("C");

    Int_t nData = (*fInData)->GetEntriesFast();
    if (nData == 0)
        return;
    else if (nData != 1) {
        std::cerr << "warning: the input " << fInputColName << " entry number is not 1, but " << nData << std::endl;
    }

    Int_t nTrackData = (*fInTrackData)->GetEntriesFast();
    if (nTrackData == 0)
        return;
    if (nTrackData != 1) {
        std::cerr << "warning: the input " << fInputTrackColName << " entry number is not 1, but " << nTrackData
                  << std::endl;
    }

    const TDataObject *const inData = static_cast<TDataObject *>((*fInData)->At(0));
    const TTelescopeData *const Data = dynamic_cast<const TTelescopeData *>(inData);
    const TDataObject *const inTrackData = static_cast<TDataObject *>((*fInTrackData)->At(0));
    const TTrack *const TrackData = dynamic_cast<const TTrack *>(inTrackData);

    // excited energy process
    if (fDoCustom)
        M3 += GetCustomExcitedEnergy();

    Double_t reac_z = GetReactionPosition(TrackData, Data);

    if (!IsValid(reac_z))
        return;

    TReactionInfo *outData = static_cast<TReactionInfo *>(fOutData->ConstructedAt(0));
    outData->SetID(0);
    outData->SetXYZ(TrackData->GetX(reac_z), TrackData->GetY(reac_z), reac_z);
    outData->SetEnergy(GetEcmFromBeam(reac_z, TrackData));
}

////////////////////////////////////////////////////////////////////////////////
/// Using bisection method (if you want Newton method is also available,
/// but in default, we use bisection method)

Double_t TTGTIKProcessor::GetReactionPosition(const TTrack *track, const TTelescopeData *data) {
    // return newton(track, data);
    return bisection(track, data);
}

////////////////////////////////////////////////////////////////////////////////
/// Currently not available, return kInvalidD.

Double_t TTGTIKProcessor::newton(const TTrack *, const TTelescopeData *) {
    return kInvalidD;
}

////////////////////////////////////////////////////////////////////////////////
/// Normal bisection method.

Double_t TTGTIKProcessor::bisection(const TTrack *track, const TTelescopeData *data) {
    Double_t flow = TargetFunction(kInitialMin, track, data);
    Double_t fhigh = TargetFunction(kInitialMax, track, data);
    Double_t low = kInitialMin;
    Double_t high = kInitialMax;
    Double_t ftmp = TargetFunction(kInitialMin, track, data);
    Int_t sign = 1;
    Bool_t isFirst = true;

    // search initial z position (rough bisection)
    for (Int_t i = 0; i < 10; i++) {
        Double_t tmpz = kInitialMin + (Double_t)i * (kInitialMax - kInitialMin);
        Double_t f = TargetFunction(tmpz, track, data);
        if (!IsValid(f))
            continue;

        if (isFirst) {
            sign = f >= 0 ? 1 : -1;
            isFirst = false;
        }

        if (sign == (f >= 0 ? 1 : -1)) {
            ftmp = f;
        } else {
            flow = ftmp;
            fhigh = f;
            low = kInitialMin + (Double_t)(i - 1) * (kInitialMax - kInitialMin);
            high = tmpz;
            break;
        }
    }
    if (!IsValid(flow) || !IsValid(fhigh)) {
        std::cerr << "[Warning in bisect] f(low) or f(high) is invalid" << std::endl;
        return kInvalidD;
    }
    if (flow * fhigh > 0) {
        std::cerr << "[Warning in bisect] f(low) * f(high) > 0"
                  << ", f(low): " << flow << ", f(high): " << fhigh
                  << ", energy = " << data->GetEtotal()
                  << std::endl;
        return kInvalidD;
    }

    // start standard bisection method
    Double_t left = low;
    Double_t right = high;

    Double_t middle = 0.0;
    Int_t itr = 0;
    while (TMath::Abs(right - left) > kEpsilon) {
        middle = (left + right) / 2.0;

        Double_t fleft = TargetFunction(left, track, data);
        Double_t fmiddle = TargetFunction(middle, track, data);
        if (!IsValid(fleft) || !IsValid(fmiddle))
            return kInvalidD;

        if (fleft * fmiddle < 0) {
            right = middle;
        } else {
            left = middle;
        }

        itr++;
        if (itr == kMaxIteration) {
            std::cerr << "[bisection] not converge!" << std::endl;
            return kInvalidD;
        }
    }
    return middle;
}

////////////////////////////////////////////////////////////////////////////////
/// From <b>assuming Z position (reaction position)</b>,
/// calculate the Ecm from two direction.
/// - Ecm(beam): Ecm calculate from beam information
/// - Ecm(data): Ecm calculate from detected particle information
/// The target function is Ecm(beam) - Ecm(data).
/// When the value become 0, the assumed Z is reconstructed position.
/// (x, y, z) position will be calculated from tracking object.

Double_t TTGTIKProcessor::TargetFunction(Double_t z, const TTrack *track, const TTelescopeData *data) {
    Double_t Ecm_beam = GetEcmFromBeam(z, track);
    Double_t Ecm_detect = GetEcmFromDetectParticle(z, track, data);
    if (!IsValid(Ecm_beam) || !IsValid(Ecm_detect)) {
        return kInvalidD;
    }
    return Ecm_beam - Ecm_detect;
}

////////////////////////////////////////////////////////////////////////////////
/// From <b>assuming Z position (reaction position)</b>,
/// calculate the Ecm from beam kinematics and energy loss.
/// The beam is Z1 particle of [Z1, Z2, Z3, Z4].

Double_t TTGTIKProcessor::GetEcmFromBeam(Double_t z, const TTrack *track) {
    // if sign > 0 enewz, sign < 0, eoldz (thickness is negative)
    Int_t sign = z > 0 ? 1 : -1;
    TVector3 beam_flight(track->GetX(z) - track->GetX(0), track->GetY(z) - track->GetY(0), z);
    Double_t energy = srim->EnergyNew(fParticleZArray[0], fParticleAArray[0],
                                      fInitialBeamEnergy, std::string(fTargetName.Data()),
                                      sign * beam_flight.Mag(), fPressure, fTemperature);
    if (energy < 0.01)
        return 0.0;

    Double_t beta = TMath::Sqrt(1.0 - TMath::Power(M1 / (M1 + energy), 2));
    Double_t ang[2] = {track->GetA(), track->GetB()};
    Double_t norm = TMath::Sqrt(TMath::Tan(ang[0]) * TMath::Tan(ang[0]) + TMath::Tan(ang[1]) * TMath::Tan(ang[1]) + 1.0);
    Double_t beta_array[3] = {beta * TMath::Tan(ang[0]) / norm, beta * TMath::Tan(ang[1]) / norm, beta * 1.0 / norm};

    TLorentzVector beam(0., 0., 0., M1);
    beam.Boost(beta_array[0], beta_array[1], beta_array[2]);

    TLorentzVector target(0., 0., 0., M2);

    TLorentzVector cm_vec = beam + target;
    TVector3 beta_cm = cm_vec.BoostVector();
    beam.Boost(-beta_cm);
    target.Boost(-beta_cm);

    return (beam.E() - beam.M()) + (target.E() - target.M());
}

////////////////////////////////////////////////////////////////////////////////
/// From <b>assuming Z position (reaction position)</b>,
/// calculate the Ecm from detected particle information.
/// Currently it uses classsic kinematics.

Double_t TTGTIKProcessor::GetEcmFromDetectParticle(Double_t z, const TTrack *track, const TTelescopeData *data) {
    Int_t tel_id = data->GetTelID();
    const TParameterObject *const inPrm = static_cast<TParameterObject *>((*fDetectorPrm)->At(tel_id - 1));
    const TDetectorParameter *Prm = dynamic_cast<const TDetectorParameter *>(inPrm);
    if (!Prm) {
        std::cerr << "parameter is not found" << std::endl;
        return kInvalidD;
    }

    Int_t stripNum[2] = {Prm->GetStripNum(0), Prm->GetStripNum(1)};
    Int_t stripID[2] = {data->GetXID(), data->GetYID()};
    Double_t stripSize[2] = {Prm->GetSize(0) / (Double_t)stripNum[0], Prm->GetSize(1) / (Double_t)stripNum[1]};

    Double_t det_x, det_y;
    if (stripID[0] >= 0 && stripID[0] < stripNum[0]) {
        det_x = -Prm->GetSize(0) / 2.0 + stripSize[0] * ((Double_t)stripID[0] + gRandom->Uniform());
    } else {
        det_x = -Prm->GetSize(0) / 2.0 + Prm->GetSize(0) * gRandom->Uniform();
    }

    if (stripID[1] >= 0 && stripID[1] < stripNum[1]) {
        det_y = -Prm->GetSize(1) / 2.0 + stripSize[1] * ((Double_t)stripID[1] + gRandom->Uniform());
    } else {
        det_y = -Prm->GetSize(1) / 2.0 + Prm->GetSize(1) * gRandom->Uniform();
    }

    TVector3 detect_position(det_x, det_y, Prm->GetDistance());
    detect_position.RotateY(Prm->GetAngle()); // rad
    detect_position += TVector3(Prm->GetCenterRotPos(0), Prm->GetCenterRotPos(1), Prm->GetCenterRotPos(2));

    TVector3 reaction_position(track->GetX(z), track->GetY(z), z);
    TVector3 track_direction(track->GetX(1.) - track->GetX(0.), track->GetY(1.) - track->GetY(0.), 1.0);

    Double_t theta = track_direction.Angle(detect_position - reaction_position); // LAB, rad
    Double_t energy = srim->EnergyNew(fParticleZArray[3], fParticleAArray[3],    // id = 3 particle
                                      data->GetEtotal(), std::string(fTargetName.Data()),
                                      -(detect_position - reaction_position).Mag(),
                                      fPressure, fTemperature);

    // kinematics (using bisection method) detected particle id=3
    // return GetEcm_kinematics(energy, theta, 0.01, 1.0e+4);

    // classic kinematics
    return GetEcm_classic_kinematics(energy, theta);
}

////////////////////////////////////////////////////////////////////////////////
/// From detected energy and angle, calculate kinematics using relativity.
/// This is used in GetEcmFromDetectPartice method.
/// currently not avalable.

Double_t TTGTIKProcessor::GetEcm_kinematics(Double_t, Double_t, Double_t, Double_t) {
    return kInvalidD;
}

////////////////////////////////////////////////////////////////////////////////
/// From detected energy and angle, calculate kinematics using classic.
/// This is used in GetEcmFromDetectPartice method.
/// Please refer from okawa's master thesis for an detail.

Double_t TTGTIKProcessor::GetEcm_classic_kinematics(Double_t energy, Double_t theta) {
    Double_t alpha = (M2 * (M1 + M2)) / (2.0 * M1);
    Double_t beta = (M4 * (M3 + M4)) / (2.0 * M3);
    Double_t qvalue = (M1 + M2) - (M3 + M4);

    Double_t v4 = TMath::Sqrt(2.0 * energy / M4);
    Double_t b = (beta * v4 * TMath::Cos(theta)) / (alpha - beta);
    Double_t c = (qvalue - beta * v4 * v4) / (alpha - beta);
    Double_t D = b * b - c;
    if (D < 0) {
        if (TMath::Abs(D) < 1.0e-5) {
            D = 0.0;
        } else {
            std::cerr << "b^2 - c = " << D << " < 0, det_energy : " << energy << ", theta : " << theta << std::endl;
            return kInvalidD;
        }
    }

    Double_t vcm = -b + TMath::Sqrt(D);
    if (vcm < 0) {
        std::cerr << "vcm < 0! : vcm = " << -b << " + " << TMath::Sqrt(D) << ", det_energy : " << energy
                  << ", theta : " << theta << std::endl;
        return kInvalidD;
    }

    return alpha * vcm * vcm;
}

////////////////////////////////////////////////////////////////////////////////
/// assuming Ecm and detected energy, calculate LAB angle.

Double_t TTGTIKProcessor::GetLabAngle(Double_t energy, Double_t energy_cm) {
    Double_t energy_L = energy + M4;
    Double_t energy_cm_all = energy_cm + M1 + M2;
    Double_t energy_4cm =
        (energy_cm_all - (M3 * M3 - M4 * M4) / energy_cm_all) / 2.0;
    Double_t energy1 = (energy_cm * energy_cm + 2.0 * energy_cm * (M1 + M2) +
                        2.0 * M1 * M2) /
                       (2.0 * M2);
    Double_t beta = TMath::Sqrt(energy1 * energy1 - M1 * M1) / (energy1 + M2);

    Double_t arg = (energy_L - energy_4cm * TMath::Sqrt(1.0 - beta * beta)) /
                   (beta * TMath::Sqrt(energy_L * energy_L - M4 * M4));

    return TMath::ACos(arg);
}

////////////////////////////////////////////////////////////////////////////////
/// This is used for 26Si(a, p)29P analysis.
/// from TALYS simulation data, the ratio of excited energy
/// are calculated and from the saved custom ROOT file,
/// assign the excited energy randomly.
///
/// You can modify as you like.

Double_t TTGTIKProcessor::GetCustomExcitedEnergy() {
    return 0.0;
}
