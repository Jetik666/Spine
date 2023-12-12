#pragma once
#include <string>

// Singleton logger class
class Logger 
{
	/* Constructor */
public:
	Logger() noexcept;
	~Logger() noexcept;

	/* Singleton */
public:
	static Logger* Instance() noexcept { return inst; }
private:
	static Logger* inst;

public:
	/* Print to Log File */
	static void PrintLog(const wchar_t* fmt, ...) noexcept;
	static std::wstring LogDirectory() noexcept;
	static std::wstring LogFile() noexcept;

	/* Print a line of '-' char's */
	static void PrintDebugSeparator() noexcept;
	/* Start Mtail Application */
	static void StartMtail() noexcept;
private:
	/* Check to see if MTail is already running */
	static bool IsMTailRunning() noexcept;
};

