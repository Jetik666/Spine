#include "Engine.h"
#include "FrameRateController.h"

#include <thread>

namespace Time
{
	FrameRateController::FrameRateController() noexcept
		: m_Limit(300)
		, m_LimitTime(1.0f / static_cast<float>(m_Limit))
		, m_BeginFrame(std::chrono::steady_clock::now())
		, m_EndFrame(m_BeginFrame)
		, m_Point(m_BeginFrame)
		, m_FrameRate(0)
		, m_FrameTime(0)
	{}

	void FrameRateController::StartFrame() noexcept
	{
		m_BeginFrame = std::chrono::steady_clock::now();
	}

	void FrameRateController::EndFrame() noexcept
	{
		m_EndFrame = std::chrono::steady_clock::now();
		m_FrameTime = std::chrono::duration<float>(m_EndFrame - m_BeginFrame).count();
		m_FrameRate = static_cast<int>(1 / m_FrameTime);
	}

	void FrameRateController::Sleep(std::mutex renderMutex) const noexcept
	{
		std::unique_lock<std::mutex> lock(renderMutex);

		if (m_FrameTime < m_LimitTime)
		{
			float remainingTimeMilliseconds = m_LimitTime - m_FrameTime;
			std::this_thread::sleep_for(std::chrono::milliseconds((int)remainingTimeMilliseconds));
		}
	}

	bool FrameRateController::UpdateInforamtion() noexcept
	{
		if (std::chrono::duration<float>(m_BeginFrame - m_Point).count() >= 1.5f)
		{
			m_Point = std::chrono::steady_clock::now();
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