#pragma once
#include "Engine/Simulation.h"
#include "Common/Time/FrameCounter.h"

namespace Windows 
{
	class Application : public TestEngine::Simulation 
	{
		/* Constructor */
	public:
		Application() noexcept;
		~Application() noexcept;

		/* Public functions */
	public:
		void Initialize() noexcept;
		
		/* Private functions */
	private:
		void Update() noexcept;
		void SetupSettings() noexcept;

		/* Private variables */
	private:
		FrameCounter m_FrameCounter;
	};
}
