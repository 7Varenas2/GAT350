#pragma once
#include <iostream>


namespace neu
{
	std::string ToLower(const std::string& str);
	std::string ToUpper(const std::string& str);
	bool CompareIgnoreCase(std::string& str1, std::string& str2);
}
