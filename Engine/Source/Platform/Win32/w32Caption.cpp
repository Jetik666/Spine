#include "Engine.h"
#include "w32Caption.h"

namespace Win32
{
	void Caption::AddCaptionButton(CaptionButton* button)
	{
		m_CaptionButtons.push_back(button);
	}
}