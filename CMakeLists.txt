cmake_minimum_required(VERSION 3.11)

include("cmake/HunterGate.cmake")
HunterGate(
        URL "https://github.com/cpp-pm/hunter/archive/v0.23.296.tar.gz"
        SHA1 "232f5022ee1d45955a7e8d3e1720f31bac1bb534"
)

project(Rumble3d)
set(PROJECT_SHORT_NAME "r3")

set(CMAKE_CXX_STANDARD 20)

#################################################
# User configuration
#################################################

# Configuration values
set(RUMBLE3D_ENABLE_TESTS 1)
set(RUMBLE3D_BUILD_SAMPLES 1)

set(R3D_VERSION_MAJOR "1")
set(R3D_VERSION_MINOR "0")
set(R3D_VERSION_PATCH "0")
set(R3D_VERSION "${R3D_VERSION_MAJOR}.${R3D_VERSION_MINOR}.${R3D_VERSION_PATCH}")

set(R3D_CONFIG_USE_DOUBLE_PRECISION "0")

# Configuration file setup
set(R3D_CONFIGURATION_PATH "${CMAKE_SOURCE_DIR}/Rumble3D/include/R3D/Common/Config.h")
configure_file("${R3D_CONFIGURATION_PATH}.in"
        "${R3D_CONFIGURATION_PATH}"
        @ONLY)

#################################################
# General configuration
#################################################

# Configure output paths
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set(RUMBLE3D_LIB_NAME ${PROJECT_NAME})
set(RUMBLE3D_TEST_NAME Test)

# Configure installation paths
set(RUMBLE3D_INCLUDE_DIRECTORY Rumble3D/include/)
set(RUMBLE3D_LIBRARY_INSTALL_PATH lib)
set(RUMBLE3D_INCLUDE_INSTALL_PATH include/)

# Configure build types #TODO:
#SET(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Configs" FORCE)
#IF(DEFINED CMAKE_BUILD_TYPE AND CMAKE_VERSION VERSION_GREATER "2.8")
#    SET_PROPERTY(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS ${CMAKE_CONFIGURATION_TYPES})
#ENDIF()
#SET(CMAKE_DEBUG_POSTFIX "_d")

#################################################
# Dependencies of library
#################################################
hunter_add_package(glm)
find_package(glm REQUIRED)

set(R3D_DEP_LIBRARIES glm)


#################################################
# Dependencies (incl. library itself)
#################################################
set(R3D_LIBRARIES ${R3D_DEP_LIBRARIES} ${PROJECT_NAME})

include_directories(${RUMBLE3D_INCLUDE_DIRECTORY})

#################################################
# Build
#################################################

# Projects
add_subdirectory(Rumble3D)

if(${RUMBLE3D_ENABLE_TESTS})
    enable_testing()
    add_subdirectory(Test)

    add_test(NAME ${RUMBLE3D_TEST_NAME}
            COMMAND ${RUMBLE3D_TEST_NAME} --config $<CONFIGURATION>
            --exe $<TARGET_FILE:${RUMBLE3D_TEST_NAME}>)
endif()

if(${RUMBLE3D_BUILD_SAMPLES})
include_directories(example)
endif()

#################################################
# Installation
#################################################
# Install library and include files

if(${CMAKE_CXX_COMPILER_ID} STREQUAL MSVCC)
    # TODO
else()
    install(TARGETS ${PROJECT_NAME}
            LIBRARY	DESTINATION ${RUMBLE3D_LIBRARY_INSTALL_PATH})

    install(DIRECTORY ${RUMBLE3D_INCLUDE_DIRECTORY}
            DESTINATION ${RUMBLE3D_INCLUDE_INSTALL_PATH})
endif()