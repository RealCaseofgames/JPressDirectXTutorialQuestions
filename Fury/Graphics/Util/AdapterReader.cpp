#include "AdapterReader.h"

std::vector<AdapterData> AdapterReader::adapters;

std::vector<AdapterData> AdapterReader::GetAdapters() {
	if (adapters.size() > 0)
		return adapters;

	ComPtr<IDXGIFactory> pFactory;

	HRESULT hr = CreateDXGIFactory(IID_PPV_ARGS(pFactory.GetAddressOf()));
	if (FAILED(hr)) {
		ErrorLogger::Log(hr, "Failed to create DXGIFactory to enumerate adapters.");
		exit(-1);
	}

	IDXGIAdapter *pAdapter;
	UINT index = 0;
	while (SUCCEEDED(pFactory->EnumAdapters(index, &pAdapter))) {
		adapters.push_back(AdapterData(pAdapter));
		index++;
	}

	return adapters;
}

AdapterData::AdapterData(IDXGIAdapter *pAdapter) {
	this->pAdapter = pAdapter;
	HRESULT hr = pAdapter->GetDesc(&desc);
	if (FAILED(hr)) {
		ErrorLogger::Log(hr, "Failed to get description for IDXGIAdapter");
	}
}