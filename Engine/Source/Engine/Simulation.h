#pragma once

#include "Platform/Win32/IApplication.h"

namespace TestEngine 
{
	class ENGINE_API Simulation : public Win32::IApplication 
	{
		/* Constructor */
	public:
		Simulation() noexcept;
		~Simulation() noexcept;

		/* Public functions */
	public:
		virtual void PreInitialize() noexcept override;
		void SetTitle(const wchar_t* title) const noexcept;
	};
}

