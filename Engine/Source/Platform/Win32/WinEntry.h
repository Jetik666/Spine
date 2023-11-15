#include "Engine.h"

#include "../IApplication.h"
#include "Common/CmdLineArgs.h"

extern Win32::IApplication* EntryApplication();

int CALLBACK WinMain(
	_In_ HINSTANCE,
	_In_opt_ HINSTANCE,
	_In_ LPSTR,
	_In_ int)
{

	auto EntryApp = EntryApplication();

	ApplicationSettings GameSettings;
	EntryApp->SetupSettings();

	CmdLineArgs::ReadArguments();

	Logger logger;

	EntryApp->PreInitialize();



	EntryApp->Initialize();



	MSG msg = { 0 };
	while (msg.message != WM_QUIT)
	{
		// If there are Window messages then process them.
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else 
		{
			EntryApp->Update();
		}
	}

	return 0;
}