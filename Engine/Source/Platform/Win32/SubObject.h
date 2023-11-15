#pragma once
namespace Win32
{ 
	class ENGINE_API SubObject
	{
		/* Constructor */
	public:
		SubObject(std::wstring className, std::wstring classTitle, HICON hIcon);
		~SubObject();

		/* Public functions */
	public:
		virtual void RegisterNewClass() const;
		virtual void Initialize() = 0;

		/* Protected functions */
	protected:
		static	LRESULT CALLBACK	SetupMessageHandler(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam);
		static	LRESULT				AssignMessageHandler(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam);
		virtual LRESULT				CommonMessageHandler(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam);

		virtual LRESULT				MessageHandler(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam) = 0;

		/* Protected variables */
	protected:
		std::wstring m_Class;
		std::wstring m_Title;
		HICON m_hIcon;

		HWND m_Handle;

		/* Getters and Setters */
	public:
		HWND GetHandle() const { return m_Handle; };
	};
}


