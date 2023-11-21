#pragma once

namespace Win32 
{ 
	class ENGINE_API SubObject 
	{
		/* Constructor */
	public:
		SubObject(const wchar_t* className, const wchar_t* classTitle, HICON hIcon) noexcept;
		~SubObject() noexcept;

		/* Public functions */
	public:
		virtual void RegisterNewClass() const noexcept;
		virtual void Initialize() = 0;

		/* Protected functions */
	protected:
		static	LRESULT CALLBACK SetupMessageHandler(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam) noexcept;
		static	LRESULT	AssignMessageHandler(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam) noexcept;
		virtual LRESULT	CommonMessageHandler(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam) noexcept;

		virtual LRESULT	MessageHandler(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam) = 0;

		/* Protected variables */
	protected:
		const wchar_t* m_Class;
		const wchar_t* m_Title;
		HICON m_hIcon;
		HWND m_Handle;

		/* Getters and Setters */
	public:
		HWND GetHandle() const noexcept { return m_Handle; };
	};
}
