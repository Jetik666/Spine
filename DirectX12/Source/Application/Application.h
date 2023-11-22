#pragma once
#include "Engine/Simulation.h"
#include "../Time/FrameCounter.h"

namespace Windows 
{
	class Application : public TestEngine::Simulation
	{
		/* Constructor */
	public:
		Application() noexcept;
		~Application() noexcept;

		/* Public methods */
	public:
		void Initialize() noexcept;
		
		/* Private methods */
	private:
		void Update() noexcept;
		void SetupSettings() noexcept;
		void ShowFPS() noexcept;

		/* Private variables */
	private:
		Test::FrameCounter m_FrameCounter;
	};
}
