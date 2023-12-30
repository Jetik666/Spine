#pragma once
#include <chrono>
#include <mutex>

namespace Time
{
	class FrameRateController
	{
		/* Constructor */
	public:
		FrameRateController() noexcept;
		~FrameRateController() noexcept = default;

		/* Public methods */
	public:
		void StartFrame() noexcept;
		void EndFrame() noexcept;
		void Sleep(std::mutex& renderMutex) const noexcept;
		bool UpdateInforamtion() noexcept;

		/* Private variables */
	private:
		uint16_t m_Limit;
		float m_LimitTime;

		std::chrono::steady_clock::time_point m_BeginFrame;
		std::chrono::steady_clock::time_point m_EndFrame;

		std::chrono::steady_clock::time_point m_Point;
		uint16_t m_FrameRate;
		float m_FrameTime;

		/* Getters and Setters */
	public:
		uint16_t Limit() const noexcept { return m_Limit; }
		void Limit(uint16_t value) noexcept;

		float TimeLimit() const noexcept { return m_LimitTime; }

		uint16_t FrameRate() const noexcept { return m_FrameRate; }
		float Time() const noexcept { return m_FrameTime; }
	};
}

