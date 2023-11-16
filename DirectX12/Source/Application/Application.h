#pragma once
#include "Engine/Simulation.h"
#include "Common/Time/FrameCounter.h"

namespace Windows 
{
	class Application : public TestEngine::Simulation
	{
		/* Constructor */
	public:
		Application();
		~Application();

		/* Public functions */
	public:
		void Initialize();
		
		/* Private functions */
	private:
		void SetupSettings();
		void Update();

		/* Private variables */
	private:
		FrameCounter m_FrameCounter;
	};
}
