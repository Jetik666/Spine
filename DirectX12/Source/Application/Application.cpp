#include "pch.h"
#include "Application.h"
#include "Platform/WIN32/WinEntry.h"

Application::Application()
{
}

Application::~Application()
{
}

void Application::Initialize()
{
	MessageBox(0, L"I have loaded up.", 0, 0);
}

void Application::Update()
{
}
