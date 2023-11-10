#include "Engine.h"
#include <fstream>
#include <string>
#include <shlobj_core.h>

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

	MessageBox(0, LogDirectory().c_str(), 0, 0);
	OutputDebugString(buffer);



	std::wfstream outfile;
	//outfile.open(std::wstring(LogDirectory() + L"/" + LogFile()), std::ios_base::app);
}

std::wstring Logger::LogDirectory()
{
	wchar_t path[1024];
	wchar_t* appDataLocal;
	SHGetKnownFolderPath(FOLDERID_RoamingAppData, 0, nullptr, &appDataLocal);
	wcscpy_s(path, sizeof(path) / sizeof(path[0]), appDataLocal);
	wcscat_s(path, L"\\Jetik\\");
	wcscat_s(path, PerGameSettings::GameName());
	CreateDirectory(path, NULL);
	wcscat_s(path, L"\\Log");
	CreateDirectory(path, NULL);
	return path;
}

std::wstring Logger::LogFile()
{
	wchar_t file[1024];
	wcscpy_s(file, PerGameSettings::GameName());
	wcscpy_s(file, PerGameSettings::BootTime());
	wcscat_s(file, L".log");
	return file;
}
