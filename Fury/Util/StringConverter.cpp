#include "StringConverter.h"

std::wstring StringConverter::StringToWide(std::string str) {
	std::wstring rStr(str.begin(), str.end());
	return rStr;
}

std::string StringConverter::WideToString(std::wstring str) {
	std::string rStr(str.begin(), str.end());
	return rStr;
}