#pragma once

class ENGINE_API OEngine;

namespace Engine
{
	enum EngineMode : INT
	{
		NONE,
		DEBUG,
		RELEASE,
		EDITOR,
		SERVER
	};

	extern OEngine g_Engine;
}

using namespace Engine;
class ENGINE_API OEngine
{
	/* Constructor */
public:
	OEngine();
	~OEngine();
	
	/* Private Variables */
private:
	EngineMode m_EngineMode;
};

