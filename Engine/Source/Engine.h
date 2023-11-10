#pragma once

#ifdef WIN32
#include <Windows.h>
#endif // WIN32

#ifdef BUILD_DLL
	#define ENGINE_API __declspec(dllexport)
#else
	#define ENGINE_API __declspec(dllimport)
#endif

#include "Common/Logger/Logger.h"
