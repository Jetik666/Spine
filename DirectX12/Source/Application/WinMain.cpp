#include "BlankProject.h"
#include "Application.h"

#include "Common/CmdLineArgs.h"

int CALLBACK WinMain(
	_In_ HINSTANCE,
	_In_opt_ HINSTANCE,
	_In_ LPSTR,
	_In_ int) 
{
	ApplicationSettings GameSettings;
	Windows::Application Game;
	Logger logger;

	CmdLineArgs::ReadArguments();

	Game.PreInitialize();
	Game.Initialize();

	return 0;
}