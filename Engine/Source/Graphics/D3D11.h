#pragma once

#include "Engine.h"

#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <dxgi1_6.h>
#include <memory>
#include <random>
#include <wrl.h>

class D3D11 : public GraphicalInput
{
	/* Constructor */
public:
	D3D11(HWND hWnd) noexcept;
	~D3D11() noexcept;

	/* Operators */
public:
	void* operator new(std::size_t size);

	/* Public methods */
public:
	void BeginFrame(float red, float green, float blue) noexcept;
	void EndFrame();
	void DrawIndexed(uint32_t count) noexcept(!DEBUG);
	void SetProjection(DirectX::FXMMATRIX proj) noexcept;
	DirectX::XMMATRIX GetProjection() const noexcept;

	void Initialize(HWND hWnd) noexcept override;
	void Update(float red, float green, float blue) noexcept override;
	void Render() override;

	void ToggleVSync(bool turnOn) noexcept override;

	/* Private variables */
private:
	DirectX::XMMATRIX m_Projection;

	Microsoft::WRL::ComPtr<ID3D11Device> m_Device;
	Microsoft::WRL::ComPtr<IDXGISwapChain> m_Swap;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_Context;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_Target;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_DSV;
};