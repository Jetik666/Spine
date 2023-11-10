#include "pch.h"
#include "Windows.h"

#include <comdef.h>

#pragma region Window configuration
Window::Configuration::Configuration() noexcept : pHINST(GetModuleHandle(nullptr))
{
	LoadString(pHINST, IDS_PERGAMENAME, pName, MAX_NAME_STRING);
	LoadString(pHINST, IDS_WINDOWCLASS, pClass, MAX_NAME_STRING);

	pWcex.cbSize = sizeof(WNDCLASSEX);
	pWcex.style = CS_HREDRAW | CS_VREDRAW;
	pWcex.cbClsExtra = 0;
	pWcex.cbWndExtra = 0;
	pWcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	pWcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	pWcex.hIcon = static_cast<HICON>(LoadIcon(pHINST, MAKEINTRESOURCE(IDI_MAINICON)));
	pWcex.hIconSm = static_cast<HICON>(LoadIcon(pHINST, MAKEINTRESOURCE(IDI_MAINICON)));
	pWcex.lpszClassName = GetClass();
	pWcex.lpszMenuName = nullptr;
	pWcex.lpfnWndProc = HandleProcess;

	RegisterClassEx(&pWcex);
}

Window::Configuration::~Configuration() noexcept 
{
	UnregisterClass(pClass, GetInstance());
}

const char* Window::Configuration::GetName() noexcept
{	
	return pName;
}

const char* Window::Configuration::GetClass() noexcept
{
	return pClass;
}

HINSTANCE Window::Configuration::GetInstance() noexcept
{
	return pHINST;
}
#pragma endregion

Window::Window(int width, int height) : pWidth(width), pHeight(height)
{
	RECT wr{};
	SetPosition(&wr);
	Initialize(wr);
}

Window::~Window()
{
	DestroyWindow(pHWND);
}

void Window::SetPosition(RECT* wr)
{
	wr->left = 100;
	wr->right = pWidth + wr->left;
	wr->top = 100;
	wr->bottom = pHeight + wr->top;
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

	pHWND = CreateWindow(pConfiguration.GetClass(), pConfiguration.GetName(),
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, x, y,
		pWidth, pHeight, nullptr, nullptr, pConfiguration.GetInstance(), this);
	if (!pHWND)
	{
		//TODO: Throw exception
		MessageBox(0, "Error.", 0, 0);
		PostQuitMessage(0);
		return;
	}

	ShowWindow(pHWND, SW_SHOW);
}

HWND Window::GetHWND() noexcept
{
	return pHWND;
}

void Window::ChangeName(const std::string& name) noexcept
{
	if (SetWindowText(pHWND, name.c_str()) == 0)
	{
		//TODO: Throw exception
	}
}

void Window::Resize(int width, int height) noexcept
{
	pWidth = width;
	pHeight = height;

	RECT wr{};
	SetPosition(&wr);

	MoveWindow(pHWND, wr.left, wr.top, pWidth, pHeight, TRUE);
}

std::optional<int> Window::ProcessMessage()
{
	MSG msg;

	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
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

LRESULT CALLBACK Window::HandleProcess(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	if (msg == WM_NCCREATE)
	{
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
		Window* const pWnd = static_cast<Window*>(pCreate->lpCreateParams);
		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::HandleMessageThunk));
		return pWnd->HandleMessage(hWnd, msg, wParam, lParam);
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT CALLBACK Window::HandleMessageThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	Window* const pWnd = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	return pWnd->HandleMessage(hWnd, msg, wParam, lParam);
}

LRESULT Window::HandleMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	switch (msg)
	{
		case WM_CLOSE:
		{
			PostQuitMessage(0);
			break;
		}

		case WM_SIZE:
		{
			RedrawWindow(pHWND, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			return 0;
		}
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}