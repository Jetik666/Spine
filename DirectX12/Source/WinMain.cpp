#include "pch.h"
#include "Application/Application.h"

int CALLBACK WinMain(
	_In_ HINSTANCE,
	_In_opt_ HINSTANCE,
	_In_ LPSTR,
	_In_ int)
{
	

	return Application{}.Initialize();
}

