#pragma once
#include "Engine.h"

constexpr int DEFAULTWIDTH = 600;
constexpr int DEFAULTHEIGHT = 600;

namespace Win32 
{
	enum WindowType : DWORD
	{
		STATIC		= WS_OVERLAPPED,
		RESIZABLE	= WS_SIZEBOX,
		POPUP		= WS_POPUP,
	};

	namespace Utils 
	{
		bool AddBitmap(const wchar_t* szFileName, HDC hWinDC, int x = 0, int y = 0) noexcept;

        /// Sets and clears style flags for a particular window.
        inline void ModifyWindowStyle(HWND hWnd, DWORD flagsToDisable, DWORD flagsToEnable)
        {
            DWORD style = GetWindowLong(hWnd, GWL_STYLE);
            SetWindowLong(hWnd, GWL_STYLE, (style & ~flagsToDisable) | flagsToEnable);
        }

        /// Sets and clears extended style flags for a particular window.
        inline void ModifyWindowExStyle(HWND hWnd, DWORD flagsToDisable, DWORD flagsToEnable)
        {
            DWORD exStyle = GetWindowLong(hWnd, GWL_EXSTYLE);
            SetWindowLong(hWnd, GWL_EXSTYLE, (exStyle & ~flagsToDisable) | flagsToEnable);
        }

        inline bool HasStyle(HWND hwnd, DWORD style)
        {
            DWORD dwStyle = (DWORD)GetWindowLong(hwnd, GWL_STYLE);
            if ((dwStyle & style) != 0) return TRUE;
            return FALSE;
        }

        /// Sets and clears style flags for a particular window.
        inline void ModifyClassStyle(HWND hWnd, DWORD flagsToDisable, DWORD flagsToEnable)
        {
            DWORD style = GetWindowLong(hWnd, GCL_STYLE);
            SetClassLong(hWnd, GCL_STYLE, (style & ~flagsToDisable) | flagsToEnable);
        }

        inline bool IsWindowFullscreen(HWND hWnd)
        {
            WINDOWPLACEMENT placement{};
            GetWindowPlacement(hWnd, &placement);

            if (placement.showCmd == SW_MAXIMIZE)
            {
                return TRUE;
            }
            return FALSE;
        }

        inline void MaximizeWindow(HWND hwnd)
        {
            WINDOWPLACEMENT wPos{};
            GetWindowPlacement(hwnd, &wPos);
            if (wPos.showCmd == SW_MAXIMIZE)
            {
                ShowWindow(hwnd, SW_NORMAL);
            }
            else
            {
                ShowWindow(hwnd, SW_MAXIMIZE);
            }
        }
	}
}