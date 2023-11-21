#pragma once

#include "SubObject.h"

#include <Uxtheme.h>
#pragma comment(lib, "uxtheme.lib")

namespace Win32 
{
	class ENGINE_API Window : public Win32::SubObject 
	{
		/* Constructor */
	public:
		Window(const wchar_t* title, HICON hIcon, WindowType type = RESIZABLE) noexcept;
		~Window() noexcept;

		/* Public functions */
	public:
		virtual void Initialize() noexcept override;
		virtual LRESULT	MessageHandler(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam) noexcept override;

		void OnNonClientCreate() const noexcept;
		void OnNonClientActivate(bool active);
		void OnNonClientPaint(HRGN region) const noexcept;

		void RedrawWindow() const noexcept;

		/* Protected variables */
	protected:
		SIZE m_Size;
		WindowType m_Type;
		bool m_Active;
		/* Getters and Setters */
	public:
		SIZE Size() const noexcept { return m_Size; }
		void Size(SIZE size) noexcept { m_Size = size; }
		void Size(int cx, int cy) noexcept { m_Size.cx = cx; m_Size.cy = cy; }

		bool Active() const noexcept { return m_Active; }
		void Active(bool active) noexcept { m_Active = active; }
	};
}

