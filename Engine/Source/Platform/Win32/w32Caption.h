#pragma once

constexpr int CB_CLOSE = 0;
constexpr int CB_MINIMIZE = 1;
constexpr int CB_MAXIMIZE = 2;

namespace Win32
{
	class ENGINE_API Caption
	{
	public:
		struct CaptionButton
		{
			const wchar_t* Text = L"X";
			
			int Command = -1;
			int Width = 50;
			RECT Rect;

			CaptionButton(const wchar_t* text, int command, int width = 50)
			{
				Text = text;
				Command = command;
				Width = width;
				Rect = RECT {0, 0, 0, 0};
			}
		};

		/* Private variables */
	private:
		bool m_ShowTitle = true;
		std::list<CaptionButton*> m_CaptionButtons;

		/* Getters and setters */
	public:
		bool ShowTitle() const noexcept { return m_ShowTitle; }
		void ShowTitle(bool show) noexcept { m_ShowTitle = show; }
		void AddCaptionButton(CaptionButton* button);
		std::list<CaptionButton*> CaptionButtons() { return m_CaptionButtons; }
	};
}

