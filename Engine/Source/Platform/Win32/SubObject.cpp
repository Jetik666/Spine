#include "Engine.h"
#include "SubObject.h"

namespace Win32
{
	Win32::SubObject::SubObject(std::wstring className, std::wstring classTitle, HICON hIcon)
		: m_Class(className), m_Title(classTitle), m_hIcon(hIcon)
	{
	}

	Win32::SubObject::~SubObject()
	{
	}

	void SubObject::RegisterNewClass() const
	{
		WNDCLASSEX wcex{};
		wcex.cbSize = sizeof(WNDCLASSEX);
		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wcex.hbrBackground = (HBRUSH)(CreateSolidBrush(RGB(46, 46, 46)));
		wcex.hIcon = m_hIcon;
		wcex.hIconSm = m_hIcon;
		wcex.lpszClassName = m_Class.c_str();
		wcex.lpszMenuName = nullptr;
		wcex.hInstance = HInstance();
		wcex.lpfnWndProc = SetupMessageHandler;
		RegisterClassEx(&wcex);
	}

	LRESULT SubObject::SetupMessageHandler(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam)
	{
		if (message == WM_NCCREATE)
		{
			const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lparam);
			Win32::SubObject* const pWnd = static_cast<Win32::SubObject*>(pCreate->lpCreateParams);
			SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
			SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Win32::SubObject::AssignMessageHandler));
			return pWnd->MessageHandler(hWnd, message, wparam, lparam);
		}
		return DefWindowProc(hWnd, message, wparam, lparam);
	}

	LRESULT SubObject::AssignMessageHandler(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam)
	{
		Win32::SubObject* const pWnd = reinterpret_cast<Win32::SubObject*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
		return pWnd->MessageHandler(hWnd, message, wparam, lparam);
	}

	LRESULT SubObject::CommonMessageHandler(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam)
	{
		return DefWindowProc(hWnd, message, wparam, lparam);
	}
}
