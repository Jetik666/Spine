#pragma once

#include "../Platform/Windows/Windows.h"
#include "Platform/IApplication.h"
#include "Common/Time/FrameCounter.h"

class Application : public IApplication
{
public:
	Application();
	~Application();

public:
	int Initialize();
	void Update();
private:
	void SetupSettings();

private:
	Window m_Window;
	FrameCounter m_FrameCounter;

	bool m_IsRunning;
};
