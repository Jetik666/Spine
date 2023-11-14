#pragma once

class ENGINE_API OEngine;

namespace EngineMode 
{
	enum EngineModes : INT 
	{
		NONE,
		DEBUG,
		RELEASE,
		EDITOR,
		SERVER
	};

	extern OEngine g_Engine;

	void ENGINE_API SetMode(EngineModes mode);
	EngineModes ENGINE_API GetMode();
	std::wstring ENGINE_API EngineModeToString();
}

using namespace EngineMode;
class ENGINE_API OEngine 
{
	/* Constructor */
public:
	OEngine();
	~OEngine();
	
	/* Private Variables */
private:
	EngineModes m_EngineMode;

	/* Getters and Setters */
public:
	EngineModes GetEngineMode() const noexcept;
	void SetEngineMode(EngineModes mode) noexcept;
};

