#include <string>
#include <Windows.h>

#include "path.hpp"

std::string get_current_path() {
	wchar_t buffer[MAX_PATH] = { 0 };
	auto length = GetModuleFileName(NULL, buffer, MAX_PATH);

	std::wstring::size_type pos = std::wstring(buffer).find_last_of(L"\\/");
	const std::wstring wresult = std::wstring(buffer).substr(0, pos);

	std::string result(wresult.begin(), wresult.end());

	return result;
}

std::string combine_paths(const std::string &a, const std::string &b) {
	return a + '\\' + b;
}