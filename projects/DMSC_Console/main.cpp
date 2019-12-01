#include <Windows.h>
#include <iostream>
#include <chrono>
#include <functional>
#include <cstdlib>

#include "InputEngine.h"

using namespace std;

struct Size {
	float width;
	float height;
};

Size getConsoleSize() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	int columns, rows;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	return { (float)columns, (float)rows };
}

void setPosition(int x, int y){
	COORD p = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

class MovingSquare {
	float speed = 1;
	char ch = '*';
	float px;
	float py;
	float vx;
	float vy;
	bool tracking = false;
	bool running = false;
	Size consoleSize;
	chrono::time_point<chrono::steady_clock> last;
public:
	MovingSquare(char c = '#', float s = 1) {
		speed = s;
		ch = c;
		consoleSize = getConsoleSize();
		vx = s * (consoleSize.width / consoleSize.height);
		vy = s;
	}

	void start(int x = 0, int y = 0) {
		px = x;
		py = y;
		last = chrono::high_resolution_clock::now();
		setPosition(x, y);
		cout << ch;

		function<void()> movementr = [this]() {
			if (running) return;
			running = true;
			if (!tracking) {
				tracking = true;
				this->last = chrono::high_resolution_clock::now();
			}
			else {
				setPosition((int)this->px, (int)this->py);
				cout << " ";
				auto now = chrono::high_resolution_clock::now();
				float delta = chrono::duration_cast<chrono::milliseconds>(now - this->last).count() / 1000.0f;
				this->last = chrono::high_resolution_clock::now();
				this->px += this->vx * delta;
				if (this->px > this->consoleSize.width - 1) this->px = this->consoleSize.width - 1;
				setPosition((int)this->px, (int)this->py);
				cout << this->ch;
			}
			running = false;
		};
		function<void()> movementd = [this]() {
			if (running) return;
			running = true;
			if (!tracking) {
				tracking = true;
				this->last = chrono::high_resolution_clock::now();
			}
			else {
				setPosition((int)this->px, (int)this->py);
				cout << " ";
				auto now = chrono::high_resolution_clock::now();
				float delta = chrono::duration_cast<chrono::milliseconds>(now - this->last).count() / 1000.0f;
				this->last = chrono::high_resolution_clock::now();
				this->py += this->vy * delta;
				if (this->py > this->consoleSize.height - 1) this->py = this->consoleSize.height - 1;
				setPosition((int)this->px, (int)this->py);
				cout << this->ch;
			}
			running = false;
		};
		function<void()> movementl = [this]() {
			if (running) return;
			running = true;
			if (!tracking) {
				tracking = true;
				this->last = chrono::high_resolution_clock::now();
			}
			else {
				setPosition((int)this->px, (int)this->py);
				cout << " ";
				auto now = chrono::high_resolution_clock::now();
				float delta = chrono::duration_cast<chrono::milliseconds>(now - this->last).count() / 1000.0f;
				this->last = chrono::high_resolution_clock::now();
				this->px -= this->vx * delta;
				if (this->px < 0) this->px = 0;
				setPosition((int)this->px, (int)this->py);
				cout << this->ch;
			}
			running = false;
		};
		function<void()> movementu = [this]() {
			if (running) return;
			running = true;
			if (!tracking) {
				tracking = true;
				this->last = chrono::high_resolution_clock::now();
			}
			else {
				setPosition((int)this->px, (int)this->py);
				cout << " ";
				auto now = chrono::high_resolution_clock::now();
				float delta = chrono::duration_cast<chrono::milliseconds>(now - this->last).count() / 1000.0f;
				this->last = chrono::high_resolution_clock::now();
				this->py -= this->vy * delta;
				if (this->py < 0) this->py = 0;
				setPosition((int)this->px, (int)this->py);
				cout << this->ch;
			}
			running = false;
		};

		function<void()> stop = [this]() {
			this->tracking = false;
		};
		InputEngine* input = InputEngine::getInstance();

		input->addKeyDownCallback('S', movementd, "movdown");
		input->addKeyUpCallback('S', stop, "movdown");
		input->addKeyDownCallback('W', movementu, "movup");
		input->addKeyUpCallback('W', stop, "movup");
		input->addKeyDownCallback('D', movementr, "movright");
		input->addKeyUpCallback('D', stop, "movright");
		input->addKeyDownCallback('A', movementl, "movleft");
		input->addKeyUpCallback('A', stop, "movleft");
	}
};

class followCursor {
	COORD position;
	char ch;
	bool running = false;
public:
	followCursor(char c = 'x'){
		ch = c;
	}

	void start() {
		function<void()> setpos = [this]() {
			if (running)
				return;
			running = true;
			setPosition(position.X, position.Y + 2);
			cout << "                   ";
			setPosition(position.X, position.Y + 1);
			cout << " ";
			setPosition(position.X, position.Y + 0);
			cout << " ";
			position = InputEngine::getInstance()->mouse.pos;
			setPosition(position.X, position.Y + 2);
			cout << "| El mouse esta ahi";
			setPosition(position.X, position.Y + 1);
			cout << "^";
			setPosition(position.X, position.Y + 0);
			cout << "x";
			running = false;
		};
		InputEngine::getInstance()->addMouseMoveCallback(setpos, "setposmouse");
	}
};

int main() {
	setPosition(0, getConsoleSize().height - 1);
	cout << "  <- mueve el '#' con WASD" << '\n';

	InputEngine* input = InputEngine::getInstance();

	function<void()> end = []() {
		exit(0);
	};
	input->addKeyDownCallback(VK_ESCAPE, end, "end program");


	MovingSquare sq('#', 10.0f);
	sq.start(0, getConsoleSize().height - 1);

	setPosition(0, 0);
	followCursor test('x');
	test.start();
	this_thread::sleep_for(chrono::hours(8760)); // sleep for a year (avoid ending program)
}
