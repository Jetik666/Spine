#include "Engine.h"
#include "D3D12.h"

D3D12::D3D12(HWND hWnd) noexcept
{
	Logger::PrintLog(L"D3D12 - Create\n");
}

D3D12::~D3D12() noexcept
{
}

void* D3D12::operator new(std::size_t size)
{
	void* ptr = ::operator new(size);

	return ptr;
}

void D3D12::Initialize(HWND hWnd) noexcept
{
	Logger::PrintLog(L"D3D12\n");
}

void D3D12::Update(float red, float green, float blue) noexcept
{

}

void D3D12::Render()
{

}

void D3D12::ToggleVSync(bool turnOn) noexcept
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
