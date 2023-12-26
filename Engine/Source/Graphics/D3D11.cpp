#include "Engine.h"
#include "D3D11.h"

#include <cmath>
#include <sstream>
#include <d3dcompiler.h>

#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"D3DCompiler.lib")

D3D11::D3D11(HWND hWnd) noexcept
{
	Logger::PrintLog(L"D3D11 - Create\n");

	DXGI_SWAP_CHAIN_DESC sd = {};
	sd.BufferDesc.Width = 0;
	sd.BufferDesc.Height = 0;
	sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 0;
	sd.BufferDesc.RefreshRate.Denominator = 0;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 1;
	sd.OutputWindow = hWnd;
	sd.Windowed = TRUE;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = 0;

	UINT swapCreateFlags = 0u;
#ifndef NDEBUG
	swapCreateFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	// For checking results of d3d functions
	HRESULT hr {};

	// Create device and front/back buffers, and swap chain and rendering context
	D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		swapCreateFlags,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&sd,
		&m_Swap,
		&m_Device,
		nullptr,
		&m_Context
	);

	// Gain access to texture subresource in swap chain (back buffer)
	Microsoft::WRL::ComPtr<ID3D11Resource> pBackBuffer;
	m_Swap->GetBuffer(0, __uuidof(ID3D11Resource), &pBackBuffer);
	m_Device->CreateRenderTargetView(pBackBuffer.Get(), nullptr, &m_Target);

	// Create depth stensil state
	D3D11_DEPTH_STENCIL_DESC dsDesc = {};
	dsDesc.DepthEnable = TRUE;
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsDesc.DepthFunc = D3D11_COMPARISON_LESS;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> pDSState;
	m_Device->CreateDepthStencilState(&dsDesc, &pDSState);

	// Bind depth state
	m_Context->OMSetDepthStencilState(pDSState.Get(), 1u);

	// Create depth stensil texture
	Microsoft::WRL::ComPtr<ID3D11Texture2D> pDepthStencil;
	D3D11_TEXTURE2D_DESC descDepth = {};
	descDepth.Width = 800u;
	descDepth.Height = 600u;
	descDepth.MipLevels = 1u;
	descDepth.ArraySize = 1u;
	descDepth.Format = DXGI_FORMAT_D32_FLOAT;
	descDepth.SampleDesc.Count = 1u;
	descDepth.SampleDesc.Quality = 0u;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	m_Device->CreateTexture2D(&descDepth, nullptr, &pDepthStencil);

	// Create view of depth stensil texture
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV = {};
	descDSV.Format = DXGI_FORMAT_D32_FLOAT;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0u;
	m_Device->CreateDepthStencilView(pDepthStencil.Get(), &descDSV, &m_DSV);

	// Bind depth stensil view to OM
	m_Context->OMSetRenderTargets(1u, m_Target.GetAddressOf(), m_DSV.Get());

	// Configure viewport
	D3D11_VIEWPORT vp = {};
	vp.Width = 800.0f;
	vp.Height = 600.0f;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0.0f;
	vp.TopLeftY = 0.0f;
	m_Context->RSSetViewports(1u, &vp);

	m_Projection = DirectX::XMMatrixPerspectiveLH(1.0f, 3.0f / 4.0f, 0.5f, 40.0f);
}

D3D11::~D3D11() noexcept
{
	m_Target.Reset();
	m_DSV.Reset();
	m_Context.Reset();
	m_Swap.Reset();
	m_Device.Reset();
}

void* D3D11::operator new(std::size_t size)
{
	void* ptr = ::operator new(size);

	return ptr;
}

void D3D11::operator delete(void* ptr)
{
	::operator delete(ptr);
}

void D3D11::DrawIndexed(uint32_t count) noexcept(!DEBUG)
{
	m_Context->DrawIndexed(count, 0u, 0u);
}

void D3D11::SetProjection(DirectX::FXMMATRIX proj) noexcept
{
	m_Projection = proj;
}

DirectX::XMMATRIX D3D11::GetProjection() const noexcept
{
	return m_Projection;
}

void D3D11::ToggleVSync(bool turnOn) noexcept
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

void D3D11::Initialize(HWND hWnd) noexcept
{
	Logger::PrintLog(L"D3D11\n");
}

void D3D11::Reset() noexcept
{
	m_Target.Reset();
	m_DSV.Reset();
	m_Context.Reset();
	m_Swap.Reset();
	m_Device.Reset();
}

void D3D11::Update(float red, float green, float blue) noexcept
{
	const float color[] = { red, green, blue, 1.0f };
	m_Context->ClearRenderTargetView(m_Target.Get(), color);
	m_Context->ClearDepthStencilView(m_DSV.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0u);
}

void D3D11::Render()
{
	HRESULT hr;

	// Present:
	// First value - Vsync
	// 0 - off
	// 1 - on
	if (FAILED(hr = m_Swap->Present(GraphicalInput::VSync(), 0u)))
	{
		if (hr == DXGI_ERROR_DEVICE_REMOVED)
		{
			throw m_Device->GetDeviceRemovedReason();
		}
		else
		{
			throw hr;
		}
	}
}
