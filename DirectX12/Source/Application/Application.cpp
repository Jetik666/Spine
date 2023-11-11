#include "pch.h"
#include "Application.h"

Application::Application() : m_Window(800, 600), m_IsRunning(true)
{
	//m_Window.SetTitle(L"Test");
	PerGameSettings gameSettings;
	SetupPerGameSettings();
	Logger logger;
}

Application::~Application() {}

int Application::Initialize()
{
	Logger::StartMtail();
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

void Application::SetupPerGameSettings()
{
	PerGameSettings::SetGameName(IDS_PERGAMENAME);
	PerGameSettings::SetShortName(IDS_SHORTNAME);
	PerGameSettings::SetMainIcon(IDI_MAINICON);
}
