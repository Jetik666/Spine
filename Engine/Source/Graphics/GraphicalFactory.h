#pragma once

namespace Graphic
{
	enum InputType : int
	{
		D3D11_t = 0,
		D3D12_t = 1,
		OpenGL_t = 2
	};

	class GraphicalFactory
	{
	public:
		static std::unique_ptr<GraphicalInput> SetInput(InputType type, HWND hWnd) noexcept;
	};
}

