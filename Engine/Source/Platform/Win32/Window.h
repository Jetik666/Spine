#pragma once

#include "SubObject.h"

namespace Win32 
{
	class ENGINE_API Window : public Win32::SubObject 
	{
		/* Constructor */
	public:
		Window(const wchar_t* className, const wchar_t* classTitle, HICON hIcon, int width, int height) noexcept;
		~Window() noexcept;

		/* Public functions */
	public:
		virtual void Initialize() noexcept override;

		/* Protected variables */
	protected:
		int m_Width;
		int m_Height;
	};
}

