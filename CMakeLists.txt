cmake_minimum_required(VERSION 3.14)
project(Rumble3d)

set(CMAKE_CXX_STANDARD 20)

# Setup library options
option(RUMBLE3D_ENABLE_TESTS "Build and run unittests" ON)
option(RUMBLE3D_BUILD_SAMPLES "Build the examples" ON)
option(RUMBLE3D_USE_STANDALONE_DEPS "Use findpackage for thirdparty libraries instead of submodules" OFF)
option(RUMBLE3D_USE_DOUBLE_PRECISION "Use double precision for physics simulation" OFF)

# Configure cmake
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/)

# Configure library
include(r3d_configure)
r3d_configure_version(1 0 0 "" "")
message("Building '${PROJECT_NAME}' library v${R3D_VERSION}")

# Third party libraries
if(NOT RUMBLE3D_USE_STANDALONE_DEPS)
    add_subdirectory(ThirdParty)
else()
    find_package(glm REQUIRED)
endif()

# Library
add_subdirectory(Rumble3D)

# Tests
if(RUMBLE3D_ENABLE_TESTS)
    enable_testing()
    add_custom_target(ctest ${PROJECT_NAME}_unittests "-v")

    add_subdirectory(Test)
endif()

# Examples
if(RUMBLE3D_BUILD_SAMPLES)
    include_directories(Example)
endif()
