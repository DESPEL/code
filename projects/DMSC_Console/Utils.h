#pragma once

#include <Windows.h>

#include <vector>
#include <string>
#include <algorithm>

namespace Utils {
	std::string trim(const std::string);
	std::vector<std::string> split(const std::string, const char delimiter = ' ');
	
	void setPosition(int x, int y);
}
