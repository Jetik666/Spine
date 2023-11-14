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

	void ENGINE_API SetMode(EngineMode mode);
	EngineMode ENGINE_API GetMode();
	std::wstring ENGINE_API EngineModeToString();
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

	/* Getters and Setters */
public:
	EngineMode GetEngineMode() const noexcept;
	void SetEngineMode(EngineMode mode) noexcept;
};

