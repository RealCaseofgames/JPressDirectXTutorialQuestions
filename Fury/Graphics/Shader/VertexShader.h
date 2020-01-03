#pragma once

#pragma comment(lib, "d3dcompiler.lib")

#include "../../Util/ErrorLogger.h"

#include <d3d11.h>
#include <wrl/client.h>
#include <d3dcompiler.h>

using namespace Microsoft::WRL;

class VertexShader {
public:
	bool Initialize(ComPtr<ID3D11Device> &device, std::string shaderpath, D3D11_INPUT_ELEMENT_DESC *layout, UINT numElements);
private:
	ComPtr<ID3D11VertexShader> shader;
	ComPtr<ID3DBlob> buffer;
	ComPtr<ID3D11InputLayout> inputLayout;
public:
	ID3D11VertexShader *GetShader();
	ID3DBlob *GetBuffer();
	ID3D11InputLayout *GetInputLayout();
};