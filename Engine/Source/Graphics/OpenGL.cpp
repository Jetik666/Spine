#include "Engine.h"
#include "OpenGL.h"

OpenGL::OpenGL(HWND hWnd) noexcept
{
	Logger::PrintLog(L"OpenGL - Create\n");
	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),  // size of this pfd 
		1,                              // version number 
		PFD_DRAW_TO_WINDOW |            // support window 
		PFD_SUPPORT_OPENGL |            // support OpenGL 
		PFD_DOUBLEBUFFER,               // double buffered 
		PFD_TYPE_RGBA,                  // RGBA type 
		32,                             // 24-bit color depth 
		0, 0, 0, 0, 0, 0,               // color bits ignored 
		0,                              // no alpha buffer 
		0,                              // shift bit ignored 
		0,                              // no accumulation buffer 
		0, 0, 0, 0,                     // accum bits ignored 
		32,                             // 32-bit z-buffer     
		0,                              // no stencil buffer 
		0,                              // no auxiliary buffer 
		PFD_MAIN_PLANE,                 // main layer 
		0,                              // reserved 
		0, 0, 0                         // layer masks ignored 
	};

	m_HDC = GetDC(hWnd);
	int pixelFormat = ChoosePixelFormat(m_HDC, &pfd);

	m_hOGLRenderContext = wglCreateContext(m_HDC);
	wglMakeCurrent(m_HDC, m_hOGLRenderContext);

	ReleaseDC(hWnd, m_HDC);
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
	if (!wglDeleteContext(m_hOGLRenderContext))
	{
		// Handle error
	}
}

void OpenGL::Update(float red, float green, float blue) noexcept
{
	glClear(GL_COLOR_BUFFER_BIT);

	SwapBuffers(m_HDC);
}

void OpenGL::Render()
{
	glfwPollEvents();
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

