#include "Engine.h"
#include "GraphicalFactory.h"

namespace Graphic
{
	std::unique_ptr<GraphicalInput> GraphicalFactory::SetInput(InputType type, HWND hWnd) noexcept
	{
		std::unique_ptr<GraphicalInput> input;

		switch (type)
		{
			case InputType::D3D11_t:
			{
				input = std::make_unique<D3D11>(hWnd);
				break;
			}

			case InputType::D3D12_t:
			{
				input = std::make_unique<D3D12>(hWnd);
				break;
			}

			case InputType::OpenGL_t:
			{
				input = std::make_unique<OpenGL>(hWnd);
				break;
			}

			default:
			{
				Logger::PrintLog(L"Can`t switch graphical input.");
				input = std::make_unique<D3D11>(hWnd);
				break;
			}
		}

		return input;
	}
}
