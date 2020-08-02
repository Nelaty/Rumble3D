cmake_minimum_required(VERSION 3.11)
project(rumble3d)

set(RUMBLE3D_ENABLE_TESTS 1)
set(RUMBLE3D_BUILD_SAMPLES 1)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/)

# Projects
include_directories(include)

add_subdirectory(src)

if(${RUMBLE3D_ENABLE_TESTS})
#include_directories(test)
endif()

if(${RUMBLE3D_BUILD_SAMPLES})
#include_directories(example)
endif()


