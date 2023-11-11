#pragma once
#include <string>

// Singleton logger class
class ENGINE_API Logger
{
	/* Constructor */
public:
	Logger();
	~Logger();

	/* Singleton */
public:
	static Logger* Instance() { return inst; }
private:
	static Logger* inst;

public:
	/* Print to Log File */
	static void PrintLog(const wchar_t* fmt, ...);
	static std::wstring LogDirectory();
	static std::wstring LogFile();

	/* Print a line of '-' char's */
	static void PrintDebugSeparator();
	/* Start Mtail Application */
	static void StartMtail();
private:
	/* Check to see if MTail is already running */
	static bool IsMTailRunning();

};

