#include "Engine.h"
#include "Simulation.h"
#include "Engine/SplashScreen.h"

TestEngine::Simulation::Simulation() {}

TestEngine::Simulation::~Simulation() {}

void TestEngine::Simulation::PreInitialize()
{
	Logger::PrintDebugSeparator();
	Logger::PrintLog(L"Application has loaded up: %s\n", ApplicationSettings::GameName());
	Logger::PrintLog(L"Boot time: %s\n", ApplicationSettings::BootTime());
	Logger::PrintLog(L"Engine Mode: %s\n", EngineMode::EngineModeToString().c_str());
	Logger::PrintDebugSeparator();

	SplashScreen::Open();
}
