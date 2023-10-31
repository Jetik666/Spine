#pragma once

class IApplication
{
public:
	IApplication();
	virtual ~IApplication() = 0;
public:
	virtual void Initialize() = 0;
	virtual void Update() = 0;
};
