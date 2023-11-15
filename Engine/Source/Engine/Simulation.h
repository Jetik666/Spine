#pragma once

#include "Platform/Win32/IApplication.h"

namespace TestEngine 
{
	class ENGINE_API Simulation : public IApplication 
	{
		/* Constructor */
	public:
		Simulation();
		~Simulation();

		/* Public functions */
	public:
		virtual void PreInitialize() override;
	};
}

