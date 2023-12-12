#pragma once
#include <string>

namespace Time 
{
	/* Get current time in string format */
	std::wstring GetTime(bool stripped = false) noexcept;
	/* Get current date in string format */
	std::wstring GetDate(bool stripped = false) noexcept;
	/* Get current date and time in string format */
	std::wstring GetDateTime(bool stripped = false) noexcept;
};

