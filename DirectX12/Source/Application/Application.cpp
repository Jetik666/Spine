#include "pch.h"
#include "Application.h"

#include "Engine/SplashScreen.h"

#include <string>
#include <thread>

Application::Application() 
	: m_IsRunning(true)
{
	m_FrameCounter.SetFramesLimit(300);
}

Application::~Application() {}

int Application::Initialize() 
{
	Logger::PrintDebugSeparator();
	Logger::PrintLog(L"Application has loaded up: %s\n", ApplicationSettings::GameName());
	Logger::PrintLog(L"Boot time: %s\n", ApplicationSettings::BootTime());
	Logger::PrintLog(L"Engine Mode: %s\n", EngineMode::EngineModeToString().c_str());
	Logger::PrintDebugSeparator();

	MSG msg = { 0 };
	while (msg.message != WM_QUIT) 
	{
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
	return 0;
}

void Application::Update() 
{
	if (m_FrameCounter.ShowFrame())
	{

	}
}

void Application::SetupSettings() 
{
	ApplicationSettings::SetGameName(IDS_PERGAMENAME);
	ApplicationSettings::SetShortName(IDS_SHORTNAME);
	ApplicationSettings::SetMainIcon(IDI_MAINICON);
}
