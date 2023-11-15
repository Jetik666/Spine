#pragma once

#include "SubObject.h"

namespace Win32
{
	class ENGINE_API Window : public Win32::SubObject
	{
		/* Constructor */
	public:
		Window(std::wstring className, std::wstring classTitle, HICON hIcon, int width, int height);
		~Window();

		/* Public functions */
	public:
		virtual void Initialize() override;

		/* Protected variables */
	protected:
		int m_Width;
		int m_Height;
	};
}

