#pragma once

// Check if platform is windows
#if !defined(_WIN32) && (defined(__WIN32__) || defined(WIN32) || defined(__MINGW32__))
#define _WIN32
#endif

// Dllimport, Dllexport
#if defined(_WIN32) && defined(_GLFW_BUILD_DLL)
    #define R3D_DECLSPEC __declspec(dllexport)
#elif defined(_WIN32) && defined(GLFW_DLL)
    #define R3D_DECLSPEC __declspec(dllimport)
#elif defined(__GNUC__) && defined(_GLFW_BUILD_DLL)
    #define R3D_DECLSPEC __attribute__((visibility("default")))
#else
    #define R3D_DECLSPEC
#endif
