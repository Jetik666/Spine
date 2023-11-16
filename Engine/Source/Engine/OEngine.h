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

	void ENGINE_API SetMode(EngineModes mode) noexcept;
	EngineModes ENGINE_API GetMode() noexcept;
	std::wstring ENGINE_API EngineModeToString() noexcept;
}

using namespace EngineMode;
class ENGINE_API OEngine 
{
	/* Constructor */
public:
	OEngine() noexcept;
	~OEngine() noexcept;
	
	/* Private Variables */
private:
	EngineModes m_EngineMode;

	/* Getters and Setters */
public:
	EngineModes GetEngineMode() const noexcept;
	void SetEngineMode(EngineModes mode) noexcept;
};

