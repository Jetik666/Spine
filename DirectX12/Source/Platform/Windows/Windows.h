#pragma once

#include <string>
#include <optional>

class Window
{
private:
	class Configuration
	{
		/* Constructor */
	public:
		Configuration() noexcept;
		~Configuration() noexcept;

		/* Private variables */
	private:
		wchar_t m_Class[MAX_NAME_STRING];
		wchar_t m_Name[MAX_NAME_STRING];

		WNDCLASSEX m_Wcex{};

		HINSTANCE m_hInst;

		/* Getters */
	public:
		const wchar_t* Name() noexcept;
		const wchar_t* Class() noexcept;
		HINSTANCE Instance() noexcept;
	};

public:
	Window(int width, int height);
	~Window();

public:
	void Resize(int width, int height) noexcept;
	std::optional<int> ProcessMessage();

private:
	void SetPosition(RECT* wr);
	void Initialize(RECT wr);

	static LRESULT CALLBACK HandleMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;

	/* Private variables */
private:
	Configuration m_Configuration;
	int m_Width;
	int m_Height;
	HWND m_HWND;

	/* Getters and Setters */
public:
	HWND GetHWND() noexcept;
	void SetTitle(const wchar_t* title) noexcept;
};

