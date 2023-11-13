#pragma once

// Singleton game settings
class ENGINE_API ApplicationSettings
{
	/* Constructor */
public:
	ApplicationSettings();
	~ApplicationSettings();

	/* Singleton */
public:
	static ApplicationSettings* Instance() { return inst; }
private:
	static ApplicationSettings* inst;

private:
	/* Private variables */

	wchar_t m_GameName[MAX_NAME_STRING];
	wchar_t m_ShortName[MAX_NAME_STRING];
	HICON m_MainIcon;
	wchar_t m_BootTime[MAX_NAME_STRING];

public:
	/* Getters and Setters */
	static wchar_t* GameName() { return inst->m_GameName; }
	static void SetGameName(UINT id) { LoadString(HInstance(), id, inst->m_GameName, MAX_NAME_STRING); }

	static wchar_t* ShortName() { return inst->m_ShortName; }
	static void SetShortName(UINT id) { LoadString(HInstance(), id, inst->m_ShortName, MAX_NAME_STRING); }

	static HICON MainIcon() { return inst->m_MainIcon; }
	static void SetMainIcon(UINT id) { LoadIcon(HInstance(), MAKEINTRESOURCE(id)); }

	static wchar_t* BootTime() { return inst->m_BootTime; }
};

