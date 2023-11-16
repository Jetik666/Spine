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
		void SetTitle();

		/* Private functions */
	private:
		virtual void Initialize() override;

		/* Protected variables */
	protected:
		int m_Width;
		int m_Height;

		HWND m_Handle;

		/* Getters and Setters */
	public:
		HWND GetHandle() const { return m_Handle; };
	};
}

