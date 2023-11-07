#pragma once

#include <string>
#include <optional>

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
	void ChangeName(const std::string& name) noexcept;
	void Resize(int width, int height) noexcept;
	std::optional<int> ProcessMessage();

	HWND GetHWND() noexcept;

private:
	void SetPosition(RECT* wr);
	void Initialize(RECT wr);

	static LRESULT CALLBACK Handle(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	static LRESULT HandleMessageThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	LRESULT HandleMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;

private:
	Configuration pConfiguration;
	int pWidth;
	int pHeight;
	HWND pHWND;
};

