#pragma once

class Window
{
public:
	Window(int width, int height);
	~Window();

public:
	static LRESULT CALLBACK HandleMessage(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam);
	WNDCLASSEX GetWindowClass();
	HWND GetHWND();

private:
	void Create();
	void Initialize();

private:
	WCHAR pClass[MAX_NAME_STRING];
	WCHAR pTitle[MAX_NAME_STRING];

	HICON pIcon;

	int pWidth;
	int pHeight;

	WNDCLASSEX pWcex{};
	HWND pHWND;
	HINSTANCE pInstance;
};

