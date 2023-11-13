#include "pch.h"
#include "Application.h"

#include <string>

Application::Application() 
	: m_Window(800, 600), m_IsRunning(true)
{
	SetupSettings();
	m_IsRunning = true;
	m_FrameCounter.SetFramesLimit(60);
}

Application::~Application() {}

int Application::Initialize()
{
#ifdef _DEBUG
	Logger::StartMtail();
#endif

	Logger::PrintLog(L"I have loaded up.%s", L"Game Project");

	std::thread renderThread(&Application::Update, this);

	while (m_IsRunning)
	{
		if (const std::optional<int> code = m_Window.ProcessMessage())
		{
			m_IsRunning = false;
			renderThread.join();
			return *code;
		}
	}

	renderThread.join();
	return 0;
}

void Application::Update()
{
	while (m_IsRunning)
	{ 
		if (m_FrameCounter.ShowFrame())
		{
			m_FrameCounter.Mark();

			#ifdef _DEBUG
			wchar_t title[1024];

			wcscpy_s(title, ApplicationSettings::GameName());
			wcscat_s(title, L" FPS: ");
			std::wstring ws = std::to_wstring(m_FrameCounter.GetFramesAmount());
			wcscat_s(title, ws.c_str());
			wcscat_s(title, L" Frame Time: ");
			ws = std::to_wstring(m_FrameCounter.GetFrameTime());
			wcscat_s(title, ws.c_str());

			m_Window.SetTitle(title);
			#endif // _DEBUG
		}
	}
}

void Application::SetupSettings()
{
	ApplicationSettings::SetGameName(IDS_PERGAMENAME);
	ApplicationSettings::SetShortName(IDS_SHORTNAME);
	ApplicationSettings::SetMainIcon(IDI_MAINICON);
}
