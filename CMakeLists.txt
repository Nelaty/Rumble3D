cmake_minimum_required(VERSION 3.14)
project(Rumble3d)

set(CMAKE_CXX_STANDARD 20)

# Configure library version
option(RUMBLE3D_ENABLE_TESTS "Build and run unittests" ON)
option(RUMBLE3D_BUILD_SAMPLES "Build the examples" ON)
option(RUMBLE3D_USE_STANDALONE_DEPS "Use findpackage for thirdparty libraries instead of submodules" OFF)

set(R3D_VERSION_MAJOR "1")
set(R3D_VERSION_MINOR "0")
set(R3D_VERSION_PATCH "0")
set(R3D_VERSION "${R3D_VERSION_MAJOR}.${R3D_VERSION_MINOR}.${R3D_VERSION_PATCH}")

# Configure library constants
set(R3D_CONFIG_USE_DOUBLE_PRECISION "0")

set(R3D_CONFIGURATION_PATH "${CMAKE_SOURCE_DIR}/Rumble3D/include/R3D/Common/Config.h")
configure_file("${R3D_CONFIGURATION_PATH}.in"
        "${R3D_CONFIGURATION_PATH}"
        @ONLY)

# Third party libraries
if(NOT RUMBLE3D_USE_STANDALONE_DEPS)
    add_subdirectory(ThirdParty)
else()
    find_package(glm REQUIRED)
endif()

# Projects
add_subdirectory(Rumble3D)

if(RUMBLE3D_ENABLE_TESTS)
    enable_testing()
    add_custom_target(ctest ${PROJECT_NAME}_unittests "-v")

    add_subdirectory(Test)
endif()

if(RUMBLE3D_BUILD_SAMPLES)
    include_directories(Example)
endif()
