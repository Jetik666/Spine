#include "Engine.h"
#include "SplashScreen.h"

#include "Platform/Win32/Win32Utils.h"

namespace SplashScreen 
{
	#define WM_OUTPUTMESSAGE (WM_USER + 0x0001)

	SplashWindow* m_SplashWindow;

	void Open() noexcept 
	{
		if (m_SplashWindow != nullptr) 
		{
			return;
		}
		m_SplashWindow = new SplashWindow();
	}

	void Close() noexcept 
	{
		return void ENGINE_API();
	}

	void AddMessage(const wchar_t* message) noexcept 
	{
		PostMessage(m_SplashWindow->Handle(), WM_OUTPUTMESSAGE, (WPARAM)message, 0);
	}

	void SetTitle(const wchar_t* title) noexcept
	{
		m_SplashWindow->SetTitle(title);
	}
}

SplashWindow::SplashWindow() noexcept
	: Win32::Window(L"SplashScreen", ApplicationSettings::MainIcon(), Win32::WindowType::POPUP)
{
	wcscpy_s(m_OutputMessage, L"SplashScreen Starting...");
	Win32::Window::RegisterNewClass();
	Win32::Window::Initialize();
}

SplashWindow::~SplashWindow() noexcept {}

LRESULT SplashWindow::MessageHandler(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam) noexcept 
{
	switch (message) 
	{
		case WM_PAINT: 
		{
			HBITMAP hbitmap{};
			HDC hdc, hmemdc{};
			PAINTSTRUCT ps;

			hdc = BeginPaint(hwnd, &ps);

			Win32::Utils::AddBitmap(ApplicationSettings::SplashURL(), hdc);

			SetBkMode(hdc, TRANSPARENT);
			SetTextColor(hdc, RGB(255, 255, 255));

			if (EngineMode::GetMode() != Mode::RELEASE) 
			{ 
				std::wstring engineModeText = EngineMode::EngineModeToString() + L" Mode";
				SetTextAlign(hdc, TA_RIGHT);
				TextOut(hdc, Size().cx - 15, 15, engineModeText.c_str(), static_cast<int>(wcslen(engineModeText.c_str())));
			}

			SetTextAlign(hdc, TA_CENTER);

			TextOut(hdc, Size().cx / 2, Size().cy - 30, m_OutputMessage, static_cast<int>(wcslen(m_OutputMessage)));
			EndPaint(hwnd, &ps);
		
			break;
		}
		case WM_OUTPUTMESSAGE: 
		{
			wchar_t* msg = (wchar_t*)wparam;
			wcscpy_s(m_OutputMessage, msg);
			RedrawWindow();
			return 0;
		}
	}

	return Window::MessageHandler(hwnd, message, wparam, lparam);
}

void SplashWindow::SetTitle(const wchar_t* title) noexcept
{
	if (SetWindowText(m_Handle, title) == 0)
	{
		//TODO: Throw exception
	}
}
