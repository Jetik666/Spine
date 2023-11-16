#include "Engine.h"
#include "Window.h"

namespace Win32 
{
	Window::Window(std::wstring className, std::wstring classTitle, HICON hIcon, int width, int height) noexcept
		: Win32::SubObject(className, classTitle, hIcon)
		, m_Width(width)
		, m_Height(height)
	{}

	Window::~Window() noexcept 
	{
		UnregisterClass(m_Class, HInstance());
	}

	void Window::Initialize() noexcept 
	{
		RECT desktop;
		const HWND hDesktop = GetDesktopWindow();
		GetWindowRect(hDesktop, &desktop);

		RECT R = { 0, 0, m_Width, m_Height };
		AdjustWindowRect(&R, WS_OVERLAPPEDWINDOW, false);
		int width = R.right - R.left;
		int height = R.bottom - R.top;

		/*
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU - Task bar is on
		WS_POPUPWINDOW - Task bar is off
		*/
		m_Handle = CreateWindow(m_Class, m_Title, 
			WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
			((desktop.right / 2) - (m_Width / 2)), ((desktop.bottom / 2) - (m_Height / 2)),
			m_Width, m_Height, 0, 0, HInstance(), (void*)this);
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
}