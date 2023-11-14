#include "Engine.h"

namespace Engine
{
	OEngine g_Engine;
}

OEngine::OEngine()
{
#ifdef _DEBUG
	m_EngineMode = EngineMode::DEBUG;
#else
	m_EngineMode = EngineMode::RELEASE;
#endif // _DEBUG

}

OEngine::~OEngine()
{
}
