#include "pch.h"
#include "Window.h"

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
	pWcex.lpfnWndProc = HandleMessage;

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
	Initialize();
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
}

void Window::Initialize()
{
	HWND hWnd = CreateWindow(pConfiguration.GetClass(), pConfiguration.GetName(), 
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, 
		pWidth, pHeight, nullptr, nullptr, pConfiguration.GetInstance(), this);
	if (!hWnd)
	{
		//TODO: Throw exception;
		MessageBox(0, "Error.", 0, 0);
		PostQuitMessage(0);
		return;
	}

	ShowWindow(hWnd, SW_SHOW);
}

HWND Window::GetHWND() noexcept
{
	return pHWND;
}

void Window::ChangeName(std::string name) noexcept
{
	if (SetWindowText(pHWND, name.c_str()) == 0)
	{
		//TODO: Throw exception
	}
}

void Window::Resize(int width, int height) noexcept
{

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