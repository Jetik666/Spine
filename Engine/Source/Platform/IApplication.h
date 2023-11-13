#pragma once

class ENGINE_API IApplication
{
public:
	IApplication();
	virtual ~IApplication() {};

public:
	virtual int Initialize() = 0;
	virtual void Update() = 0;
private:
	virtual void SetupGameSettings() = 0;
};

