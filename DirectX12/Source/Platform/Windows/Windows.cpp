#include "pch.h"
#include "Windows.h"

#include <comdef.h>

#pragma region Window configuration
Window::Configuration::Configuration() noexcept : m_hInst(GetModuleHandle(nullptr))
{
	LoadString(m_hInst, IDS_PERGAMENAME, m_Name, MAX_NAME_STRING);
	LoadString(m_hInst, IDS_WINDOWCLASS, m_Class, MAX_NAME_STRING);

	m_Wcex.cbSize = sizeof(WNDCLASSEX);
	m_Wcex.style = CS_HREDRAW | CS_VREDRAW;
	m_Wcex.cbClsExtra = 0;
	m_Wcex.cbWndExtra = 0;
	m_Wcex.hInstance = GetInstance();
	m_Wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	m_Wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	m_Wcex.hIcon = static_cast<HICON>(LoadIcon(m_hInst, MAKEINTRESOURCE(IDI_MAINICON)));
	m_Wcex.hIconSm = static_cast<HICON>(LoadIcon(m_hInst, MAKEINTRESOURCE(IDI_MAINICON)));
	m_Wcex.lpszClassName = GetClass();
	m_Wcex.lpszMenuName = nullptr;
	m_Wcex.lpfnWndProc = HandleMessage;

	RegisterClassEx(&m_Wcex);
}

Window::Configuration::~Configuration() noexcept 
{
	UnregisterClass(m_Class, GetInstance());
}

const wchar_t* Window::Configuration::GetName() noexcept
{	
	return m_Name;
}

const wchar_t* Window::Configuration::GetClass() noexcept
{
	return m_Class;
}

HINSTANCE Window::Configuration::GetInstance() noexcept
{
	return m_hInst;
}
#pragma endregion

Window::Window(int width, int height) : m_Width(width), m_Height(height)
{
	RECT wr{};
	SetPosition(&wr);
	Initialize(wr);
}

Window::~Window()
{
	DestroyWindow(m_HWND);
}

void Window::SetPosition(RECT* wr)
{
	wr->left = 100;
	wr->right = m_Width + wr->left;
	wr->top = 100;
	wr->bottom = m_Height + wr->top;
	if (AdjustWindowRect(wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE) == 0)
	{
		//TODO: Throw exception
	}
}

void Window::Initialize(RECT wr)
{
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);

	int windowWidth = wr.right - wr.left;
	int windowHeight = wr.bottom - wr.top;

	int x = (screenWidth - windowWidth) / 2;
	int y = (screenHeight - windowHeight) / 2;

	m_HWND = CreateWindow(m_Configuration.GetClass(), m_Configuration.GetName(),
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, x, y,
		m_Width, m_Height, nullptr, nullptr, m_Configuration.GetInstance(), this);
	if (!m_HWND)
	{
		//TODO: Throw exception
		MessageBox(0, L"Error.", 0, 0);
		PostQuitMessage(0);
		return;
	}

	ShowWindow(m_HWND, SW_SHOW);
}

void Window::Resize(int width, int height) noexcept
{
	m_Width = width;
	m_Height = height;

	RECT wr{};
	SetPosition(&wr);

	MoveWindow(m_HWND, wr.left, wr.top, m_Width, m_Height, TRUE);
}

std::optional<int> Window::ProcessMessage()
{
	MSG msg;

	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
		{
			return (int)msg.wParam;
		}

		if (msg.message == WM_MOVE || msg.message == WM_SIZE)
		{
			return {};
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return {};
}

LRESULT CALLBACK Window::HandleMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	switch (msg)
	{
		case WM_CLOSE:
		{
			PostQuitMessage(0);
			break;
		}
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

HWND Window::GetHWND() noexcept
{
	return m_HWND;
}

void Window::SetTitle(const wchar_t* name) noexcept
{
	if (SetWindowText(m_HWND, name) == 0)
	{
		//TODO: Throw exception
	}
}
