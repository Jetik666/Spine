#pragma once

#include "Engine.h"

#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <dxgi1_6.h>
#include <memory>
#include <random>
#include <vector>
#include <wrl.h>

class DirectX_11
{
	/* Constructor */
public:
	DirectX_11(HWND hWnd) noexcept;
	DirectX_11(const DirectX_11&) = delete;
	DirectX_11& operator=(const DirectX_11&) = delete;
	~DirectX_11() noexcept;

	/* Public methods */
public:
	void BeginFrame(float red, float green, float blue) noexcept;
	void EndFrame();
	void DrawIndexed(uint32_t count) noexcept(!DEBUG);
	void SetProjection(DirectX::FXMMATRIX proj) noexcept;
	DirectX::XMMATRIX GetProjection() const noexcept;
	void TurnOffVsync() noexcept;

	/* Private variables */
private:
	uint8_t m_VSync = 1;

	DirectX::XMMATRIX m_Projection;

	Microsoft::WRL::ComPtr<ID3D11Device> m_Device;
	Microsoft::WRL::ComPtr<IDXGISwapChain> m_Swap;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_Context;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_Target;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_DSV;
};