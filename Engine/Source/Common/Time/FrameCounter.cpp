#include "Engine.h"
#include "FrameCounter.h"

FrameCounter::FrameCounter() noexcept
	: m_FramesLimit(300)
	, m_FrameLimitTime(static_cast<float>(1.0f / (float)m_FramesLimit))
	, m_FramesAmount(0)
	, m_FrameTime(std::chrono::duration<float>::zero())
	, m_Peek(std::chrono::steady_clock::now())
{}

FrameCounter::~FrameCounter() noexcept {}

bool FrameCounter::ShowFrame() noexcept
{
	std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
	if (m_FrameLimitTime <= std::chrono::duration<float>(currentTime - m_Peek).count())
	{
		m_FrameTime = currentTime - m_Peek;
		m_FramesAmount = static_cast<unsigned short>(1.0 / m_FrameTime.count());
		m_Peek = currentTime;

		return true;
	}
	return false;
}

unsigned short FrameCounter::GetFramesLimit() const noexcept
{
	return m_FramesLimit;
}

void FrameCounter::SetFramesLimit(unsigned short value) noexcept
{
	m_FramesLimit = value;
	m_FrameLimitTime = static_cast<float>(1.0f / (float)m_FramesLimit);
}

unsigned short FrameCounter::GetFramesAmount() const noexcept
{
	return m_FramesAmount;
}

float FrameCounter::GetFrameTime() const noexcept
{
	return m_FrameTime.count();
}