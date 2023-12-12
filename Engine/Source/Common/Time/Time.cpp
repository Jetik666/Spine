#include "Engine.h"
#include <ctime>
#include <sstream>
#include <iomanip>

namespace Time
{
	std::wstring GetTime(bool stripped) noexcept
	{
		time_t now = time(0);
		tm ltm;
		localtime_s(&ltm, &now);
		std::wstringstream wss;
		wss << std::put_time(&ltm, L"%T");

		std::wstring timeString = wss.str();

		if (stripped)
		{
			std::wstring chars = L":";
			for (wchar_t c : chars)
			{
				timeString.erase(std::remove(timeString.begin(), timeString.end(), c), timeString.end());
			}
		}

		return timeString;
	}

	std::wstring GetDate(bool stripped) noexcept
	{
		time_t now = time(0);
		tm ltm;
		localtime_s(&ltm, &now);
		std::wstringstream wss;
		wss << std::put_time(&ltm, L"%d/%m/%y");
		std::wstring timeString = wss.str();

		if (stripped) 
		{
			std::wstring chars = L"/";
			for (wchar_t c : chars)
			{
				timeString.erase(std::remove(timeString.begin(), timeString.end(), c), timeString.end());
			}
		}

		return timeString;
	}

	std::wstring GetDateTime(bool stripped) noexcept
	{
		std::wstring timeString = GetDate(stripped) + L" " + GetTime(stripped);

		if (stripped) 
		{
			std::wstring chars = L" ";
			for (wchar_t c : chars) 
			{
				timeString.erase(std::remove(timeString.begin(), timeString.end(), c), timeString.end());
			}
		}

		return timeString;
	}
};
