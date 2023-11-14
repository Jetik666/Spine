#include "pch.h"
#include "Application/Application.h"
#include "Common/CmdLineArgs.h"

int CALLBACK WinMain(
	_In_ HINSTANCE,
	_In_opt_ HINSTANCE,
	_In_ LPSTR,
	_In_ int) 
{

	ApplicationSettings gameSettings;
	Logger logger;

	CmdLineArgs::ReadArguments();

	Application newApplication;

	return newApplication.Initialize();
}
