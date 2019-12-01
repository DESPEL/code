#pragma once

#include <vector>
#include <string>

namespace Graphics {

	std::vector<std::string> makeRect(int width, int height, char ch = '+', bool fill = false);
	std::string makeLine(int len, char fill);
}

