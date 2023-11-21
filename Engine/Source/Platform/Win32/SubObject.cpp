#include "Engine.h"
#include "SubObject.h"

namespace Win32 
{
	SubObject::SubObject(const wchar_t* name, const wchar_t* title, HICON hIcon) noexcept
		: m_Class(name), m_Title(title), m_hIcon(hIcon), m_Handle(nullptr) {}

	SubObject::~SubObject() noexcept {}

	void SubObject::RegisterNewClass() const noexcept 
	{
		WNDCLASSEX wcex{};
		wcex.cbSize = sizeof(WNDCLASSEX);
		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wcex.hbrBackground = (HBRUSH)(CreateSolidBrush(RGB(36, 36, 36)));
		wcex.hIcon = m_hIcon;
		wcex.hIconSm = m_hIcon;
		wcex.lpszClassName = m_Class;
		wcex.lpszMenuName = nullptr;
		wcex.hInstance = HInstance();
		wcex.lpfnWndProc = SetupMessageHandler;
		RegisterClassEx(&wcex);
	}

	LRESULT SubObject::SetupMessageHandler(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam) noexcept 
	{
		if (message == WM_NCCREATE) 
		{
			const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lparam);
			SubObject* const pWnd = static_cast<SubObject*>(pCreate->lpCreateParams);
			SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
			SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&SubObject::AssignMessageHandler));
			pWnd->Handle(hWnd);
			return pWnd->MessageHandler(hWnd, message, wparam, lparam);
		}
		return DefWindowProc(hWnd, message, wparam, lparam);
	}

	LRESULT SubObject::AssignMessageHandler(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam) noexcept 
	{
		SubObject* const pWnd = reinterpret_cast<SubObject*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
		return pWnd->MessageHandler(hWnd, message, wparam, lparam);
	}

	LRESULT SubObject::MessageHandler(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam) noexcept
	{
		return DefWindowProc(hWnd, message, wparam, lparam);
	}
}
