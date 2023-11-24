#include "Engine.h"
#include "Window.h"

constexpr DWORD DCX_USESTYLE = 0x00010000;

namespace Win32 
{
	Window::Window(const wchar_t* title, HICON hIcon, WindowType type) noexcept
		: Win32::SubObject(title, title, hIcon)
		, m_Type(type)
	{
		Size(DEFAULTWIDTH, DEFAULTHEIGHT);

		size_t nameLength = wcslen(title) + 1;
		m_Name = (wchar_t*)malloc(nameLength * sizeof(wchar_t));
		if (m_Name != NULL)
		{
			wcscpy_s(m_Name, nameLength, title);
		}

		Running(true);
	}

	Window::~Window() noexcept 
	{
		UnregisterClass(m_Class, HInstance());
		free(m_Name);
	}

	void Window::Initialize() noexcept 
	{
		RECT desktop;
		const HWND hDesktop = GetDesktopWindow();
		GetWindowRect(hDesktop, &desktop);

		RECT R = { 0, 0, Size().cx, Size().cy};
		AdjustWindowRect(&R, m_Type, false);
		int width = R.right - R.left;
		int height = R.bottom - R.top;

		m_Handle = CreateWindow(m_Class, m_Title, m_Type, 
			((desktop.right / 2) - (Size().cx / 2)), ((desktop.bottom / 2) - (Size().cy / 2)),
			Size().cx, Size().cy, 0, 0, HInstance(), (void*)this);
		if (!m_Handle) 
		{
			DWORD error = GetLastError();
			std::wstring errorMessage = L"Failed to create window! Error code: " + std::to_wstring(error);
			MessageBox(0, errorMessage.c_str(), 0, 0);
			PostQuitMessage(0);
			return;
		}

		ShowWindow(m_Handle, SW_SHOW);
		UpdateWindow(m_Handle);

		m_Graphics.Initialize(Handle());
		Graphics().SetProjection(DirectX::XMMatrixPerspectiveLH(1.0f, 3.0f / 4.0f, 0.5f, 40.0f));
	}

