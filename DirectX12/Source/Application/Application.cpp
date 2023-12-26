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
		GraphicsRef().ToggleVSync(true);
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
		while (Running())
		{
			if (FrameRate().ShowFrame())
			{
			#ifdef _DEBUG
				//ShowFPS();
			#endif
				//TODO: Fix memory leak
				Sleep(1500);
				Graphics(Graphic::GraphicalFactory::SetInput(Graphic::D3D12_t, Handle()));
				Sleep(1500);
				Graphics(Graphic::GraphicalFactory::SetInput(Graphic::OpenGL_t, Handle()));
				Sleep(1500);
				Graphics(Graphic::GraphicalFactory::SetInput(Graphic::D3D11_t, Handle()));

				/*GraphicsRef().Update(1.0f, 1.0f, 1.0f);



				GraphicsRef().Render();*/
			}
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
		std::wstring amount = L" FPS: " + std::to_wstring(static_cast<unsigned short>(FrameRate().Amount()));
		std::wstring frameTime = L" Frame Time: " + std::to_wstring(FrameRate().Time());
		std::wstring fpsInfo = ApplicationSettings::GameName() + amount + frameTime;

		const wchar_t* info = fpsInfo.c_str();

		Name(info);
	}
}
