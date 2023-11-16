#include "Engine.h"

namespace EngineMode
{
	OEngine g_Engine;

	void ENGINE_API SetMode(EngineModes mode) noexcept 
	{
		g_Engine.SetEngineMode(mode);
	}

	EngineModes ENGINE_API GetMode() noexcept 
	{
		return g_Engine.GetEngineMode();
	}

	std::wstring ENGINE_API EngineModeToString() noexcept 
	{
		switch (EngineMode::GetMode()) {
		case EngineModes::DEBUG:		return L"Debug";
		case EngineModes::RELEASE:	return L"Release";
		case EngineModes::EDITOR:	return L"Editor";
		case EngineModes::SERVER:	return L"Server";
		default:					return L"None";
		}
	}
}

OEngine::OEngine() noexcept 
{
#ifdef _DEBUG
	m_EngineMode = EngineModes::DEBUG;
#else
	m_EngineMode = EngineMode::RELEASE;
#endif // _DEBUG

}

OEngine::~OEngine() {}

EngineModes OEngine::GetEngineMode() const noexcept 
{
	return m_EngineMode;
}

void OEngine::SetEngineMode(EngineModes mode) noexcept 
{
	m_EngineMode = mode;
}
