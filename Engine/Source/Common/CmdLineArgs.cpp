#include "Engine.h"
#include "CmdLineArgs.h"
#include <algorithm>

namespace CmdLineArgs
{
	void ReadArguments() noexcept
	{
		int argc = 0;
		LPWSTR* argv = CommandLineToArgvW(GetCommandLineW(), &argc);

		for (int i = 1; i < argc; ++i)
		{
			std::wstring key = argv[i];
			if (key[0] == '-')
			{
				key.erase(0, 1);
				std::transform(key.begin(), key.end(), key.begin(), ::tolower);
				ReadArgument(key);
			}
		}
	}

	void ReadArgument(std::wstring argument) noexcept
	{
		if (argument == L"mtail")
		{
			Logger::StartMtail();
		}
		else if (argument == L"debug")
		{
			EngineMode::SetMode(EngineMode::Mode::DEBUG);
		}
		else if (argument == L"editor")
		{
			EngineMode::SetMode(EngineMode::Mode::EDITOR);
		}
		else if (argument == L"server")
		{
			EngineMode::SetMode(EngineMode::Mode::SERVER);
		}
		else
		{
			Logger::PrintLog(L"Unknown argument: %s.", argument.c_str());
		}
	}
}
