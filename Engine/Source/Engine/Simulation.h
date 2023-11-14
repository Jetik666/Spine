#pragma once

#include "Platform/IApplication.h"

namespace TestEngine 
{
	class ENGINE_API Simulation : public Win32::IApplication 
	{
		/* Constructor */
	public:
		Simulation();
		~Simulation();
	};
}

