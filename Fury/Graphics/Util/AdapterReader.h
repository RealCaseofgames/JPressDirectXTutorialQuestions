#pragma once

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "DirectXTK.lib")
#pragma comment(lib, "DXGI.lib")

#include "../../Util/ErrorLogger.h"

#include <d3d11.h>
#include <wrl/client.h>
#include <vector>

using namespace Microsoft::WRL;

class AdapterData {
public:
	AdapterData(IDXGIAdapter *pAdapter);
	IDXGIAdapter *pAdapter;
	DXGI_ADAPTER_DESC desc;
};

class AdapterReader {
public:
	static std::vector<AdapterData> GetAdapters();
private:
	static std::vector<AdapterData> adapters;
};