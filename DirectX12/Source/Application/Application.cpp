#include "pch.h"
#include "Application.h"

Application::Application() : m_Window(800, 600), m_IsRunning(true)
{
	SetupSettings();
}

Application::~Application() {}

int Application::Initialize()
{
#ifdef _DEBUG
	Logger::StartMtail();
#endif

	Logger::PrintLog(L"I have loaded up.%s", L"Game Project");

	while (m_IsRunning)
	{
		if (const std::optional<int> code = m_Window.ProcessMessage())
		{
			m_IsRunning = false;
			return *code;
		}
		Update();
	}

	return 0;
}

void Application::Update()
{
	
}

void Application::SetupSettings()
{
	ApplicationSettings::SetGameName(IDS_PERGAMENAME);
	ApplicationSettings::SetShortName(IDS_SHORTNAME);
	ApplicationSettings::SetMainIcon(IDI_MAINICON);
}
