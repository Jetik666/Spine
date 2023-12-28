#include "Engine.h"
#include "OpenGL.h"

OpenGL::OpenGL(HWND hWnd) noexcept
	:
	m_HWND(hWnd)
{
	Logger::PrintLog(L"OpenGL - Create\n");

	if (!glfwInit())
	{
		return;
	}

	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),  // size of this pfd 
		1,                              // version number 
		PFD_DRAW_TO_WINDOW |            // support window 
		PFD_SUPPORT_OPENGL |            // support OpenGL 
		PFD_DOUBLEBUFFER,               // double buffered 
		PFD_TYPE_RGBA,                  // RGBA type 
		24,                             // 24-bit color depth 
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

	m_HDC = GetDC(m_HWND);
	int pixelFormat = ChoosePixelFormat(m_HDC, &pfd);
	if (pixelFormat == 0)
	{
		// Handle error: ChoosePixelFormat failed
	}

	BOOL success = SetPixelFormat(m_HDC, pixelFormat, &pfd);
	if (!success)
	{
		// Handle error: SetPixelFormat failed
	}

	m_hOGLRenderContext = wglCreateContext(m_HDC);
	wglMakeCurrent(m_HDC, m_hOGLRenderContext);
	glViewport(0, 0, 600, 800);
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
	ReleaseDC(m_HWND, m_HDC);
}

void OpenGL::Update(float red, float green, float blue) noexcept
{
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void OpenGL::Render()
{
	//glfwPollEvents();
	SwapBuffers(m_HDC);
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

