#include "BlankProject.h"
#include "Application.h"

namespace Windows 
{
	Application::Application() 
	{
		SetupSettings();
	}

	Application::~Application() {}

	void Application::Initialize() 
	{
		MSG msg = { 0 };
		while (msg.message != WM_QUIT) 
		{
			// If there are Window messages then process them.
			if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else {
				Update();
			}
		}
	}

	void Application::Update() 
	{
		if (m_FrameCounter.ShowFrame()) 
		{

		}
	}

	void Application::SetupSettings() {
		ApplicationSettings::SetGameName(IDS_PERGAMENAME);
		ApplicationSettings::SetShortName(IDS_SHORTNAME);
		ApplicationSettings::SetMainIcon(IDI_MAINICON);
	}
}
