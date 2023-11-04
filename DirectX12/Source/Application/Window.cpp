#include "pch.h"
#include "Window.h"

Window::Window(int width, int height)
{
	LoadString(HInstance(), IDS_PERGAMENAME, pTitle, MAX_NAME_STRING);
	LoadString(HInstance(), IDS_WINDOWCLASS, pClass, MAX_NAME_STRING);
	pWidth = width;
	pHeight = height;
	pIcon = LoadIcon(HInstance(), MAKEINTRESOURCE(IDI_MAINICON));
	Create();
	Initialize();
}

Window::~Window()
{
	UnregisterClass(pClass, pInstance);
}

void Window::Create()
{
	pWcex.cbSize = sizeof(WNDCLASSEX);
	pWcex.style = CS_HREDRAW | CS_VREDRAW;
	pWcex.cbClsExtra = 0;
	pWcex.cbWndExtra = 0;
	pWcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	pWcex.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
	pWcex.hIcon = pIcon;
	pWcex.hIconSm = pIcon;
	pWcex.lpszClassName = pClass;
	pWcex.lpszMenuName = nullptr;
	pWcex.hInstance = HInstance();
	pWcex.lpfnWndProc = HandleMessage;

	RegisterClassEx(&pWcex);
}

void Window::Initialize()
{
	HWND hWnd = CreateWindow(pClass, pTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, pWidth, pHeight, nullptr, nullptr, HInstance(), nullptr);
	if (!hWnd)
	{
		//throw new Exception;
		PostQuitMessage(0);
		return;
	}

	ShowWindow(hWnd, SW_SHOW);
}

LRESULT CALLBACK Window::HandleMessage(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, message, wparam, lparam);
}

WNDCLASSEX Window::GetWindowClass()
{
	return pWcex;
}

HWND Window::GetHWND()
{
	return pHWND;
}