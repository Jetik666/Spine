#pragma once
#pragma warning(push)
#pragma warning(disable: 4251)

#include <Windows.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <wrl.h>
#include <vector>
#include <memory>
#include <random>

class ENGINE_API Graphics
{
	/* Constructor */
public:
	Graphics();
	~Graphics();
	
	/* Public methods */
public:
	void Initialize(HWND hWnd) noexcept;
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

	Microsoft::WRL::ComPtr<ID3D11Device> pDevice;
	Microsoft::WRL::ComPtr<IDXGISwapChain> pSwap;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> pContext;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pTarget;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> pDSV;


};
#pragma warning(pop)
