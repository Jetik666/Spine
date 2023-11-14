#include "Engine.h"

ApplicationSettings* ApplicationSettings::inst;

ApplicationSettings::ApplicationSettings()
	: m_GameName(L"undefined"), m_ShortName(L"undefined"), m_BootTime(L"undefined"), m_MainIcon(NULL)
{
	inst = this;

	wcscpy_s(inst->m_GameName, L"undefined");
	wcscpy_s(inst->m_ShortName, L"undefined");
	wcscpy_s(inst->m_BootTime, Time::GetDateTime(true).c_str());
}

ApplicationSettings::~ApplicationSettings() {}