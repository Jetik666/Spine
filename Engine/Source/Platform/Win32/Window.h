#pragma once

#include "SubObject.h"

#include <optional>
#include <memory>
#include <Uxtheme.h>
#pragma comment(lib, "uxtheme.lib")

namespace Win32 
{
	class ENGINE_API Window : public SubObject, public Caption
	{
		/* Constructor */
	public:
		Window(const wchar_t* title, HICON hIcon, WindowType type = RESIZABLE) noexcept;
		~Window() noexcept;

		/* Public methods */
	public:
		virtual void Initialize() noexcept override;
		virtual LRESULT	MessageHandler(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam) noexcept override;

		void OnNonClientCreate() noexcept;
		void OnNonClientActivate(bool active) noexcept;
		void OnNonClientPaint(HRGN region) const noexcept;

		void RedrawWindow() const noexcept;
		void PaintCaption(HDC hdc) const noexcept;

		void OnNonClientLeftMouseButtonDown() noexcept;
		void OnGetMinMaxInfo(MINMAXINFO* minmax) const noexcept;
		void OnExitSizeMove() const noexcept;
		void OnPaint() const noexcept;

		/* Private variables */
	private:
		SIZE m_Size;
		WindowType m_Type;

		bool m_Active;
		bool m_Running;

		wchar_t* m_Name;

		Graphics m_Graphics;

		/* Getters and Setters */
	public:
		SIZE Size() const noexcept { return m_Size; }
		void Size(SIZE size) noexcept { m_Size = size; }
		void Size(int cx, int cy) noexcept { m_Size.cx = cx; m_Size.cy = cy; }

		WindowType Type() const noexcept { return m_Type; }
		void Type(WindowType type) noexcept { m_Type = type; }

		bool Active() const noexcept { return m_Active; }
		void Active(bool active) noexcept { m_Active = active; }

		bool Running() const noexcept { return m_Running; }
		void Running(bool running) noexcept { m_Running = running; }

		wchar_t* Name() const noexcept { return m_Name; }
		void Name(wchar_t* name) noexcept;
		void Name(const wchar_t* name) noexcept;

		Graphics Graphics() const noexcept { return m_Graphics; }
		void Graphics(HWND hWnd) noexcept { m_Graphics.Initialize(hWnd); }
	};
}

