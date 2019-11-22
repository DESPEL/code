#include "Utils.h"

namespace utils {
	std::string sanitize(std::string text) {
		for (char& c : text) {
			switch (c) {
			case 'á':
				c = 'a';
				break;
			case 'é':
				c = 'e';
				break;
			case 'í':
				c = 'i';
				break;
			case 'ó':
				c = 'o';
				break;
			case 'ú':
				c = 'u';
				break;
			case 'Á':
				c = 'A';
				break;
			case 'É':
				c = 'E';
				break;
			case 'Í':
				c = 'I';
				break;
			case 'Ó':
				c = 'O';
				break;
			case 'Ú':
				c = 'U';
				break;
			}
		}
		return text;
	}
	std::string to_lower(std::string str) {
		for (char& c : str) {
			c = std::tolower(c);
		}
		return str;
	}

	std::string trim(std::string str) {
		bool chi = false;
		std::string rstr = "";
		for (int i = 0; i < str.size(); i++) {
			if (str[i] != ' ' || chi) {
				rstr += std::string(1, str[i]);
				chi = true;
			}
		}
		while (!rstr.empty() && rstr.back() == ' ')
			rstr.pop_back();
		return rstr;
	}
}