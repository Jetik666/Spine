#pragma once

class OpenGL : public GraphicalInput
{
	/* Constructor */
public:
	OpenGL(HWND hWnd) noexcept;
	~OpenGL() noexcept;;

	/* Operators */
public:
	void* operator new(std::size_t size);

	/* Public methods */
public:
	void Initialize(HWND hWnd) noexcept override;
	void Update(float red, float green, float blue) noexcept override;
	void Render() override;

	void ToggleVSync(bool turnOn) noexcept override;
};

