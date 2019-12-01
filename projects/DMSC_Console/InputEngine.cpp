#include "InputEngine.h"

using namespace std;

InputEngine* InputEngine::instance = nullptr;

void InputEngine::ErrorExit(LPSTR lpszMessage)
{
	fprintf(stderr, "%s\n", lpszMessage);

	// Restore input mode on exit.

	SetConsoleMode(hStdin, fdwSaveOldMode);

	ExitProcess(0);
}

void startEngine(InputEngine* engine) {
	engine->readEvents();
}

InputEngine::InputEngine() {
	task = thread(startEngine, this);
}

InputEngine* InputEngine::getInstance() {
	if (instance == nullptr)
		instance = new InputEngine;
	return instance;
}

void InputEngine::readEvents() {
	//cout << "read events called" << '\n';

	DWORD cNumRead, fdwMode, i;
	INPUT_RECORD irInBuf[128];
	int counter = 0;

	// Get the standard input handle. 

	hStdin = GetStdHandle(STD_INPUT_HANDLE);
	if (hStdin == INVALID_HANDLE_VALUE)
		ErrorExit(LPSTR("GetStdHandle"));

	// Save the current input mode, to be restored on exit. 

	if (!GetConsoleMode(hStdin, &fdwSaveOldMode))
		ErrorExit(LPSTR("GetConsoleMode"));

	// Enable the window and mouse input events. 

	fdwMode = ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;;
	if (!SetConsoleMode(hStdin, fdwMode))
		ErrorExit(LPSTR("SetConsoleMode"));

	// Loop to read and handle the next 100 input events. 
	while (true)
	{
		// Wait for the events. 

		if (!ReadConsoleInput(
			hStdin,      // input buffer handle 
			irInBuf,     // buffer to read into 
			128,         // size of read buffer 
			&cNumRead)) // number of records read 
			ErrorExit(LPSTR("ReadConsoleInput"));

		// Dispatch the events to the appropriate handler. 
		for (i = 0; i < cNumRead; i++)
		{
			switch (irInBuf[i].EventType)
			{
			case KEY_EVENT: // keyboard input 
				KeyEventProc(irInBuf[i].Event.KeyEvent);
				break;

			case MOUSE_EVENT: // mouse input 
				MouseEventProc(irInBuf[i].Event.MouseEvent);
				break;

			case WINDOW_BUFFER_SIZE_EVENT: // scrn buf. resizing 
				ResizeEventProc(irInBuf[i].Event.WindowBufferSizeEvent);
				break;

			case FOCUS_EVENT:  // disregard focus events 
			case MENU_EVENT:   // disregard menu events 
				break;

			default:
				ErrorExit(LPSTR("Unknown event type"));
				break;
			}
		}
	}
}

void InputEngine::KeyEventProc(KEY_EVENT_RECORD ker)
{
	if (ker.bKeyDown) {
		if (keysDown.find(ker.wVirtualKeyCode) == end(keysDown)) {
			keysDown.insert(ker.wVirtualKeyCode);
			for (pair<const string, function<void()>>& callback : keyPressCallbacks[ker.wVirtualKeyCode])
				callback.second();
		}
		for (pair<const string, function<void()>>& callback : keyDownCallbacks[ker.wVirtualKeyCode])
			callback.second();
	}
	else {
		for (pair<const string, function<void()>>& callback : keyUpCallbacks[ker.wVirtualKeyCode])
			callback.second();
	}
}

void InputEngine::MouseEventProc(MOUSE_EVENT_RECORD mer)
{
#ifndef MOUSE_HWHEELED
#define MOUSE_HWHEELED 0x0008
#endif
	switch (mer.dwEventFlags)
	{
	case 0:
		if (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			for (pair<const string, function<void()>>& callback : clickCallbacks[FROM_LEFT_1ST_BUTTON_PRESSED])
				callback.second();
		}
		else if (mer.dwButtonState == RIGHTMOST_BUTTON_PRESSED)
		{
			for (pair<const string, function<void()>>& callback : clickCallbacks[RIGHTMOST_BUTTON_PRESSED])
				callback.second();
		}
		else
		{
			// button release idk
		}
		break;
	case DOUBLE_CLICK: // same as one click, but doubled
		if (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			for (pair<const string, function<void()>>& callback : clickCallbacks[FROM_LEFT_1ST_BUTTON_PRESSED])
				callback.second();
		}
		else if (mer.dwButtonState == RIGHTMOST_BUTTON_PRESSED)
		{
			for (pair<const string, function<void()>>& callback : clickCallbacks[RIGHTMOST_BUTTON_PRESSED])
				callback.second();
		}
		else
		{
			// button release idk
		}
		break;
	case MOUSE_HWHEELED:
		// no callback at this moment
		break;
	case MOUSE_MOVED:
		// only update position (:
		mouse.pos = mer.dwMousePosition;
		break;
	case MOUSE_WHEELED:
		break;
	default:
		//printf("unknown\n");
		break;
	}
}

void InputEngine::ResizeEventProc(WINDOW_BUFFER_SIZE_RECORD wbsr)
{
	for (pair<const string, function<void()>>& callback : resizeCallbacks)
		callback.second();
	windowDimensions = wbsr.dwSize;
}


void InputEngine::addKeyDownCallback(DWORD key_id, function<void()> callback, string key) {
	keyDownCallbacks[key_id][key] = callback;
}

void InputEngine::removeKeyDownCallback(DWORD key_id, string key) {
	keyDownCallbacks[key_id].erase(key);
}

void InputEngine::addKeyUpCallback(DWORD key_id, function<void()> callback, string key) {
	keyUpCallbacks[key_id][key] = callback;
}

void InputEngine::removeKeyUpCallback(DWORD key_id, string key) {
	keyUpCallbacks[key_id].erase(key);
}

void InputEngine::addKeyPressCallback(DWORD key_id, function<void()> callback, string key) {
	keyPressCallbacks[key_id][key] = callback;
}

void InputEngine::removeKeyPressCallback(DWORD key_id, string key) {
	keyPressCallbacks[key_id].erase(key);
}

void InputEngine::addLeftClickCallback(function<void()> callback, string key) {
	clickCallbacks[FROM_LEFT_1ST_BUTTON_PRESSED][key] = callback;
}

void InputEngine::removeLeftClickCallback(string key) {
	clickCallbacks[FROM_LEFT_1ST_BUTTON_PRESSED].erase(key);
}

void InputEngine::addRightClickCallback(function<void()> callback, string key) {
	clickCallbacks[RIGHTMOST_BUTTON_PRESSED][key] = callback;
}

void InputEngine::removeRightClickCallback(string key) {
	clickCallbacks[RIGHTMOST_BUTTON_PRESSED].erase(key);
}

void InputEngine::addResizeCallback(function<void()> callback, string key) {
	resizeCallbacks[key] = callback;
}

void InputEngine::removeResizeCallback(string key) {
	resizeCallbacks.erase(key);
}