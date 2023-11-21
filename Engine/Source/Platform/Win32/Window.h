#pragma once

#include "SubObject.h"

#include <Uxtheme.h>
#pragma comment(lib, "uxtheme.lib")

namespace Win32 
{
	class ENGINE_API Window : public Win32::SubObject, public Win32::Caption
	{
		/* Constructor */
	public:
		Window(const wchar_t* title, HICON hIcon, WindowType type = RESIZABLE) noexcept;
		~Window() noexcept;

		/* Public functions */
	public:
		virtual void Initialize() noexcept override;
		virtual LRESULT	MessageHandler(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam) noexcept override;

		void OnNonClientCreate() noexcept;
		void OnNonClientActivate(bool active) noexcept;
		void OnNonClientPaint(HRGN region) noexcept;

		void RedrawWindow() const noexcept;
		void PaintCaption(HDC hdc) noexcept;

		void OnNonClientLeftMouseButtonDown();

		/* Protected variables */
	protected:
		SIZE m_Size;
		WindowType m_Type;
		bool m_Active;
		const wchar_t* m_Name;
		/* Getters and Setters */
	public:
		SIZE Size() const noexcept { return m_Size; }
		void Size(SIZE size) noexcept { m_Size = size; }
		void Size(int cx, int cy) noexcept { m_Size.cx = cx; m_Size.cy = cy; }

		bool Active() const noexcept { return m_Active; }
		void Active(bool active) noexcept { m_Active = active; }

		const wchar_t* Name() const noexcept { return m_Name; }
		void Name(const wchar_t* name) { m_Name = name; }
	};
}

