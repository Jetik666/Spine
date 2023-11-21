#include "BlankProject.h"
#include "Application.h"

#include "Platform/Win32/Window.h"

namespace Windows 
{
	Application::Application() noexcept 
	{
		SetupSettings();
	}

	Application::~Application() noexcept {}

	void Application::Initialize() noexcept 
	{
		MSG msg = { 0 };
		while (msg.message != WM_QUIT) 
		{
			// If there are Window messages then process them.
			if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) 
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else 
			{
				Update();
			}
		}
	}

	void Application::Update() noexcept 
	{
		if (m_FrameCounter.ShowFrame()) 
		{
			#ifdef _DEBUG
			/*wchar_t title[1024];

			wcscpy_s(title, ApplicationSettings::GameName());
			wcscat_s(title, L" FPS: ");
			std::wstring ws = std::to_wstring(m_FrameCounter.GetFramesAmount());
			wcscat_s(title, ws.c_str());
			wcscat_s(title, L" Frame Time: ");
			ws = std::to_wstring(m_FrameCounter.GetFrameTime());
			wcscat_s(title, ws.c_str());

			SetTitle(title);*/

			std::wstring amount = std::to_wstring(m_FrameCounter.GetFramesAmount());
			std::wstring frameTime = std::to_wstring(m_FrameCounter.GetFrameTime());
			const wchar_t* title = L"Test FPS: %s Frame Time: %s";
			wcscpy_s
			#endif
		}
	}

	void Application::SetupSettings() noexcept
	{
		ApplicationSettings::SetGameName(IDS_PERGAMENAME);
		ApplicationSettings::SetShortName(IDS_SHORTNAME);
		ApplicationSettings::SetMainIcon(IDI_MAINICON);
		ApplicationSettings::SetSplashURL(IDS_SPLASHURL);
	}
}
