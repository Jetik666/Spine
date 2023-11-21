#pragma once

// Singleton game settings
class ENGINE_API ApplicationSettings 
{
	/* Constructor */
public:
	ApplicationSettings() noexcept;
	~ApplicationSettings() noexcept;

	/* Singleton */
public:
	static ApplicationSettings* Instance() noexcept { return inst; }
private:
	static ApplicationSettings* inst;

	/* Private variables */
private:
	wchar_t m_GameName[MAX_NAME_STRING];
	wchar_t m_ShortName[MAX_NAME_STRING];
	HICON m_MainIcon;
	wchar_t m_BootTime[MAX_NAME_STRING];
	wchar_t m_SplashURL[MAX_NAME_STRING];

	/* Getters and Setters */
public:
	static wchar_t* GameName() noexcept { return inst->m_GameName; }
	static void SetGameName(unsigned int id) noexcept { LoadString(HInstance(), id, inst->m_GameName, MAX_NAME_STRING); }

	static wchar_t* ShortName() noexcept { return inst->m_ShortName; }
	static void SetShortName(unsigned int id) noexcept { LoadString(HInstance(), id, inst->m_ShortName, MAX_NAME_STRING); }

	static HICON MainIcon() noexcept { return inst->m_MainIcon; }
	static void SetMainIcon(unsigned int id) noexcept { LoadIcon(HInstance(), MAKEINTRESOURCE(id)); }

	static wchar_t* BootTime() noexcept { return inst->m_BootTime; }

	static wchar_t* SplashURL() noexcept { return inst->m_SplashURL; }
	static void SetSplashURL(unsigned int id) noexcept { LoadString(HInstance(), id, inst->m_SplashURL, MAX_NAME_STRING); }
};

