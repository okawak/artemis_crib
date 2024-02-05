// K.Okawa created <okawa@cns.s.u-tokyo.ac.jp>
#ifndef LINKDEF_CRIB_H
#define LINKDEF_CRIB_H

#ifdef __CINT__

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;

// segment and category
// main
#pragma link C++ class art::TF1PPACProcessor;
#pragma link C++ class art::TTimingChargeAllMappingProcessor;
#pragma link C++ class art::TTimingDataMappingProcessor;
#pragma link C++ class art::TBranchCopyProcessor;
#pragma link C++ class art::TEvtNumProcessor;
#pragma link C++ class art::TTreePeriodicEventStore;
#pragma link C++ class art::TModuleData + ;
#pragma link C++ class art::TSegmentOutputProcessor;
#pragma link C++ class art::TScalerMonitorProcessor;
// MUX
#pragma link C++ class art::TMUXData + ;
#pragma link C++ class art::TMUXDataMappingProcessor;
#pragma link C++ class art::TMUXPositionConverter;
#pragma link C++ class art::TMUXPositionValidator;
#pragma link C++ class art::TMUXCalibrationProcessor;
// telescope
#pragma link C++ class art::TTelescopeData + ;
#pragma link C++ class art::TTelescopeProcessor;
// reconst
#pragma link C++ class art::TTGTIKProcessor;
#pragma link C++ class art::TReactionInfo + ;
//  commands
#pragma link C++ class TCatCmdLoopStart;
#pragma link C++ class TCatCmdLoopStop;
#pragma link C++ class art::TCmdXfitg;
#pragma link C++ class art::TCmdXstatus;
#pragma link C++ class art::TCmdXYblow;
#pragma link C++ class art::TCmdXblow;
#pragma link C++ class TCatCmdTCutG;
#pragma link C++ class art::TCmdErase;
#pragma link C++ class art::TCmdDraw;
// geo
#pragma link C++ class art::TUserGeoInitializer;
#pragma link C++ class art::TDetectorParameter + ;
#pragma link C++ class art::TTargetParameter + ;
// simulation
#pragma link C++ class art::TEffectiveThickness;
#pragma link C++ class art::TDetectParticleProcessor;
#pragma link C++ class art::TNBodyReactionProcessor;
#pragma link C++ class art::TParticleInfo + ;
#pragma link C++ class art::TRandomBeamGenerator;
#pragma link C++ class art::TTreeBeamGenerator;
#pragma link C++ class art::TSolidAngleProcessor;
// #pragma link C++ class art::TTwoBodyScattering;
#pragma link C++ class art::TCRIBPIDProcessor;
// timestamp
#pragma link C++ class art::TTSData + ;
#pragma link C++ class art::TTSMappingProcessor;
#pragma link C++ class art::TModuleDecoderTimestamp;
#endif // __CINT__

#endif // LINKDEF_CRIB_H
