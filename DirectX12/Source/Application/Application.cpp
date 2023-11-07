#include "pch.h"
#include "Application.h"

Application::Application() : pWindow(800, 600), isRunning(true)
{
	pWindow.ChangeName("Test");
}

Application::~Application() {}

int Application::Initialize()
{
	while (isRunning)
	{
		if (const std::optional<int> code = pWindow.ProcessMessage())
		{
			isRunning = false;
			return *code;
		}
		Update();
	}

	return 0;
}

void Application::Update()
{

}
