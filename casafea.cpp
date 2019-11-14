#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>

struct consoleRenderer {
	int rows, columns;
	static std::vector<std::string> buffer;

	consoleRenderer() {
		CONSOLE_SCREEN_BUFFER_INFO csbi;

		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
		columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
		rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
		std::string temp = "";
		for (int i = 0; i < columns; i++)
			temp += " ";
		std::vector<std::string> tmpbuf(rows, temp);
		buffer = tmpbuf;
	}

	void pall() {
		for (int i = 0; i < rows; i++) {
			print(0, i, buffer[i]);
		}
	}

	void cls() {
		static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		COORD topLeft = { 0, 0 };
		std::cout.flush();
		GetConsoleScreenBufferInfo(hOut, &csbi);
		DWORD length = csbi.dwSize.X * csbi.dwSize.Y;

		DWORD written;
		FillConsoleOutputCharacter(hOut, TEXT(' '), length, topLeft, &written);
		FillConsoleOutputAttribute(hOut, csbi.wAttributes, length, topLeft, &written);
		SetConsoleCursorPosition(hOut, topLeft);
	}

	void setCursorPosition(int x, int y)
	{
		const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		std::cout.flush();
		COORD coord = { (SHORT)x, (SHORT)y };
		SetConsoleCursorPosition(hOut, coord);
	}

	void print(int x, int y, const std::string message) {
		setCursorPosition(x, y);
		updateBuffer(message);
		std::cout << message;
	}
	void print(const std::string message) {
		updateBuffer(message);
		std::cout << message;
	}

	void updateBuffer(const std::string msg) {
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
		COORD position = csbi.dwCursorPosition;
		int px = position.X;
		int py = position.Y;
		for (int i = 0; i < msg.size(); i++) {
			if (px >= columns) {
				px = px - columns;
				py++;
			}
			if (py >= rows) py = py - rows;
			buffer[py][px] = msg[i];
			px++;
		}
	}

	void setBuffer(int x, int y, std::string msg) {
		setCursorPosition(x, y);
		updateBuffer(msg);
	}

	int midr() { return rows / 2; }
	int midc() { return columns / 2; }
};

struct coord {
    coord() {}
    coord(int px, int py) { x = px, y = py;}
    int x, y;
    bool <(const coord &c2) {
        return x < c2.x;
    }
    bool >(const coord &c2) {
        return x > c2.x;
    }
}

namespace draw {
    consoleRenderer cr;
    void triangle(const coord c1, const coord c2, const coord c3, const char c) {

    }

    void line(const coord c1, const coord c2, const char c) {
        const mic = min(c1, c2);
        const mxc = max(c1, c2);

        auto y = [&c1, &c2](int x) {
            return (c2.y - c1.y) / (c2.x - c1.x) * x + (c1.y - (c2.y - c1.y) / (c2.x - c1.x) * x);
        }

        for (int i = mic.x; i <= mxc.x; i++) {
            cr.setBuffer(x, y(x), c);
        }
        cr.pall();
    }
}

int main() {
    draw(coord(0,0), coord(5,5), 'x');

}