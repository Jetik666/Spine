#pragma once
constexpr int CB_CLOSE = 0;
constexpr int CB_MINIMIZE = 1;
constexpr int CB_MAXIMIZE = 2;

namespace Win32
{
	class ENGINE_API Caption
	{
	public:
		struct Button
		{
			const wchar_t* Text = L"X";

			int Command = -1;
			int Width = 50;
			RECT Rect;

			Button(const wchar_t* text, int command, int width = 50)
			{
				Text = text;
				Command = command;
				Width = width;
				Rect = RECT { 0, 0, 0, 0 };
			}
		};
	public:
		Caption() noexcept { m_Buttons = Array::DynamicArray<Button*>(); }

		/* Private variables */
	private:
		bool m_ShowTitle = true;
		Array::DynamicArray<Button*> m_Buttons;

		/* Getters and setters */
	public:
		bool ShowTitle() const noexcept { return m_ShowTitle; }
		void ShowTitle(bool show) noexcept { m_ShowTitle = show; }
		void AddButton(Button* button) noexcept;
		Array::DynamicArray<Button*> Buttons() const noexcept { return m_Buttons; }
	};
}
