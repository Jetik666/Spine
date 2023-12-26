#include "Engine.h"
#include "OpenGL.h"

OpenGL::OpenGL(HWND hWnd) noexcept
{
	Logger::PrintLog(L"OpenGL - Create\n");
}

OpenGL::~OpenGL() noexcept
{
}

void* OpenGL::operator new(std::size_t size)
{
	void* ptr = ::operator new(size);

	return ptr;
}

void OpenGL::operator delete(void* ptr)
{
	::operator delete(ptr);
}

void OpenGL::Initialize(HWND hWnd) noexcept
{
	Logger::PrintLog(L"OpenGL\n");
}

void OpenGL::Reset() noexcept
{
}

void OpenGL::Update(float red, float green, float blue) noexcept
{
}

void OpenGL::Render()
{
}

void OpenGL::ToggleVSync(bool turnOn) noexcept
{
	if (turnOn)
	{
		GraphicalInput::VSync(1);
	}
	else
	{
		GraphicalInput::VSync(0);
	}
}

