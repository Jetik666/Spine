#pragma once
#include <string>

// Singleton logger class
class ENGINE_API Logger
{
public:
	Logger();
	~Logger();

public:
	static Logger* Instance() { return inst; }
	static void PrintLog(const wchar_t* fmt, ...);
private:
	static std::wstring LogDirectory();
	static std::wstring LogFile();

private:
	static Logger* inst;
};

