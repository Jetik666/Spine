#include "Engine.h"
#include "FrameRateController.h"

namespace Time
{
	FrameRateController::FrameRateController() noexcept
		: m_Limit(300)
		, m_LimitTime(1.0f / static_cast<float>(m_Limit))
		, m_Amount(0)
		, m_Time(0)
		, m_Peek(std::chrono::steady_clock::now())
	{}

	bool FrameRateController::ShowFrame() noexcept
	{
		std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
		float time = std::chrono::duration<float>(currentTime - m_Peek).count();

		if (m_LimitTime <= time)
		{
			m_Time = time;
			m_Amount = static_cast<uint16_t>(1.0 / m_Time);
			m_Peek = currentTime;
			return true;
		}

		return false;
	}

	void FrameRateController::Limit(uint16_t value) noexcept
	{
		m_Limit = value;
		m_LimitTime = 1.0f / static_cast<float>(m_Limit);
	}
}