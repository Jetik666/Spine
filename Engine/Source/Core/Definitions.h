#pragma once

#ifdef BUILD_DLL
	#define ENGINE_API __declspec(dllexport)
#else
	#define ENGINE_API __declspec(dllimport)
#endif

constexpr auto MAX_NAME_STRING = 128;
#define HInstance() GetModuleHandle(NULL)
