#pragma once

#include "Platform/Win32/Window.h"

namespace SplashScreen 
{
	void Open() noexcept;
	void Close() noexcept;
	void AddMessage(const wchar_t* message) noexcept;
	void SetTitle(const wchar_t* title) noexcept;
};

class SplashWindow : public Win32::Window 
{
	/* Constructor */
public:
	SplashWindow() noexcept;
	~SplashWindow() noexcept;

	/* Public methods */
public:
	virtual LRESULT	MessageHandler(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam) noexcept override;
	void SetTitle(const wchar_t* name) noexcept;

	/* Private variables */
private:
	wchar_t m_OutputMessage[MAX_NAME_STRING];
};
