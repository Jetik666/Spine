#pragma once
#include <map>

class ENGINE_API OEngine;

namespace EngineMode  
{
	enum Mode : int 
	{
		NONE,
		DEBUG,
		RELEASE,
		EDITOR,
		SERVER
	};

	extern OEngine g_Engine;

	void SetMode(Mode mode) noexcept;
	Mode GetMode() noexcept;
	std::wstring EngineModeToString() noexcept;
}

using namespace EngineMode;
class OEngine 
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

