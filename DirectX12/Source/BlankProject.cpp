#include "BlankProject.h"
#include "Engine/Simulation.h"
#include "Platform/Win32/WinEntry.h"

class BlankProject : public TestEngine::Simulation
{
public:
	BlankProject() {};
	~BlankProject() {};

public:
	void SetupSettings();
	void Initialize() {};
	void Update() {};

private:
};

ENTRYAPP(BlankProject);

void BlankProject::SetupSettings()
{
	ApplicationSettings::SetGameName(IDS_PERGAMENAME);
	ApplicationSettings::SetShortName(IDS_SHORTNAME);
	ApplicationSettings::SetMainIcon(IDI_MAINICON);
}