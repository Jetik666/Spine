#include "pch.h"
#include "Application.h"

Application::Application() : pWindow(800, 600), isRunning(true)
{
	
}

Application::~Application()
{
}

int Application::Initialize()
{
	MessageBox(0, "I have loaded up.", 0, 0);
	
	while (isRunning)
	{
		Update();
	}

	return 0;
}

void Application::Update()
{
	MessageBox(0, "I have been updated.", 0, 0);
}
