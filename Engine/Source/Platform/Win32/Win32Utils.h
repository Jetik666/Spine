#pragma once
#include "Engine.h"

namespace Win32
{
	namespace Utils
	{
		bool ENGINE_API AddBitmap(const wchar_t* szFileName, HDC hWinDC, int x = 0, int y = 0);
	}
}