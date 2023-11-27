#include "Engine.h"
#include "w32Caption.h"

namespace Win32
{
	void Caption::AddButton(Button* button) noexcept
	{
		m_Buttons.Push(button);
	}
}