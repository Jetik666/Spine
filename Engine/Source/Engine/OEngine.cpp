#include "Engine.h"

namespace Engine
{
	OEngine g_Engine;
	void ENGINE_API SetMode(EngineMode mode)
	{
		g_Engine.SetEngineMode(mode);
	}
	EngineMode ENGINE_API GetMode()
	{
		g_Engine.GetEngineMode();
	}
	std::wstring ENGINE_API EngineModeToString()
	{
		switch (Engine::GetMode())
		{
		case EngineMode::DEBUG:		return L"Debug";
		case EngineMode::RELEASE:	return L"Release";
		case EngineMode::EDITOR:	return L"Editor";
		case EngineMode::SERVER:	return L"Server";
		default:					return L"None";
		}
	}
}

OEngine::OEngine()
{
#ifdef _DEBUG
	m_EngineMode = EngineMode::DEBUG;
#else
	m_EngineMode = EngineMode::RELEASE;
#endif // _DEBUG

}

OEngine::~OEngine() {}

EngineMode OEngine::GetEngineMode() const noexcept
{
	return m_EngineMode;
}

void OEngine::SetEngineMode(EngineMode mode) noexcept
{
	m_EngineMode = mode;
}
