#pragma once

#include "Platform/Win32/IApplication.h"

namespace TestEngine 
{
	class Simulation : public Win32::IApplication, public Win32::Window
	{
		/* Constructor */
	public:
		Simulation() noexcept;
		~Simulation() noexcept;

		/* Public methods */
	public:
		virtual void PreInitialize() noexcept override;
		virtual LRESULT MessageHandler(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam) noexcept override;
	};
}

