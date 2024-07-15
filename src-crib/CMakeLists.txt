set(CRIBLIB_NAME crib)

set(CRIBSOURCES
    TF1PPACProcessor.cc
    TTimingChargeAllMappingProcessor.cc
    TTimingDataMappingProcessor.cc
    TBranchCopyProcessor.cc
    TEvtNumProcessor.cc
    TTreePeriodicEventStore.cc
    TModuleData.cc
    TSegmentOutputProcessor.cc
    TScalerMonitorProcessor.cc
    # mux
    mux/TMUXCalibrationProcessor.cc
    mux/TMUXData.cc
    mux/TMUXDataMappingProcessor.cc
    mux/TMUXPositionConverter.cc
    mux/TMUXPositionValidator.cc
    # telescope
    telescope/TTelescopeData.cc
    telescope/TTelescopeProcessor.cc
    # reconst
    #reconst/TTGTIKProcessor.cc
    reconst/TReactionInfo.cc
    # commands
    commands/TCatCmdLoopStart.cc
    commands/TCatCmdLoopStop.cc
    commands/TCmdXfitg.cc
    commands/TCmdXstatus.cc
    commands/TCmdXYblow.cc
    commands/TCmdXblow.cc
    commands/TCatCmdTCutG.cc
    commands/TCmdErase.cc
    commands/TCmdDraw.cc
    # geo
    geo/TUserGeoInitializer.cc
    geo/TDetectorParameter.cc
    geo/TTargetParameter.cc
    # simulation
    #simulation/TEffectiveThickness.cc
    #simulation/TDetectParticleProcessor.cc
    #simulation/TNBodyReactionProcessor.cc
    simulation/TParticleInfo.cc
    simulation/TRandomBeamGenerator.cc
    simulation/TTreeBeamGenerator.cc
    simulation/TSolidAngleProcessor.cc
    #simulation/TTwoBodyScattering.cc
    #simulation/TCRIBPIDProcessor.cc
    # timestamp
    timestamp/TTSData.cc
    timestamp/TTSMappingProcessor.cc
    timestamp/TModuleDecoderTimestamp.cc
)

set(CRIBHEADERS
    TF1PPACProcessor.h
    TTimingChargeAllMappingProcessor.h
    TTimingDataMappingProcessor.h
    TBranchCopyProcessor.h
    TEvtNumProcessor.h
    TTreePeriodicEventStore.h
    TModuleData.h
    TSegmentOutputProcessor.h
    TScalerMonitorProcessor.h
    # mux
    mux/TMUXCalibrationProcessor.h
    mux/TMUXData.h
    mux/TMUXDataMappingProcessor.h
    mux/TMUXPositionConverter.h
    mux/TMUXPositionValidator.h
    # telescope
    telescope/TTelescopeData.h
    telescope/TTelescopeProcessor.h
    # reconst
    #reconst/TTGTIKProcessor.h
    reconst/TReactionInfo.h
    # commands
    commands/TCatCmdLoopStart.h
    commands/TCatCmdLoopStop.h
    commands/TCmdXfitg.h
    commands/TCmdXstatus.h
    commands/TCmdXYblow.h
    commands/TCmdXblow.h
    commands/TCatCmdTCutG.h
    commands/TCmdErase.h
    commands/TCmdDraw.h
    # geo
    geo/TUserGeoInitializer.h
    geo/TDetectorParameter.h
    geo/TTargetParameter.h
    # simulation
    #simulation/TEffectiveThickness.h
    #simulation/TDetectParticleProcessor.h
    #simulation/TNBodyReactionProcessor.h
    simulation/TParticleInfo.h
    simulation/TRandomBeamGenerator.h
    simulation/TTreeBeamGenerator.h
    simulation/TSolidAngleProcessor.h
    #simulation/TTwoBodyScattering.h
    #simulation/TCRIBPIDProcessor.h
    # timestamp
    timestamp/TTSData.h
    timestamp/TTSMappingProcessor.h
    timestamp/TModuleDecoderTimestamp.h
)

if (SRIMlib_FOUND)
  list(APPEND CRIBSOURCES
       reconst/TTGTIKProcessor.cc
       simulation/TDetectParticleProcessor.cc
       simulation/TNBodyReactionProcessor.cc
       simulation/TEffectiveThickness.cc
       simulation/TCRIBPIDProcessor.cc
  )
  list(APPEND CRIBHEADERS
       reconst/TTGTIKProcessor.h
       simulation/TDetectParticleProcessor.h
       simulation/TNBodyReactionProcessor.h
       simulation/TEffectiveThickness.h
       simulation/TCRIBPIDProcessor.h
  )
endif()

add_library(${CRIBLIB_NAME} SHARED ${CRIBSOURCES})

target_include_directories(${CRIBLIB_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(${CRIBLIB_NAME}
    PRIVATE
        ${ROOT_LIBRARIES}
        ${YAML_CPP_LIBRARIES}
        artemis::catcore
        artemis::catloop
        artemis::artcont
        artemis::catcmd
        artemis::catmc
        artemis::artdecoder
        artemis::artridf
        artemis::artrdf
        artemis::arthist
        artemis::artparam
        artemis::artshare
        artemis::CAT
)
# we will not support SRIMlib in the future
if (SRIMlib_FOUND)
  target_link_libraries(${CRIBLIB_NAME} PRIVATE SRIMlib)
endif()

if (TSrim_FOUND)
  target_link_libraries(${CRIBLIB_NAME} PRIVATE Srim)
endif()

ROOT_GENERATE_DICTIONARY(G__${CRIBLIB_NAME}
    ${CRIBHEADERS}
    LINKDEF "artcrib_linkdef.h"
    MODULE ${CRIBLIB_NAME}
)

set_target_properties(
    ${CRIBLIB_NAME}
    PROPERTIES
        PUBLIC_HEADER "${CRIBHEADERS}"
)

install(TARGETS ${CRIBLIB_NAME}
    EXPORT cribTargets
    INCLUDES DESTINATION include
    ARCHIVE DESTINATION lib
    PUBLIC_HEADER DESTINATION include/src-crib
    LIBRARY DESTINATION lib
)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/lib${CRIBLIB_NAME}_rdict.pcm
    DESTINATION lib
)
