#pragma once

class D3D12 : public GraphicalInput
{
	/* Constructor */
public:
	D3D12(HWND hWnd) noexcept;
	~D3D12() noexcept;;

	/* Operators */
public:
	void* operator new(std::size_t size);
	void operator delete(void* ptr);

	/* Public methods */
public:
	void Initialize(HWND hWnd) noexcept override;
	void Reset() noexcept override;

	void Update(float red, float green, float blue) noexcept override;
	void Render() override;

	void ToggleVSync(bool turnOn) noexcept override;
};

