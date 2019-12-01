#include "GUI.h"

using namespace std;


Label::Label(string content, Size size, Align align, Padding padding) {
	int i = 0, splitIdx = 0;
	content = Utils::trim(content);
	vector<string> splittedContent = Utils::split(content);
	text = vector<string>(size.height, Graphics::makeLine(padding.left, ' '));
	for ( ; i < padding.top; i++)
		text[i] = Graphics::makeLine(size.width, ' ');
	for (; i < size.height - padding.bottom; i++) {
		while (true) {
			if (splitIdx >= splittedContent.size()) 
				break;
			if (splittedContent[splitIdx].size() + text[i].size() + padding.right <= size.width) {
				text[i] += splittedContent[splitIdx] + ' ';
				splitIdx++;
			}
			else {
				text[i] += Graphics::makeLine(size.width - text[i].size(), ' ');
				break;
			}
		}
	}
	if (align == Align::CENTER) {
		for (string& s : text) {
			string temp = Utils::trim(s);
			int sidx = size.width / 2 - temp.size() / 2;
			string res = Graphics::makeLine(sidx, ' ') + temp;
			res += Graphics::makeLine(size.width - res.size(), ' ');
			s = res;
		}
	}
	if (align == Align::RIGHT) {
		for (string& s : text) {
			string temp = Utils::trim(s);
			int space = size.width - (temp.size() + padding.right);
			string res = Graphics::makeLine(space, ' ') + temp;
			res += Graphics::makeLine(size.width - res.size(), ' ');
			s = res;
		}
	}
}

int Button::global_id = 0;

Button::Button(Label content, Coord pos, char border, char active) {
	id = global_id++;
	position = pos;
	button = Graphics::makeRect(content.text[0].size() + 2, content.text.size() + 2, border);
	for (int i = 0; i < content.text.size(); i++) {
		for (int j = 0; j < content.text[0].size(); j++) {
			button[i + 1][j + 1] = content.text[i][j];
		}
	}
	buttonActive = button;
	for (string& row : buttonActive)
		for (char& c : row)
			if (c == ' ') c = active;

}


Button::Button(Label content, Coord pos, function<void()> callback, char border, char active) {
	id = global_id++;
	position = pos;
	this->callback = callback;
	button = Graphics::makeRect(content.text[0].size() + 2, content.text.size() + 2, border);
	for (int i = 0; i < content.text.size(); i++) {
		for (int j = 0; j < content.text[0].size(); j++) {
			button[i + 1][j + 1] = content.text[i][j];
		}
	}
	buttonActive = button;
	for (string& row : buttonActive)
		for (char& c : row)
			if (c == ' ') c = active;
	
}

void Button::start() {
	
	function<void()> outside = [this]() {
		Mouse mouse = InputEngine::getInstance()->mouse;
		if (!(mouse.pos.X >= this->position.x && mouse.pos.X <= this->position.x + this->button[0].size() - 1) 
			|| !(mouse.pos.Y >= this->position.y && mouse.pos.Y <= this->position.y + this->button.size() - 1)){
			if (!this->inside)
				return;
			this->inside = false;
			Utils::setPosition(this->position.x, this->position.y);
			int i = 0;
			for (string row : this->button) {
				Utils::setPosition(this->position.x, this->position.y + i);
				cout << row;
				i++;
			}
		}
		
	};
	function<void()> inside = [this]() {
		Mouse mouse = InputEngine::getInstance()->mouse;
		if (!(mouse.pos.X >= this->position.x && mouse.pos.X <= this->position.x + this->button[0].size() - 1))
			return;
		if (!(mouse.pos.Y >= this->position.y && mouse.pos.Y <= this->position.y + this->button.size() - 1))
			return;
		if (this->inside)
			return;
		this->inside = true;
		int i = 0;
		for (string row : this->buttonActive) {
			Utils::setPosition(this->position.x, this->position.y + i);
			cout << row;
			i++;
		}
	};

	function<void()> click = [this]() {
		Mouse mouse = InputEngine::getInstance()->mouse;
		if (!(mouse.pos.X >= this->position.x && mouse.pos.X <= this->position.x + this->button[0].size() - 1))
			return;
		if (!(mouse.pos.Y >= this->position.y && mouse.pos.Y <= this->position.y + this->button.size() - 1))
			return;
		this->callback();
	};
	this->inside = true;
	outside();
	InputEngine::getInstance()->addMouseMoveCallback(inside, to_string(this->id) + "enterclbk");
	InputEngine::getInstance()->addMouseMoveCallback(outside, to_string(this->id) + "leaveclbk");
	InputEngine::getInstance()->addLeftClickCallback(click, to_string(this->id) + "clickclbk");
}