#include "BlankProject.h"
#include "Application.h"

#include "Platform/Win32/Window.h"

namespace Windows 
{
	Application::Application() noexcept 
	{
		SetupSettings();	}

	Application::~Application() noexcept {}

	void Application::Initialize() noexcept 
	{
		Graphics().ToggleVSync(false);

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
		Graphics().BeginFrame(0.1f, 0.1f, 0.1f);



		Graphics().EndFrame();

		#ifdef _DEBUG
		ShowFPS();
		#endif
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
		std::wstring amount = L" FPS: " + std::to_wstring(static_cast<unsigned short>(Graphics().FrameRate().Amount()));
		std::wstring frameTime = L" Frame Time: " + std::to_wstring(Graphics().FrameRate().Time());
		std::wstring fpsInfo = ApplicationSettings::GameName() + amount + frameTime;

		const wchar_t* info = fpsInfo.c_str();

		Name(info);
	}
}
