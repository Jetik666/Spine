#include "Engine.h"
#include "Simulation.h"
#include "Engine/SplashScreen.h"

namespace TestEngine
{
	Simulation::Simulation() noexcept {}

	Simulation::~Simulation() noexcept {}

	void Simulation::PreInitialize() noexcept
	{
		Logger::PrintDebugSeparator();
		Logger::PrintLog(L"Application has loaded up: %s\n", ApplicationSettings::GameName());
		Logger::PrintLog(L"Boot time: %s\n", ApplicationSettings::BootTime());
		Logger::PrintLog(L"Engine Mode: %s\n", EngineMode::EngineModeToString().c_str());
		Logger::PrintDebugSeparator();

		SplashScreen::Open();
	}

	void Simulation::SetTitle(const wchar_t* title) const noexcept
	{
		SplashScreen::SetTitle(title);
	}
}