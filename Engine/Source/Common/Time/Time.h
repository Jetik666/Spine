#pragma once
#include <string>

namespace Time {
	/* Get current time in string format */
	std::wstring ENGINE_API GetTime(bool stripped = false) noexcept;
	/* Get current date in string format */
	std::wstring ENGINE_API GetDate(bool stripped = false) noexcept;
	/* Get current date and time in string format */
	std::wstring ENGINE_API GetDateTime(bool stripped = false) noexcept;
};

