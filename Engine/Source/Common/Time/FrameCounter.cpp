#include "Engine.h"
#include "FrameCounter.h"


FrameCounter::FrameCounter() noexcept
	: m_FramesAmount(0)
	, m_FrameTime(std::chrono::duration<float>::zero())
	, m_Peek(std::chrono::steady_clock::now())
{}

FrameCounter::~FrameCounter() noexcept {}

void FrameCounter::Mark() noexcept
{
	std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
	m_FrameTime = currentTime - m_Peek;
	m_FramesAmount = static_cast<short>(1 / m_FrameTime.count());
	m_Peek = currentTime;
}

bool FrameCounter::ShowFrame() noexcept
{
	std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
	if (static_cast<float>(1) / m_FramesLimit <= std::chrono::duration<float>(currentTime - m_Peek).count())
	{
		return true;
	}
	return false;
}

unsigned short FrameCounter::GetFramesLimit() noexcept
{
	return m_FramesLimit;
}

void FrameCounter::SetFramesLimit(unsigned short value) noexcept
{
	m_FramesLimit = value;
}

unsigned short FrameCounter::GetFramesAmount() noexcept
{
	return m_FramesAmount;
}

float FrameCounter::GetFrameTime() noexcept
{
	return m_FrameTime.count();
}