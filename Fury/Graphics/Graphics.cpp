#include "Graphics.h"
#include "Geometry/Vertex.h"

bool Graphics::Initialize(HWND hwnd, int width, int height) {
	bool ret = true;

	ret &= InitializeDirectX(hwnd, width, height);
	ret &= InitializeShaders();
	ret &= InitializeScene();

	return ret;
}

void Graphics::Render() {
	devcon->OMSetRenderTargets(1, rtv.GetAddressOf(), nullptr);
	devcon->ClearRenderTargetView(rtv.Get(), Blue);

	devcon->IASetInputLayout(vertexShader.GetInputLayout());
	devcon->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_LINELIST);

	devcon->VSSetShader(vertexShader.GetShader(), NULL, 0);
	devcon->PSSetShader(pixelShader.GetShader(), NULL, 0);

	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	devcon->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &stride, &offset);

	devcon->Draw(3, 0);
	swapchain->Present(1, 0);
}

bool Graphics::InitializeDirectX(HWND hwnd, int width, int height) {
	std::vector<AdapterData> adapters = AdapterReader::GetAdapters();

	IDXGIAdapter *pUsedAdapter = adapters[0].pAdapter;
	UINT usedIndex = 0;
	UINT memSize = 0;

	if (adapters.size() < 1) {
		ErrorLogger::Log("No DXGI Adapters found.");
		return false;
	}
	

	DXGI_SWAP_CHAIN_DESC scd;
	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

	scd.BufferCount = 1;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferDesc.Height = height;
	scd.BufferDesc.RefreshRate.Numerator = 60;
	scd.BufferDesc.RefreshRate.Denominator = 1;
	scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	scd.BufferDesc.Width = width;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	scd.OutputWindow = hwnd;
	scd.SampleDesc.Count = 1;
	scd.SampleDesc.Quality = 0;
	scd.Windowed = true;

	UINT flags = 0;

#ifdef _DEBUG
	flags = D3D11_CREATE_DEVICE_DEBUG;
#endif

	HRESULT hr = D3D11CreateDeviceAndSwapChain(
		pUsedAdapter,
		D3D_DRIVER_TYPE_UNKNOWN,
		NULL,
		flags,
		NULL,
		0,
		D3D11_SDK_VERSION,
		&scd,
		swapchain.GetAddressOf(),
		device.GetAddressOf(),
		NULL,
		devcon.GetAddressOf());

	if (FAILED(hr)) {
		ErrorLogger::Log(hr, "Failed to create D3D11 Device and DXGI Swap Chain");
		return false;
	}

	ComPtr<ID3D11Texture2D> backBuffer;

	hr = swapchain->GetBuffer(0, IID_PPV_ARGS(backBuffer.GetAddressOf()));
	if (FAILED(hr)) {
		ErrorLogger::Log(hr, "Could not get back buffer");
		return false;
	}

	hr = device->CreateRenderTargetView(backBuffer.Get(), NULL, rtv.GetAddressOf());
	if (FAILED(hr)) {
		ErrorLogger::Log(hr, "Could not create Render Target View.");
	}

	devcon->OMSetRenderTargets(1, rtv.GetAddressOf(), nullptr);

	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(viewport));

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = width;
	viewport.Height = height;
	viewport.MinDepth = 0;
	viewport.MaxDepth = 1;

	devcon->RSSetViewports(1, &viewport);

	return true;
}

bool Graphics::InitializeShaders() {
	std::string shaderFolder;
#pragma region DetertmineShaderPath
	if (IsDebuggerPresent() == TRUE) {
#ifdef _DEBUG
#ifdef _WIN64
		shaderFolder = "../x64/Debug/";
#else
		shaderFolder = "../Debug/";
#endif // _WIN64
#else
#ifdef _WIN64
		shaderFolder = "../x64/Release/";
#else
		shaderFolder = "../Release/";
#endif // _WIN64
#endif // _DEBUG
	}

	D3D11_INPUT_ELEMENT_DESC layout[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	UINT numElements = ARRAYSIZE(layout);

	bool ret = true;
	ret &= vertexShader.Initialize(device, shaderFolder + "VertexShader.cso", layout, numElements);
	ret &= pixelShader.Initialize(device, shaderFolder + "PixelShader.cso");

	return ret;
}

bool Graphics::InitializeScene() {
	Vertex v[] = {
		Vertex(-1, -1),
		Vertex(1, -1),
		Vertex(0, 1)
	};

	D3D11_BUFFER_DESC vbDesc;
	ZeroMemory(&vbDesc, sizeof(vbDesc));

	vbDesc.Usage = D3D11_USAGE_DEFAULT;
	vbDesc.ByteWidth = sizeof(Vertex) * ARRAYSIZE(v);
	vbDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbDesc.CPUAccessFlags = 0;
	vbDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA vbData;
	ZeroMemory(&vbData, sizeof(vbData));
	vbData.pSysMem = v;

	HRESULT hr = device->CreateBuffer(&vbDesc, &vbData, vertexBuffer.GetAddressOf());
	if (FAILED(hr)) {
		ErrorLogger::Log(hr, "Failed to create Vertex Buffer.");
		return false;
	}

	if (vertexBuffer.Get() != nullptr) {
		OutputDebugStringA("Success.\n");
	}

	return true;
}