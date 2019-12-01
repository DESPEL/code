#include "StringGraphics.h"

using namespace std;

vector<string> Graphics::makeRect(int width, int height, char ch, bool fill) {
	vector<string> res(height, "");
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (i == 0 || i == height - 1 || j == 0 || j == width - 1 || fill) {
				res[i] += ch;
				continue;
			}
			else {
				res[i] += ' ';
			}
		}
	}
	return res;
}

string Graphics::makeLine(int length, char fill) {
	string ret;
	for (int i = 0; i < length; i++)
		ret += fill;
	return ret;
}