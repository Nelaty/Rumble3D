#pragma once
#include "Config.h"

namespace rum
{
	#ifdef R3D_DLL_EXPORT
	#define R3D_DECLSPEC __declspec(dllexport)
	#elif R3D_DLL_IMPORT
	#define R3D_DECLSPEC __declspec(dllimport)
	#endif

	#ifndef R3D_DECLSPEC
	#define R3D_DECLSPEC
	#endif
}