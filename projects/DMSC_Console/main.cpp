#include <Windows.h>
#include <iostream>

#include "InputEngine.h"

using namespace std;



int main() {
	InputEngine* input = InputEngine::getInstance();

	function<void()> keya = []() {
		cout << "Key A pressed" << '\n';
	};
	function<void()> lclick = []() {
		cout << "Left Click" << '\n';
	};
	function<void()> resizeclbk = []() {
		cout << "Window Resized" << '\n';
	};
	input->addKeyDownCallback(0x41, keya, "callback 1");
	input->addLeftClickCallback(lclick, "callback lclick");
	input->addResizeCallback(resizeclbk, "rsz clbk");


	while (true) {
		//cout << "cosas";
	}
}
