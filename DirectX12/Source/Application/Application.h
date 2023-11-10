#pragma once

#include "../Platform/Windows/Windows.h"

class Application
{
public:
	Application();
	~Application();

public:
	int Initialize();
	void Update();

private:
	Window pWindow;

	bool isRunning;
};
