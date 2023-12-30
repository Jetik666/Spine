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
		GraphicsRef().ToggleVSync(false);
		FrameRate().Limit(300);

		std::thread render(&Application::Update, this);

		while (Running()) 
		{
			ProccessMessage();
		}

		render.join();
	}

	void Application::Update() noexcept 
	{
		std::mutex renderMutex;
		std::condition_variable frameCondition;

		while (Running())
		{

			FrameRate().StartFrame();

			const float c = sin(FrameRate().Time()) / 2.0f + 0.5f;
			GraphicsRef().Update(c, c, 1.0f);
			GraphicsRef().Render();

			FrameRate().EndFrame();
			FrameRate().Sleep(renderMutex);

		#ifdef _DEBUG
			ShowFPS();
		#endif

			frameCondition.notify_one();
			std::unique_lock<std::mutex> unlock(renderMutex);
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
		if (FrameRate().UpdateInforamtion())
		{
			std::wstring amount = L" FPS: " + std::to_wstring(FrameRate().FrameRate());
			std::wstring frameTime = L" Frame Time: " + std::to_wstring(FrameRate().Time());
			std::wstring fpsInfo = ApplicationSettings::GameName() + amount + frameTime;

			Name(fpsInfo.c_str());
		}
	}
}
