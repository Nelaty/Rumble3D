cmake_minimum_required(VERSION 3.11)
project(rumble3d)
set(PROJECT_SHORT_NAME "r3")

set(CMAKE_CXX_STANDARD 20)

set(RUMBLE3D_ENABLE_TESTS 1)
set(RUMBLE3D_BUILD_SAMPLES 1)

# Configure output paths
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/)

set(RUMBLE3D_TEST_NAME Test)

# Configure installation paths
set(RUMBLE3D_INCLUDE_DIRECTORY include/)
set(RUMBLE3D_LIBRARY_INSTALL_PATH lib)
set(RUMBLE3D_INCLUDE_INSTALL_PATH include/)

# Projects
include_directories(include)

add_subdirectory(src)

if(${RUMBLE3D_ENABLE_TESTS})
enable_testing()
add_subdirectory(Test)

add_test(NAME ${RUMBLE3D_TEST_NAME}
        COMMAND ${RUMBLE3D_TEST_NAME} --config $<CONFIGURATION>
        --exe $<TARGET_FILE:${RUMBLE3D_TEST_NAME}>)
endif()

if(${RUMBLE3D_BUILD_SAMPLES})
#include_directories(example)
endif()

# Install library and include files
install(TARGETS ${PROJECT_NAME}
        LIBRARY	DESTINATION ${RUMBLE3D_LIBRARY_INSTALL_PATH})

install(DIRECTORY ${RUMBLE3D_INCLUDE_DIRECTORY}
        DESTINATION ${RUMBLE3D_INCLUDE_INSTALL_PATH})