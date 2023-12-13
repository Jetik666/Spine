#pragma once
#include "Engine/Simulation.h"
#include <mutex>

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

	private:
		std::mutex m_RenderThread;
	};
}
