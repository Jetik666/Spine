#pragma once

#include "Definitions.h"

#include "Engine/OEngine.h"

#include "Common/Logger/Logger.h"
#include "Common/Time/Time.h"
#include "Core/ApplicationSettings.h"

#include "Common/Time/FrameRateController.h"

#include "Graphics/GraphicalInput.h"
#include "Graphics/D3D/D3D11.h"
#include "Graphics/D3D/D3D12.h"
#include "Graphics/OpenGL/OpenGL.h"
#include "Graphics/GraphicalFactory.h"

#ifdef WIN32
	#include "Platform/Win32/Win32Utils.h"
	#include "Platform/Win32/SubObject.h"
	#include "Platform/Win32/w32Caption.h"
	#include "Platform/Win32/Window.h"
	#include "Platform/Win32/IApplication.h"
#endif
