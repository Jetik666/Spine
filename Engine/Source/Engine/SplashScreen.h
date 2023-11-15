#pragma once

#include "Platform/Win32/Window.h"

namespace SplashScreen
{
	void ENGINE_API Open();
	void ENGINE_API Close();
	void ENGINE_API AddMessage(const wchar_t* message);
};

class ENGINE_API SplashWindow : public Win32::Window
{
	/* Constructor */
public:
	SplashWindow();
	~SplashWindow();

	/* Public functions */
public:
	virtual LRESULT				MessageHandler(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam) override;

	/* Private variables */
private:
	wchar_t m_OutputMessage[MAX_NAME_STRING];
};
