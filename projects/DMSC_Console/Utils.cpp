#include "Utils.h"

using namespace std;

string Utils::trim(const string str) {
	if (str.empty()) return "";
	int i = 0, j = str.size() - 1;
	while (i < str.size() && str[i] == ' ') i++;
	while (j >= 0 && str[j] == ' ') j--;
	return str.substr(i, j - i + 1);
}

vector<string> Utils::split(const string str, const char delimiter) {
	vector<string> splitted;
	string temp;
	for (const char& c : str)
		if (c == ' ') {
			splitted.push_back(temp);
			temp.clear();
		}
		else
			temp += c;
	splitted.push_back(temp);
	return splitted;
}

void Utils::setPosition(int x, int y) {
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { (SHORT)x, (SHORT)y });
}