#pragma once

#include "Platform/Win32/Window.h"

namespace SplashScreen 
{
	void ENGINE_API Open() noexcept;
	void ENGINE_API Close() noexcept;
	void ENGINE_API AddMessage(const wchar_t* message) noexcept;
	void SetTitle(const wchar_t* title) noexcept;
};

class ENGINE_API SplashWindow : public Win32::Window 
{
	/* Constructor */
public:
	SplashWindow() noexcept;
	~SplashWindow() noexcept;

	/* Public functions */
public:
	virtual LRESULT	MessageHandler(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam) noexcept override;
	void SetTitle(const wchar_t* name) noexcept;

	/* Private variables */
private:
	wchar_t m_OutputMessage[MAX_NAME_STRING];
};
