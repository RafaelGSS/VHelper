#pragma once
#include <atlbase.h>
#include <string>
#include <codecvt>


namespace utils {

	inline std::string bstr2Str(BSTR t_source) {
		std::wstring wstr(t_source, SysStringLen(t_source));

		using convert_typeX = std::codecvt_utf8<wchar_t>;
		std::wstring_convert<convert_typeX, wchar_t> converterX;

		return converterX.to_bytes(wstr);
	}

	inline std::wstring string2WStr(const std::string& s)
	{
		int slength = (int)s.length() + 1;
		
		int len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
		
		wchar_t* buf = new wchar_t[len];
		MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
		
		std::wstring r(buf);
		delete[] buf;

		return r;
	}
}