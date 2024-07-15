cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
project(artemis-crib)

# ROOT 6 installation
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})

# Default installation dir
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(CMAKE_INSTALL_PREFIX
      ${CMAKE_SOURCE_DIR}/build/install
      CACHE PATH "..." FORCE)
endif()

# path definitions
find_package(artemis HINTS ${ARTPATH} REQUIRED)
# we will not support SRIMlib in the future
find_package(SRIMlib HINTS ${SRIMLIB_DIR})
if(SRIMlib_FOUND)
  message(STATUS "Found SRIMlib library")
else()
  message(STATUS "Not Found SRIMlib library")
endif()

find_package(TSrim)
if(TSrim_FOUND)
  message(STATUS "Found TSrim library")
else()
  message(STATUS "Not Found TSrim library")
endif()

# Locate the ROOT package and defines a number of variables
find_package(
  ROOT REQUIRED
  COMPONENTS RIO
             Net
             Physics
             Minuit
             Minuit2
             Geom
             Gui
             Genetic
             RHTTP)
find_package(yaml-cpp REQUIRED HINTS ${ARTEMIS_YAML_CPP_LIB_DIR}/../)

# -fPIC
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# ---Define useful ROOT functions and macros (e.g. ROOT_GENERATE_DICTIONARY)
include(${ROOT_USE_FILE})

add_subdirectory(src-crib)

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/.thisartemis-crib.sh.in"
               "${CMAKE_SOURCE_DIR}/thisartemis-crib.sh" @ONLY)

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/.artemislogon.C.in"
               "${CMAKE_SOURCE_DIR}/artemislogon.C" @ONLY)

# make uninstall
add_custom_target("uninstall" COMMENT "Uninstall installed files")
add_custom_command(
  TARGET "uninstall"
  POST_BUILD
  COMMENT "Uninstall files with install_manifest.txt"
  COMMAND xargs rm -vf < install_manifest.txt || echo Nothing in
          install_manifest.txt to be uninstalled!)