	LRESULT Window::MessageHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) noexcept
	{
		switch (message)
		{
			case WM_NCCREATE:
			{
				OnNonClientCreate();
				return TRUE;
			}
			case WM_NCACTIVATE:
			{
				OnNonClientActivate(LOWORD(wParam) != WA_INACTIVE);
				return TRUE;
			}
			case WM_NCPAINT:
			{
				OnNonClientPaint((HRGN)wParam);
				return FALSE;
			}
			case WM_NCLBUTTONDOWN:
			{
				OnNonClientLeftMouseButtonDown();
				break;
			}
			case WM_NCLBUTTONDBLCLK:
			{
				Utils::MaximizeWindow(Handle());
				return 0;
			}

			case WM_GETMINMAXINFO:
			{
				OnGetMinMaxInfo((MINMAXINFO*)lParam);
				return 0;
			}
			case WM_EXITSIZEMOVE:
			{
				OnExitSizeMove();
				break;
			}

			case WM_PAINT: 
			{
				OnPaint();
				break;
			}

			case WM_TIMER:
			{
				RedrawWindow();
				break;
			}
		}

		return SubObject::MessageHandler(hWnd, message, wParam, lParam);
	}

	void Window::OnNonClientCreate() noexcept
	{
		SetTimer(Handle(), 1, 100, NULL);
		SetWindowTheme(Handle(), L"", L"");
		Utils::ModifyClassStyle(Handle(), 0, CS_DROPSHADOW);

		Caption::AddCaptionButton(new CaptionButton(L"X", CB_CLOSE));
		Caption::AddCaptionButton(new CaptionButton(L"🗖", CB_MAXIMIZE));
		Caption::AddCaptionButton(new CaptionButton(L"🗕", CB_MINIMIZE));
	}

	void Window::OnNonClientActivate(bool active) noexcept
	{
		Active(active);
	}

	void Window::OnNonClientPaint(HRGN region) const noexcept
	{
		// Start section
		HDC hdc = GetDCEx(Handle(), region, DCX_WINDOW | DCX_INTERSECTRGN | DCX_USESTYLE);

		RECT rect {};
		GetWindowRect(Handle(), &rect);

		SIZE m_Size = SIZE { rect.right - rect.left, rect.bottom - rect.top };

		HBITMAP hbmMem = CreateCompatibleBitmap(hdc, m_Size.cx, m_Size.cy);
		HANDLE hOld = SelectObject(hdc, hbmMem);

		// Draw section
		HBRUSH brush = CreateSolidBrush(RGB(46, 46, 46));

		RECT newRect = RECT { 0, 0, m_Size.cx, m_Size.cy };

		FillRect(hdc, &newRect, brush);
		DeleteObject(brush);

		if (Active() && !Utils::IsWindowFullscreen(Handle()))
		{
			brush = CreateSolidBrush(RGB(100, 100, 100));
			FrameRect(hdc, &newRect, brush);
		}

		PaintCaption(hdc);

		DeleteObject(brush);

		// End draw section
		BitBlt(hdc, 0, 0, m_Size.cx, m_Size.cy, hdc, 0, 0, SRCCOPY);

		SelectObject(hdc, hOld);
		DeleteObject(hbmMem);

		ReleaseDC(Handle(), hdc);
	}

	void Window::RedrawWindow() const noexcept
	{
		SetWindowPos(Handle(), 0, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_DRAWFRAME | SWP_FRAMECHANGED); // reset window
		SendMessage(Handle(), WM_PAINT, 0, 0);
	}

	void Window::PaintCaption(HDC hdc) const noexcept
	{
		RECT rect {};
		GetWindowRect(Handle(), &rect);

		SIZE m_Size = SIZE { rect.right - rect.left, rect.bottom - rect.top };

		if (ShowTitle())
		{
			rect = RECT { 8, 0, m_Size.cx, 30 };

			SetBkMode(hdc, TRANSPARENT);
			SetTextColor(hdc, Active() ? RGB(255, 255, 255) : RGB(92, 92, 92));
			// DT_VCENTER - Vertical Center;
			// DT_LEFT - Horizontal Left;
			DrawText(hdc, Name(), static_cast<int>(wcslen(Name())), &rect, DT_SINGLELINE | DT_VCENTER | DT_LEFT);
		}

		int offset = 0;
		POINT pt;
		GetCursorPos(&pt);
		GetWindowRect(Handle(), &rect);

		pt.x -= rect.left;
		pt.y -= rect.top;

		LONG style = GetWindowLong(Handle(), GWL_STYLE);
		for (auto& button : Caption::CaptionButtons())
		{
			offset += button->Width;
			button->Rect = RECT { m_Size.cx - offset, 0, m_Size.cx - offset + button->Width, 30 };

			if (button->Rect.left < pt.x && button->Rect.right > pt.x && button->Rect.top < pt.y && button->Rect.bottom > pt.y)
			{
				HBRUSH brush = CreateSolidBrush(RGB(100, 100, 100));
				FillRect(hdc, &button->Rect, brush);
				DeleteObject(brush);
			}

			if (wcscmp(button->Text, L"🗖") == 0 && Utils::IsWindowFullscreen(Handle()))
			{
				SetWindowLong(Handle(), GWL_STYLE, style & ~WS_SIZEBOX);
				button->Text = L"🗗";
			}
			else if (wcscmp(button->Text, L"🗗") == 0 && !Utils::IsWindowFullscreen(Handle()))
			{
				SetWindowLong(Handle(), GWL_STYLE, style | WS_THICKFRAME);
				button->Text = L"🗖";
			}

			DrawText(hdc, button->Text, static_cast<int>(wcslen(button->Text)), &button->Rect, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
		}
	}

	void Window::OnNonClientLeftMouseButtonDown() noexcept
	{
		int offset = 0;
		POINT pt;
		GetCursorPos(&pt);

		RECT rect {};
		GetWindowRect(Handle(), &rect);

		pt.x -= rect.left;
		pt.y -= rect.top;

		for (auto& button : Caption::CaptionButtons())
		{
			if (button->Rect.left < pt.x && button->Rect.right > pt.x && button->Rect.top < pt.y && button->Rect.bottom > pt.y)
			{
				switch (button->Command)
				{
					case CB_CLOSE:		
					{ 
						SendMessage(Handle(), WM_CLOSE, 0, 0);	
						Running(false);
						break; 
					}
					case CB_MINIMIZE:	
					{ 
						ShowWindow(Handle(), SW_MINIMIZE);
						break; 
					} 
					case CB_MAXIMIZE:	
					{ 
						Win32::Utils::MaximizeWindow(Handle());
						break;
					}
				}
			}
		}
	}

	void Window::OnGetMinMaxInfo(MINMAXINFO* minmax) const noexcept
	{
		RECT WorkArea {};
		SystemParametersInfo(SPI_GETWORKAREA, 0, &WorkArea, 0);
		minmax->ptMaxSize.x = WorkArea.right - WorkArea.left + 5;
		minmax->ptMaxSize.y = WorkArea.bottom - WorkArea.top + 5;
		minmax->ptMaxPosition.x = WorkArea.left;
		minmax->ptMaxPosition.y = WorkArea.top;
		minmax->ptMinTrackSize.x = 400;
		minmax->ptMinTrackSize.y = 300;
	}

	void Window::OnExitSizeMove() const noexcept
	{
		RECT rect {};
		GetWindowRect(Handle(), &rect);
		RECT WorkArea {};
		SystemParametersInfo(SPI_GETWORKAREA, 0, &WorkArea, 0);
		if (rect.top < WorkArea.top + 10 && !Utils::IsWindowFullscreen(Handle()))
		{
			Utils::MaximizeWindow(Handle());
		}
	}

	void Window::OnPaint() const noexcept
	{
		PAINTSTRUCT ps {};
		HDC hdc = BeginPaint(Handle(), &ps);

		RECT rect {};
		GetClientRect(Handle(), &rect);

		HBRUSH brush = CreateSolidBrush(RGB(36, 36, 36));
		FillRect(hdc, &rect, brush);

		DeleteObject(brush);
		EndPaint(Handle(), &ps);
	}

	void Window::Name(wchar_t* name) noexcept
	{
		free(m_Name);
		size_t nameLength = wcslen(name) + 1; 
		m_Name = (wchar_t*)malloc(nameLength * sizeof(wchar_t));
		if (m_Name != NULL)
		{
			wcscpy_s(m_Name, nameLength, name);
		}
	}
	void Window::Name(const wchar_t* name) noexcept
	{
		free(m_Name);
		size_t nameLength = wcslen(name) + 1;
		m_Name = (wchar_t*)malloc(nameLength * sizeof(wchar_t));
		if (m_Name != NULL)
		{
			wcscpy_s(m_Name, nameLength, name);
		}
	}
}