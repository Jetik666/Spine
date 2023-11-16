#include "Engine.h"
#include "FrameCounter.h"

FrameCounter::FrameCounter() noexcept
	: m_FramesLimit(300)
	, m_FrameLimitTime(static_cast<float>(1.0f / (float)m_FramesLimit))
	, m_FramesAmount(0)
	, m_FrameTime(0)
	, m_Peek(0)
{}

FrameCounter::~FrameCounter() noexcept {}

bool FrameCounter::ShowFrame() noexcept 
{
	int64_t currentTime = std::chrono::steady_clock::now().time_since_epoch().count();
	float time = std::chrono::duration<float>(currentTime - m_Peek).count();

	if (m_FrameLimitTime <= time) 
	{
		m_FrameTime = time;
		m_FramesAmount = static_cast<unsigned short>(1.0 / m_FrameTime);
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
	return m_FrameTime;
}