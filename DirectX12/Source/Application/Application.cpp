#include "BlankProject.h"
#include "Application.h"

#include "Platform/Win32/Window.h"

namespace Windows 
{
	Application::Application() noexcept 
	{
		SetupSettings();
		m_FrameCounter.FramesLimit(300);
	}

	Application::~Application() noexcept {}

	void Application::Initialize() noexcept 
	{
		MSG msg = { 0 };
		while (Running()) 
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
			ShowFPS();
			#endif
			m_Graphics.BeginFrame(1.0f, 1.0f, 1.0f);



			m_Graphics.EndFrame();
		}
	}

	void Application::SetupSettings() noexcept
	{
		ApplicationSettings::GameName(IDS_PERGAMENAME);
		ApplicationSettings::ShortName(IDS_SHORTNAME);
		ApplicationSettings::MainIcon(IDI_MAINICON);
		ApplicationSettings::SplashURL(IDS_SPLASHURL);
	}

	void Application::ShowFPS() noexcept
	{
		std::wstring amount = L" FPS: " + std::to_wstring(static_cast<unsigned short>(m_FrameCounter.FramesAmount()));
		std::wstring frameTime = L" Frame Time: " + std::to_wstring(m_FrameCounter.FrameTime());
		std::wstring fpsInfo = ApplicationSettings::GameName() + amount + frameTime;

		const wchar_t* info = fpsInfo.c_str();

		Name(info);
	}
}
