#pragma once

// Dllimport, Dllexport
#if defined(_WIN32) && defined(_GLFW_BUILD_DLL)
    #define R3D_EXPORT __declspec(dllexport)
#elif defined(_WIN32) && defined(GLFW_DLL)
    #define R3D_EXPORT __declspec(dllimport)
#elif defined(__GNUC__) && defined(_GLFW_BUILD_DLL)
    #define R3D_EXPORT __attribute__((visibility("default")))
#else
    #define R3D_EXPORT
#endif
