#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <functional>

#include "InputEngine.h"

#include "Utils.h"
#include "StringGraphics.h"

struct Size {
	int width;
	int height;
};

struct Coord {
	int x; // column
	int y; // row
};

struct Padding {
	float top = 0;
	float right = 0;
	float bottom = 0;
	float left = 0;
};

class Label {
public:
	enum Align {
		LEFT = 0,
		CENTER = 1,
		RIGHT = 2
	};

	std::vector<std::string> text;
	Label(std::string content, Size size, Align align, Padding pad = {0, 0, 0, 0});


};

class Button {

public:
	enum Align {
		LEFT = 0,
		CENTER = 1,
		RIGHT = 2
	};
	static int global_id;

	int id;
	std::vector<std::string> button;
	std::vector<std::string> buttonActive;
	Coord position;
	bool inside = false;
	std::function<void()> callback;

	Button(Label content, Coord pos, char border = '+', char active = '.');
	Button(Label content, Coord pos, std::function<void()> callback, char border = '+', char active = '.');
	void start();
};

namespace GUI {



}
