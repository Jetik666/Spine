#include "Engine.h"
#include "SplashScreen.h"

namespace SplashScreen
{
	#define WM_OUTPUTMESSAGE (WM_USER + 0x0001)

	SplashWindow* m_SplashWindow;

	void Open()
	{
		if (m_SplashWindow != nullptr)
		{
			return;
		}
		m_SplashWindow = new SplashWindow();
	}

	void Close()
	{
		return void ENGINE_API();
	}

	void AddMessage(const wchar_t* message)
	{
		PostMessage(m_SplashWindow->GetHandle(), WM_OUTPUTMESSAGE, (WPARAM)message, 0);
	}
}

SplashWindow::SplashWindow()
	: Win32::Window(L"SplashScreen", L"SplashScreen", NULL, 800, 500)
{
	wcscpy_s(m_OutputMessage, L"SplashScreen Starting...");
	Win32::Window::RegisterNewClass();
	Win32::Window::Initialize();
}

SplashWindow::~SplashWindow()
{
}

LRESULT SplashWindow::MessageHandler(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	switch (message)
	{
	case WM_PAINT:
	{
		HBITMAP hbitmap;
		HDC hdc, hmemdc;
		PAINTSTRUCT ps;

		hdc = BeginPaint(hwnd, &ps);

		SetBkMode(hdc, TRANSPARENT);
		SetTextColor(hdc, RGB(255, 255, 255));

		if (EngineMode::GetMode() != EngineModes::RELEASE)
		{ 
			std::wstring engineModeText = EngineMode::EngineModeToString() + L" Mode";
			SetTextAlign(hdc, TA_RIGHT);
			TextOut(hdc, m_Width - 15, 15, engineModeText.c_str(), wcslen(engineModeText.c_str()));
		}

		SetTextAlign(hdc, TA_CENTER);

		TextOut(hdc, m_Width / 2, m_Height - 30, m_OutputMessage, wcslen(m_OutputMessage));
		EndPaint(hwnd, &ps);
		
		break;
	}
	case WM_OUTPUTMESSAGE:
	{
		wchar_t* msg = (wchar_t*)wparam;
		wcscpy_s(m_OutputMessage, msg);
		RedrawWindow(GetHandle(), NULL, NULL, RDW_INVALIDATE);
		return 0;
	}
	}

	return CommonMessageHandler(hwnd, message, wparam, lparam);
}