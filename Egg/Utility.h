#pragma once

#include "Common.h"

namespace Egg {

	namespace Utility {

		/*
		Takes a number and returns its closest multiplicative of 256. The returned number is always bigger or equal than the input number
		*/
		constexpr unsigned int Align256(unsigned int v) {
			return (v + 255U) & (~255U);
		}

		/*
		Prints a Blob's content as string to the Visual Studio Output window, if the blob is null, a message will still appear
		*/
		void DebugPrintBlob(com_ptr<ID3DBlob> blob);

		/*
		formats a wide string into a std::wstring
		*/
		std::wstring WFormat(const wchar_t * format, ...);

		/*
		Prints a widechar printf-like message to the Visual Studio Output window
		*/
		void WDebugf(const wchar_t * format, ...);

		/*
		Prints a printf-like message to the Visual Studio Output window
		*/
		void Debugf(const char * format, ...);

		/*
		Queries the available video adapters from the OS
		*/
		void GetAdapters(IDXGIFactory5 * dxgiFactory, std::vector<com_ptr<IDXGIAdapter1>> & adapters);

	}

}
