#include "Utility.h"

/*
Only allow 1024 character long mesasges, if your message get cropped consider increasing this number
*/
#define OUTPUT_BUFFER_SIZE 1024

void Egg::Utility::DebugPrintBlob(com_ptr<ID3DBlob> blob) {
	if(blob != nullptr) {
		OutputDebugString(reinterpret_cast<const char*>(blob->GetBufferPointer()));
	} else {
		OutputDebugString("Blob was NULL");
	}
}

std::wstring Egg::Utility::WFormat(const wchar_t * format, ...) {
	va_list va;
	va_start(va, format);
	std::wstring wstr;
	wstr.resize(OUTPUT_BUFFER_SIZE);
	vswprintf_s(&(wstr.at(0)), OUTPUT_BUFFER_SIZE, format, va);
	va_end(va);
	wstr.shrink_to_fit();
	return wstr;
}

// prints a formatted wide string to the VS output window
void Egg::Utility::WDebugf(const wchar_t * format, ...) {
	va_list va;
	va_start(va, format);

	std::wstring wstr;
	wstr.resize(OUTPUT_BUFFER_SIZE);

	vswprintf_s(&(wstr.at(0)), OUTPUT_BUFFER_SIZE, format, va);

	OutputDebugStringW(wstr.c_str());

	va_end(va);
}

// prints a formatted string to the VS output window
void Egg::Utility::Debugf(const char * format, ...) {
	va_list va;
	va_start(va, format);

	std::string str;
	str.resize(OUTPUT_BUFFER_SIZE);

	vsprintf_s(&(str.at(0)), OUTPUT_BUFFER_SIZE, format, va);

	OutputDebugString(str.c_str());

	va_end(va);
}

void Egg::Utility::GetAdapters(IDXGIFactory5 * dxgiFactory, std::vector<com_ptr<IDXGIAdapter1>> & adapters) {
	com_ptr<IDXGIAdapter1> tempAdapter{ nullptr };
	OutputDebugStringW(L"Detected Video Adapters:\n");
	unsigned int adapterId = 0;

	for(HRESULT query = dxgiFactory->EnumAdapters1(adapterId, tempAdapter.GetAddressOf());
		query != DXGI_ERROR_NOT_FOUND;
		query = dxgiFactory->EnumAdapters1(++adapterId, tempAdapter.GetAddressOf())) {

		// check if not S_OK
		DX_API("Failed to query DXGI adapter") query;

		if(tempAdapter != nullptr) {
			DXGI_ADAPTER_DESC desc;
			tempAdapter->GetDesc(&desc);

			WDebugf(L"    %s\n", desc.Description);

			adapters.push_back(std::move(tempAdapter));
			tempAdapter.Reset();
		}
	}
}
