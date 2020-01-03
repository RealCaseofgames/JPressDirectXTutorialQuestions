#pragma once

#pragma comment(lib, "d3dcompiler.lib")

#include "../../Util/ErrorLogger.h"

#include <d3d11.h>
#include <wrl/client.h>
#include <d3dcompiler.h>

using namespace Microsoft::WRL;

class PixelShader {
public:
	bool Initialize(ComPtr<ID3D11Device> &device, std::string shaderpath);
private:
	ComPtr<ID3D11PixelShader> shader;
	ComPtr<ID3DBlob> buffer;
public:
	ID3D11PixelShader *GetShader();
	ID3DBlob *GetBuffer();
};