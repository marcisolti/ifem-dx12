#include "Common.h"
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <cstdarg>

void Egg::Internal::Assert(bool trueMeansOk, const char * msgOnFail, ...) {
	va_list argList;
	va_start(argList, msgOnFail);

	if(!trueMeansOk) { 
		std::string buffer;
		buffer.resize(1024);
		/*
		vsprintf_s:
		v: takes a va_list (variadic arg list)
		s: writes to string
		printf
		_s: secure, takes buffer size as argument
		*/
		vsprintf_s(&(buffer.at(0)), 1024, msgOnFail, argList);
		MessageBoxA(NULL, buffer.c_str(), "Assertion failed!", MB_ICONSTOP | MB_OK);
		exit(-1);
	}

	va_end(argList);
}


Egg::Internal::HResultTester::HResultTester(const char * msg, const char * file, int line, ...) :
	message{ msg }, file{ file }, line{ line } {
	va_list l;
	va_start(l, line);
	va_copy(args, l);
	va_end(l);

}

void Egg::Internal::HResultTester::operator<<(HRESULT hr) {
	if(FAILED(hr)) {
		std::ostringstream oss;
		oss << file << "(" << line << "): " << message;
		std::string buffer;
		buffer.resize(1024);

		vsprintf_s(&(buffer.at(0)), 1024, oss.str().c_str(), args);
		va_end(args);

		MessageBoxA(NULL, buffer.c_str(), "Error!", MB_ICONSTOP | MB_OK);
		exit(-1);
	}
	va_end(args);
}