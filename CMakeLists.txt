cmake_minimum_required(VERSION 3.5.1 FATAL_ERROR)
set(CMAKE_LEGACY_CYGWIN_WIN32 0)

project("Rumble3D")

enable_testing()


if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR
   "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	set(warnings "-Wall -Wextra -Werror -Wno-error=sign-compare -Wno-error=unused-parameter -Wno-error=unused-variable -Wno-error=type-limits -std=c++14")
# elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
# 	set(warnings "/W4 /WX /EHsc")
endif()
if(NOT CONFIGURED_ONCE)
	set(CMAKE_C_FLAGS "${warnings}" CACHE STRING "Flags used by the compiler during all build types." FORCE)
	set(CMAKE_CXX_FLAGS "${warnings}" CACHE STRING "Flags used by the compiler during all build types." FORCE)
endif()



add_subdirectory(Rumble3D)
add_subdirectory(Example)




set(CONFIGURED_ONCE TRUE CACHE INTERNAL "A flag showing that CMake has configured at least once.")
