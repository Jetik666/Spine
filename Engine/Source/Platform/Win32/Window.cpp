#include "Engine.h"
#include "Window.h"

constexpr DWORD DCX_USESTYLE = 0x00010000;

namespace Win32 
{
	Window::Window(const wchar_t* title, HICON hIcon, WindowType type) noexcept
		: Win32::SubObject(title, title, hIcon)
		, m_Type(type)
	{
		Size(DEFAULTWIDTH, DEFAULTHEIGHT);
	}

	Window::~Window() noexcept 
	{
		UnregisterClass(m_Class, HInstance());
	}

	void Window::Initialize() noexcept 
	{
		RECT desktop;
		const HWND hDesktop = GetDesktopWindow();
		GetWindowRect(hDesktop, &desktop);

		RECT R = { 0, 0, Size().cx, Size().cy};
		AdjustWindowRect(&R, m_Type, false);
		int width = R.right - R.left;
		int height = R.bottom - R.top;

		m_Handle = CreateWindow(m_Class, m_Title, m_Type, 
			((desktop.right / 2) - (Size().cx / 2)), ((desktop.bottom / 2) - (Size().cy / 2)),
			Size().cx, Size().cy, 0, 0, HInstance(), (void*)this);
		if (!m_Handle) 
		{
			DWORD error = GetLastError();
			std::wstring errorMessage = L"Failed to create window! Error code: " + std::to_wstring(error);
			MessageBox(0, errorMessage.c_str(), 0, 0);
			PostQuitMessage(0);
			return;
		}

		ShowWindow(m_Handle, SW_SHOW);
		UpdateWindow(m_Handle);
	}

	LRESULT Window::MessageHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) noexcept
	{
		switch (message)
		{
			case WM_NCCREATE:
			{
				OnNonClientCreate();
				return TRUE;
			}
			case WM_NCACTIVATE:
			{
				OnNonClientActivate(LOWORD(wParam) != WA_INACTIVE);
				return TRUE;
			}
			case WM_NCPAINT:
			{
				OnNonClientPaint((HRGN)wParam);
				return FALSE;
			}
			case WM_TIMER:
			{
				RedrawWindow();
				break;
			}
		}

		return SubObject::MessageHandler(hWnd, message, wParam, lParam);
	}

	void Window::OnNonClientCreate() const noexcept
	{
		SetTimer(Handle(), 1, 100, NULL);
		SetWindowTheme(Handle(), L"", L"");

		Utils::ModifyClassStyle(Handle(), 0, CS_DROPSHADOW);
	}

	void Window::OnNonClientActivate(bool active)
	{
		Active(active);
	}

	void Window::OnNonClientPaint(HRGN region) const noexcept
	{
		HDC hdc = GetDCEx(Handle(), region, DCX_WINDOW | DCX_INTERSECTRGN | DCX_USESTYLE);

		RECT rect;
		GetWindowRect(Handle(), &rect);

		SIZE size = SIZE { rect.right - rect.left, rect.bottom - rect.top };

		HBITMAP hbmMem = CreateCompatibleBitmap(hdc, size.cx, size.cy);
		HANDLE hOld = SelectObject(hdc, hbmMem);



		HBRUSH brush = CreateSolidBrush(RGB(46, 46, 46));

		RECT newRect = RECT { 0, 0, size.cx, size.cy };

		FillRect(hdc, &newRect, brush);
		DeleteObject(brush);

		if (Active())
		{
			brush = CreateSolidBrush(RGB(100, 100, 100));
			FrameRect(hdc, &newRect, brush);
		}

		DeleteObject(brush);

		BitBlt(hdc, 0, 0, size.cx, size.cy, hdc, 0, 0, SRCCOPY);

		SelectObject(hdc, hOld);
		DeleteObject(hbmMem);

		ReleaseDC(Handle(), hdc);
	}

	void Window::RedrawWindow() const noexcept
	{
		SetWindowPos(Handle(), 0, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_DRAWFRAME | SWP_FRAMECHANGED); // reset window
		SendMessage(Handle(), WM_PAINT, 0, 0);
	}
}