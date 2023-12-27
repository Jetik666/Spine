#include "Engine.h"
#include "Simulation.h"
#include "Engine/SplashScreen.h"

namespace TestEngine
{
	Simulation::Simulation() noexcept
		: Win32::Window(ApplicationSettings::GameName(), ApplicationSettings::MainIcon())
	{}

	Simulation::~Simulation() noexcept {}

	void Simulation::PreInitialize() noexcept
	{
		Win32::Window::Name(ApplicationSettings::GameName());

		Logger::PrintDebugSeparator();
		Logger::PrintLog(L"Application has loaded up: %s\n", ApplicationSettings::GameName());
		Logger::PrintLog(L"Boot time: %s\n", ApplicationSettings::BootTime());
		Logger::PrintLog(L"Engine Mode: %s\n", EngineMode::EngineModeToString().c_str());
		Logger::PrintDebugSeparator();

		//SplashScreen::Open();

		Win32::Window::RegisterNewClass();
		Win32::Window::Initialize();
		Win32::Window::Graphics(Graphic::GraphicalFactory::SetInput(Graphic::OpenGL_t, Win32::Window::Handle()));
	}

	LRESULT Simulation::MessageHandler(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam) noexcept
	{
		return Window::MessageHandler(hwnd, message, wparam, lparam);
	}
}