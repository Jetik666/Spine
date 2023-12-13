#pragma once
#include <chrono>

namespace Time
{
	class FrameRateController
	{
		/* Constructor */
	public:
		FrameRateController() noexcept;
		~FrameRateController() noexcept;

		/* Public methods */
	public:
		bool ShowFrame() noexcept;

		/* Private variables */
	private:
		uint16_t m_Limit;
		float m_LimitTime;
		uint16_t m_Amount;
		float m_Time;

		std::chrono::steady_clock::time_point m_Peek;

		/* Getters and Setters */
	public:
		uint16_t Limit() const noexcept { return m_Limit; }
		void Limit(uint16_t value) noexcept;

		uint16_t Amount() const noexcept { return m_Amount; }

		float Time() const noexcept { return m_Time; }
	};
}

