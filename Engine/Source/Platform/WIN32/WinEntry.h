#include "Engine.h"

#include "IApplication.h"

extern IApplication* EntryApplication();

int CALLBACK WinMain(
	_In_ HINSTANCE,
	_In_opt_ HINSTANCE,
	_In_ LPSTR,
	_In_ int)
{
	auto EntryApp = EntryApplication();

	EntryApp->Initialize();
	return 0;
}