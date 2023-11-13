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
	void Mark() noexcept;
	bool ShowFrame() noexcept;

	/* Private variables */
private:
	unsigned short m_FramesLimit = 300;
	std::chrono::duration<float> m_FrameTime;
	unsigned short m_FramesAmount;

	std::chrono::steady_clock::time_point m_Peek;

	/* Getters and Setters */
public:
	unsigned short GetFramesLimit() noexcept;
	void SetFramesLimit(unsigned short value) noexcept;
	unsigned short GetFramesAmount() noexcept;
	float GetFrameTime() noexcept;
};

