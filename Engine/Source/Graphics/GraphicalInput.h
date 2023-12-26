#pragma once

class GraphicalInput
{
	/* Public methods */
public:
	virtual void Initialize(HWND hWnd) noexcept = 0;
	virtual void Update(float red, float green, float blue) noexcept = 0;
	virtual void Render() = 0;

	virtual void ToggleVSync(bool turnOn) noexcept = 0;

	/* Private variables */
private:
	uint8_t m_VSync = 1;

	/* Getters and Setters */
public:
	uint8_t VSync() const noexcept { return m_VSync; }
	bool VSyncIsOn() const noexcept { return m_VSync == 1 ? true : false; }
	void VSync(uint8_t value) noexcept { m_VSync = value; }
};

