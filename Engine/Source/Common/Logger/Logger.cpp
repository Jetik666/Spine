#include "Engine.h"
#include <fstream>

Logger* Logger::inst;

Logger::Logger()
{
	inst = this;
}

Logger::~Logger()
{
}

void Logger::PrintLog(const wchar_t* fmt, ...)
{
	wchar_t buffer[4096];
	va_list args;

	va_start(args, fmt);
	vswprintf_s(buffer, fmt, args);
	va_end(args);

	MessageBox(0, buffer, 0, 0);
}
