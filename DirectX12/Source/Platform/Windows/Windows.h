#pragma once

#include <string>
#include <optional>

class Window
{
private:
	class Configuration
	{
	public:
		/* Constructor */
		Configuration() noexcept;
		~Configuration() noexcept;

	private:
		/* Private variables */
		wchar_t m_Class[MAX_NAME_STRING];
		wchar_t m_Name[MAX_NAME_STRING];

		WNDCLASSEX m_Wcex{};

		HINSTANCE m_hInst;

	public:
		/* Getters */
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

	static LRESULT CALLBACK HandleProcess(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	static LRESULT HandleMessageThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	LRESULT HandleMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;

private:
	/* Private variables */
	Configuration m_Configuration;
	int m_Width;
	int m_Height;
	HWND m_HWND;

public:
	/* Getters and Setters */
	HWND GetHWND() noexcept;
	void SetTitle(const wchar_t* title) noexcept;
};

