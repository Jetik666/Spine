#include "Engine.h"
#include "Simulation.h"
#include "Engine/SplashScreen.h"

namespace TestEngine
{
	Simulation::Simulation() noexcept
		: Win32::Window(L"Test", ApplicationSettings::MainIcon())
	{}

	Simulation::~Simulation() noexcept {}

	void Simulation::PreInitialize() noexcept
	{
		Logger::PrintDebugSeparator();
		Logger::PrintLog(L"Application has loaded up: %s\n", ApplicationSettings::GameName());
		Logger::PrintLog(L"Boot time: %s\n", ApplicationSettings::BootTime());
		Logger::PrintLog(L"Engine Mode: %s\n", EngineMode::EngineModeToString().c_str());
		Logger::PrintDebugSeparator();


		Win32::Window::RegisterNewClass();
		Win32::Window::Initialize();
		SplashScreen::Open();
	}

	LRESULT Simulation::MessageHandler(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam) noexcept
	{
		switch (message)
		{
			
		}

		return Window::MessageHandler(hwnd, message, wparam, lparam);
	}

	void Simulation::SetTitle(const wchar_t* title) noexcept
	{
		if (SetWindowText(m_Handle, title) == 0)
		{
			//TODO: Throw exception
		}
	}

	//void Simulation::SetTitle(const wchar_t* title) const noexcept
	//{
	//	SplashScreen::SetTitle(title);
	//}
}