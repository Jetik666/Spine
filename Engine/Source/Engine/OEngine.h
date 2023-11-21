#pragma once
#include <map>

class ENGINE_API OEngine;

namespace EngineMode  
{
	enum Mode : INT 
	{
		NONE,
		DEBUG,
		RELEASE,
		EDITOR,
		SERVER
	};

	extern OEngine g_Engine;

	void ENGINE_API SetMode(Mode mode) noexcept;
	Mode ENGINE_API GetMode() noexcept;
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
	Mode m_EngineMode;

	/* Getters and Setters */
public:
	Mode GetEngineMode() const noexcept;
	void SetEngineMode(Mode mode) noexcept;
};

