#pragma once

#include "../Platform/Windows/Windows.h"
#include "Platform/IApplication.h"

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

	bool m_IsRunning;
};
