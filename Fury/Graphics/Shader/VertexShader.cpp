#include "VertexShader.h"

bool VertexShader::Initialize(ComPtr<ID3D11Device> &device, std::string shaderpath, D3D11_INPUT_ELEMENT_DESC *layout, UINT numElements) {
	HRESULT hr = D3DReadFileToBlob(StringConverter::StringToWide(shaderpath).c_str(), buffer.GetAddressOf());
	if (FAILED(hr)) {
		std::string errMsg = "Failed to load shader: ";
		errMsg += shaderpath;
		ErrorLogger::Log(hr, errMsg);
		return false;
	}

	hr = device->CreateVertexShader(buffer->GetBufferPointer(), buffer->GetBufferSize(), nullptr, shader.GetAddressOf());
	if (FAILED(hr)) {
		std::string errMsg = "Failed to create Vertex Shader: ";
		errMsg += shaderpath;
		ErrorLogger::Log(hr, errMsg);
		return false;
	}

	hr = device->CreateInputLayout(layout, numElements, buffer->GetBufferPointer(), buffer->GetBufferSize(), inputLayout.GetAddressOf());
	if (FAILED(hr)) {
		ErrorLogger::Log(hr, "Failed to create InputLayout");
		return false;
	}
	OutputDebugStringA("Success.\n");
	return true;
}

ID3D11VertexShader *VertexShader::GetShader() {
	return shader.Get();
}

ID3DBlob *VertexShader::GetBuffer() {
	return buffer.Get();
}

ID3D11InputLayout *VertexShader::GetInputLayout() {
	return inputLayout.Get();
}