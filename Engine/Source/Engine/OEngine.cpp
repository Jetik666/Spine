#include "Engine.h"

namespace EngineMode
{
	OEngine g_Engine;

	void SetMode(Mode mode) noexcept 
	{
		g_Engine.SetEngineMode(mode);
	}

	Mode GetMode() noexcept 
	{
		return g_Engine.GetEngineMode();
	}

	std::wstring EngineModeToString() noexcept 
	{
		switch (EngineMode::GetMode()) 
		{
			case Mode::DEBUG:		return L"Debug";
			case Mode::RELEASE:		return L"Release";
			case Mode::EDITOR:		return L"Editor";
			case Mode::SERVER:		return L"Server";
			default:				return L"None";
		}
	}
}

OEngine::OEngine() noexcept 
{
#ifdef _DEBUG
	m_EngineMode = Mode::DEBUG;
#else
	m_EngineMode = EngineMode::RELEASE;
#endif // _DEBUG

}

OEngine::~OEngine() noexcept  {}

Mode OEngine::GetEngineMode() const noexcept 
{
	return m_EngineMode;
}

void OEngine::SetEngineMode(Mode mode) noexcept 
{
	m_EngineMode = mode;
}
