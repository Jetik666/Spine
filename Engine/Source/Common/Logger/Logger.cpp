#include "Engine.h"
#include <cstdio>
#include <fstream>
#include <string>
#include <shlobj_core.h>
#include <TlHelp32.h>

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

	OutputDebugString(buffer);

	std::wfstream outfile;
	outfile.open(std::wstring(LogDirectory() + L"/" + LogFile()), std::ios_base::app);

	if (outfile.is_open())
	{
		std::wstring s = buffer;
		outfile << L"[" << Time::GetDateTime() << L"] " << s;
		outfile.close();
		OutputDebugString(s.c_str());
	}
	else
	{
		MessageBox(NULL, L"Unable to open log file...", L"Log Error", MB_OK);
	}
}

std::wstring Logger::LogDirectory()
{
	wchar_t path[1024];
	wchar_t* appDataLocal;
	SHGetKnownFolderPath(FOLDERID_RoamingAppData, 0, nullptr, &appDataLocal);
	wcscpy_s(path, sizeof(path) / sizeof(path[0]), appDataLocal);
	wcscat_s(path, L"\\Jetik");
	CreateDirectory(path, NULL);
	wcscat_s(path, L"\\");
	wcscat_s(path, PerGameSettings::GameName());
	CreateDirectory(path, NULL);
	wcscat_s(path, L"\\Log");
	CreateDirectory(path, NULL);
	return path;
}

std::wstring Logger::LogFile()
{
	wchar_t file[1024];
	MessageBox(0, PerGameSettings::GameName(), 0, 0);
	wcscpy_s(file, PerGameSettings::GameName());
	wcscat_s(file, PerGameSettings::BootTime());
	wcscat_s(file, L".log");
	file[1023] = '\0';
	return std::wstring(file);
}

void Logger::PrintDebugSeparator()
{
	std::wstring s = L"\n------------------------------------------------------------------------------------\n\n";

#ifdef _DEBUG
	std::wfstream outfile;
	outfile.open(std::wstring(LogDirectory() + L"/" + LogFile()), std::ios_base::app);

	if (outfile.is_open())
	{
		outfile << s;
		outfile.close();
	}
	else
	{
		MessageBox(NULL, L"Unable to open log file...", L"Log Error", MB_OK);
	}
#endif
}

bool Logger::IsMTailRunning()
{
	bool exists = false;
	PROCESSENTRY32 entry {};
	entry.dwSize = sizeof(PROCESSENTRY32);

	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	if (Process32First(snapshot, &entry))
		while (Process32Next(snapshot, &entry))
			if (!_wcsicmp(entry.szExeFile, L"mTAIL.exe"))
				exists = true;

	CloseHandle(snapshot);
	return exists;
}

void Logger::StartMtail()
{
	if (IsMTailRunning())
	{
		Logger::PrintLog(L"--MTail failed to start - Already running\n");
		return;
	}

	Logger::PrintLog(L"--Starting MTail\n");
	wchar_t path[MAX_PATH] = { 0 };
	GetCurrentDirectoryW(MAX_PATH, path);
	std::wstring url = path + std::wstring(L"/mTAIL.exe");
	std::wstring params = L" \"" + LogDirectory() + L"/" + LogFile() + L"\" /start";
	ShellExecute(0, NULL, url.c_str(), params.c_str(), NULL, SW_SHOWDEFAULT);
}
