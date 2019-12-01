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
	bool trackingd = false;
	bool trackingr = false;
	bool trackingu = false;
	bool trackingl = false;
	Size consoleSize;
	chrono::time_point<chrono::steady_clock> last;
public:
	MovingSquare(char c = '#', float s = 1) {
		speed = s;
		ch = c;
		consoleSize = getConsoleSize();
	}

	void start(int x = 0, int y = 0) {
		px = x;
		py = y;
		last = chrono::high_resolution_clock::now();
		setPosition(x, y);
		cout << ch;

		function<void()> movementr = [this]() {
			if (!trackingr) {
				trackingr = true;
				this->last = chrono::high_resolution_clock::now();
			}
			else {
				setPosition((int)this->px, (int)this->py);
				cout << " ";
				auto now = chrono::high_resolution_clock::now();
				float delta = chrono::duration_cast<chrono::milliseconds>(now - this->last).count() / 1000.0f;
				this->px += this->speed * delta;
				if (this->px > this->consoleSize.width) this->px = this->consoleSize.width;
				setPosition((int)this->px, (int)this->py);
				cout << this->ch;
			}
		};
		function<void()> movementd = [this]() {
			if (!trackingd) {
				trackingd = true;
				this->last = chrono::high_resolution_clock::now();
			}
			else {
				setPosition((int)this->px, (int)this->py);
				cout << " ";
				auto now = chrono::high_resolution_clock::now();
				float delta = chrono::duration_cast<chrono::milliseconds>(now - this->last).count() / 1000.0f;
				this->py += this->speed * delta;
				if (this->py > this->consoleSize.height) this->py = this->consoleSize.height;
				setPosition((int)this->px, (int)this->py);
				cout << this->ch;
			}
		};
		function<void()> movementl = [this]() {
			if (!trackingl) {
				trackingl = true;
				this->last = chrono::high_resolution_clock::now();
			}
			else {
				setPosition((int)this->px, (int)this->py);
				cout << " ";
				auto now = chrono::high_resolution_clock::now();
				float delta = chrono::duration_cast<chrono::milliseconds>(now - this->last).count() / 1000.0f;
				this->px -= this->speed * delta;
				if (this->px < 0) this->px = 0;
				setPosition((int)this->px, (int)this->py);
				cout << this->ch;
			}
		};
		function<void()> movementu = [this]() {
			if (!trackingu) {
				trackingu = true;
				this->last = chrono::high_resolution_clock::now();
			}
			else {
				setPosition((int)this->px, (int)this->py);
				cout << " ";
				auto now = chrono::high_resolution_clock::now();
				float delta = chrono::duration_cast<chrono::milliseconds>(now - this->last).count() / 1000.0f;
				this->py -= this->speed * delta;
				if (this->py < 0) this->py = 0;
				setPosition((int)this->px, (int)this->py);
				cout << this->ch;
			}
		};

		function<void()> stopr = [this]() {
			this->trackingr = false;
		};

		function<void()> stopd = [this]() {
			this->trackingd = false;
		};
		function<void()> stopl = [this]() {
			this->trackingl = false;
		};
		function<void()> stopu = [this]() {
			this->trackingu = false;
		};
		InputEngine* input = InputEngine::getInstance();

		input->addKeyDownCallback('S', movementd, "movdown");
		input->addKeyUpCallback('S', stopd, "movdown");
		input->addKeyDownCallback('W', movementu, "movup");
		input->addKeyUpCallback('W', stopu, "movup");
		input->addKeyDownCallback('D', movementr, "movright");
		input->addKeyUpCallback('D', stopr, "movright");
		input->addKeyDownCallback('A', movementl, "movleft");
		input->addKeyUpCallback('A', stopl, "movleft");
	}
};


int main() {
	cout << "  <- mueve el '#' con WASD" << '\n';

	InputEngine* input = InputEngine::getInstance();

	function<void()> end = []() {
		exit(0);
	};
	input->addKeyDownCallback(VK_ESCAPE, end, "end program");


	MovingSquare sq;
	sq.start();
	this_thread::sleep_for(chrono::hours(8760)); // sleep for a year (avoid ending program)
}
