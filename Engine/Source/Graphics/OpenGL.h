#pragma once
#include "Graphics/GLFW/glfw3.h"

class OpenGL : public GraphicalInput
{
	/* Constructor */
public:
	OpenGL(HWND hWnd) noexcept;
	~OpenGL() noexcept;;

	/* Operators */
public:
	void* operator new(std::size_t size);
	void operator delete(void* ptr);

	/* Public methods */
public:
	void Initialize(HWND hWnd) noexcept override;
	void Reset() noexcept override;

	void Update(float red, float green, float blue) noexcept override;
	void Render() override;

	void ToggleVSync(bool turnOn) noexcept override;

	/* Private variable */
private:
	HDC m_HDC;
	HGLRC m_hOGLRenderContext;
};

