#pragma once

#include <Windows.h>
#include <d3d11.h>
#include <dxgi1_6.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <vector>
#include <memory>
#include <random>

class ENGINE_API Graphics
{
	/* Constructor */
public:
	Graphics(HWND hWnd) noexcept;
	~Graphics() noexcept;
	
	/* Public methods */
public:
	void BeginFrame(float red, float green, float blue) noexcept;
	void EndFrame();
	void DrawIndexed(UINT count) noexcept(!DEBUG);
	void SetProjection(DirectX::FXMMATRIX proj) noexcept;
	DirectX::XMMATRIX GetProjection() const noexcept;
	void TurnOffVsync() noexcept;

	/* Private variables */
private:
	unsigned int m_VSync = 1;

	DirectX::XMMATRIX pProjection;

	ComPointer<ID3D11Device> pDevice;
	ComPointer<IDXGISwapChain3> pSwap;
	ComPointer<ID3D11DeviceContext> pContext;
	ComPointer<ID3D11RenderTargetView> pTarget;
	ComPointer<ID3D11DepthStencilView> pDSV;

};
