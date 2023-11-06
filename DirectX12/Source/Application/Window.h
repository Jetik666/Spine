#pragma once

#include <string>

class Window
{
private:
	class Configuration
	{
	public:
		Configuration() noexcept;
		~Configuration() noexcept;
		
	public:
		const char* GetName() noexcept;
		const char* GetClass() noexcept;
		HINSTANCE GetInstance() noexcept;

	private:
		char pClass[MAX_NAME_STRING];
		char pName[MAX_NAME_STRING];

		WNDCLASSEX pWcex{};

		HINSTANCE pHINST;
	};

public:
	Window(int width, int height);
	~Window();

public:
	void ChangeName(std::string name) noexcept;
	void Resize(int width, int height) noexcept;

	HWND GetHWND() noexcept;

private:
	void SetPosition(RECT* wr);
	void Initialize();

	static LRESULT CALLBACK HandleMessage(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam);

private:
	Configuration pConfiguration;
	int pWidth;
	int pHeight;
	HWND pHWND;
};

