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
				ReadArgument(key.c_str());
			}
		}
	}

	void ReadArgument(const wchar_t* argument) noexcept
	{
		if (wcscmp(argument, L"mtail") == 0)
		{
			Logger::StartMtail();
			return;
		}
		if (wcscmp(argument, L"debug") == 0)
		{
			EngineMode::SetMode(EngineMode::EngineModes::DEBUG);
			return;
		}
		if (wcscmp(argument, L"editor") == 0)
		{
			EngineMode::SetMode(EngineMode::EngineModes::EDITOR);
			return;
		}
		if (wcscmp(argument, L"server") == 0)
		{
			EngineMode::SetMode(EngineMode::EngineModes::SERVER);
			return;
		}
	}
}
