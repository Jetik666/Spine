#pragma once

#include "Definitions.h"

#include "Engine/OEngine.h"

#include "Common/Logger/Logger.h"
#include "Common/Time/Time.h"
#include "Core/ApplicationSettings.h"

#ifdef WIN32
	#include "Platform/Win32/Win32Utils.h"
	#include "Platform/Win32/SubObject.h"
	#include "Platform/Win32/w32Caption.h"
	#include "Platform/Win32/Window.h"
	#include "Platform/Win32/IApplication.h"
#endif
