#pragma once

#include <DirectXMath.h>
#include <DirectXColors.h>

#include "Util/AdapterReader.h"
#include "Shader/VertexShader.h"
#include "Shader/PixelShader.h"

using namespace Microsoft::WRL;
using namespace DirectX;
using namespace DirectX::Colors;

class Graphics {
public:
	bool Initialize(HWND hwnd, int width, int height);
	void Render();
private:
	bool InitializeDirectX(HWND hwnd, int width, int height);
	bool InitializeShaders();
	bool InitializeScene();

	ComPtr<ID3D11Device> device;
	ComPtr<ID3D11DeviceContext> devcon;
	ComPtr<IDXGISwapChain> swapchain;
	ComPtr<ID3D11RenderTargetView> rtv;
	ComPtr<ID3D11Buffer> vertexBuffer;

	VertexShader vertexShader;
	PixelShader pixelShader;
};