#pragma once
#include <chrono>

namespace Test
{
	/* Frames Counter */
	class FrameCounter
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
		unsigned short m_FramesAmount;
		float m_FrameTime;

		std::chrono::steady_clock::time_point m_Peek;

		/* Getters and Setters */
	public:
		unsigned short FramesLimit() const noexcept { return m_FramesLimit; }
		void FramesLimit(unsigned short value) noexcept;

		unsigned short FramesAmount() const noexcept { return m_FramesAmount; }

		float FrameTime() const noexcept { return m_FrameTime; }
	};
}
