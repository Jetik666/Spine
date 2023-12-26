#include "Engine.h"
#include "GraphicalFactory.h"

namespace Graphic
{
	GraphicalInput* GraphicalFactory::SetInput(InputType type, HWND hWnd) noexcept
	{
		switch (type)
		{
			case InputType::D3D11_t:
			{
				return new D3D11(hWnd);
			}

			case InputType::D3D12_t:
			{
				return new D3D12(hWnd);
			}

			case InputType::OpenGL_t:
			{
				return new OpenGL(hWnd);
			}

			default:
			{
				Logger::PrintLog(L"Can`t switch graphical input.");
				return new D3D11(hWnd);
			}
		}
	}
}
