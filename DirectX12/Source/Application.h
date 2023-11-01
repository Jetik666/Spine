#pragma once

#include "Platform/WIN32/IApplication.h"

class Application : public IApplication
{
public:
	Application();
	~Application();
public:
	void Initialize();
	void Update();
};
