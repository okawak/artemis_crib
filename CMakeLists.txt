cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
project(artemis-crib)

# ROOT 6 installation
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})

# Default installation dir
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/build/install CACHE PATH "..." FORCE)
endif()

# path definitions
find_package(artemis HINTS ${ARTPATH} REQUIRED)
find_package(SRIMlib HINTS ${SRIMLIB_DIR} REQUIRED)

#---Locate the ROOT package and defines a number of variables (e.g. ROOT_INCLUDE_DIRS)
find_package(ROOT REQUIRED COMPONENTS RIO Net Physics Minuit Minuit2 Geom Gui Genetic RHTTP)
find_package(yaml-cpp REQUIRED HINTS ${ARTEMIS_YAML_CPP_LIB_DIR}/../)

#-fPIC
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


#---Define useful ROOT functions and macros (e.g. ROOT_GENERATE_DICTIONARY)
include(${ROOT_USE_FILE})

#link_directories(${ARTEMIS_GET_LIB_DIR})

add_subdirectory(src-crib)

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/.thisartemis-crib.sh.in"
    "${CMAKE_SOURCE_DIR}/thisartemis-crib.sh"
    @ONLY
)

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/.artemislogon.C.in"
    "${CMAKE_SOURCE_DIR}/artemislogon.C"
    @ONLY
)

# make uninstall
add_custom_target("uninstall" COMMENT "Uninstall installed files")
add_custom_command(
    TARGET "uninstall"
    POST_BUILD
    COMMENT "Uninstall files with install_manifest.txt"
    COMMAND xargs rm -vf < install_manifest.txt || echo Nothing in
            install_manifest.txt to be uninstalled!
)

add_custom_target(copy-compile-commands ALL
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_BINARY_DIR}/compile_commands.json
    ${CMAKE_SOURCE_DIR}/compile_commands.json
  DEPENDS ${CMAKE_BINARY_DIR}/compile_commands.json
  COMMENT "Copying compile_commands.json to root directory"
)
