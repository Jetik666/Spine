#pragma once
#include <chrono>

/* Frames Counter */
class ENGINE_API FrameCounter
{
	/* Constructor */
public:
	FrameCounter() noexcept;
	~FrameCounter() noexcept;

	/* Public methods */
public:
	bool ShowFrame() noexcept;

	/* Private variables */
private:
	unsigned short m_FramesLimit;
	float m_FrameLimitTime;
	std::chrono::duration<float> m_FrameTime;
	unsigned short m_FramesAmount;

	std::chrono::steady_clock::time_point m_Peek;

	/* Getters and Setters */
public:
	unsigned short GetFramesLimit() const noexcept;
	void SetFramesLimit(unsigned short value) noexcept;

	unsigned short GetFramesAmount() const noexcept;

	float GetFrameTime() const noexcept;
};
