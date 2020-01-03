#include "PixelShader.h"

bool PixelShader::Initialize(ComPtr<ID3D11Device> &device, std::string shaderpath) {
	HRESULT hr = D3DReadFileToBlob(StringConverter::StringToWide(shaderpath).c_str(), buffer.GetAddressOf());
	if (FAILED(hr)) {
		std::string errMsg = "Failed to load shader: ";
		errMsg += shaderpath;
		ErrorLogger::Log(hr, errMsg);
		return false;
	}

	hr = device->CreatePixelShader(buffer->GetBufferPointer(), buffer->GetBufferSize(), nullptr, shader.GetAddressOf());
	if (FAILED(hr)) {
		std::string errMsg = "Failed to create Vertex Shader: ";
		errMsg += shaderpath;
		ErrorLogger::Log(hr, errMsg);
		return false;
	}
	OutputDebugStringA("Success.\n");
	return true;
}

ID3D11PixelShader *PixelShader::GetShader() {
	return shader.Get();
}

ID3DBlob *PixelShader::GetBuffer() {
	return buffer.Get();
}