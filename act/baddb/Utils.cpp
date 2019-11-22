#include "Utils.h"

namespace utils {
	std::string sanitize(std::string text) {
		for (char& c : text) {
			switch (c) {
			case '�':
				c = 'a';
				break;
			case '�':
				c = 'e';
				break;
			case '�':
				c = 'i';
				break;
			case '�':
				c = 'o';
				break;
			case '�':
				c = 'u';
				break;
			case '�':
				c = 'A';
				break;
			case '�':
				c = 'E';
				break;
			case '�':
				c = 'I';
				break;
			case '�':
				c = 'O';
				break;
			case '�':
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