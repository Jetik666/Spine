#include "BlankProject.h"
#include "Application.h"

int CALLBACK WinMain(
	_In_ HINSTANCE,
	_In_opt_ HINSTANCE,
	_In_ LPSTR,
	_In_ int) 
{
	ApplicationSettings GameSettings;
	Windows::Application Game;

	Logger logger;
	Game.PreInitialize();
	Game.Initialize();

	return 0;
}