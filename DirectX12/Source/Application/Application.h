#pragma once

#include "Engine/Simulation.h"
#include "Common/Time/FrameCounter.h"

class Application : public TestEngine::Simulation
{
public:
	Application();
	~Application();

public:
	int Initialize();
	void Update();
	void SetupSettings();

private:
	FrameCounter m_FrameCounter;

	bool m_IsRunning;
};
