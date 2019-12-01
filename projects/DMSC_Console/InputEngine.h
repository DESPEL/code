#pragma once

#include <Windows.h>
#include <iostream>
#include <stdio.h>
#include <map>
#include <set>
#include <vector>
#include <functional>
#include <thread>

class InputEngine
{
	struct Mouse {
		COORD pos;
	};

	static InputEngine* instance;
	HANDLE hStdin;
	DWORD fdwSaveOldMode;
	std::thread task;

	InputEngine();

	void ErrorExit(LPSTR lpszMessage);
	void KeyEventProc(KEY_EVENT_RECORD ker);
	void MouseEventProc(MOUSE_EVENT_RECORD mer);
	void ResizeEventProc(WINDOW_BUFFER_SIZE_RECORD wbsr);
	void readEvents();

	std::map<WORD, std::map<std::string, std::function<void()>>> keyDownCallbacks;
	std::map<WORD, std::map<std::string, std::function<void()>>> keyUpCallbacks;
	std::map<WORD, std::map<std::string, std::function<void()>>> keyPressCallbacks;

	std::map<std::string, std::function<void()>> mouseMoveCallbacks;
	std::map<WORD, std::map<std::string, std::function<void()>>> clickCallbacks;

	std::map<std::string, std::function<void()>> resizeCallbacks;
public:
	std::set<WORD> keysDown;
	Mouse mouse;
	COORD windowDimensions;

	static InputEngine* getInstance();

	void addKeyDownCallback(DWORD key_id, std::function<void()> callback, std::string key);
	void removeKeyDownCallback(DWORD key_id, std::string key);

	void addKeyUpCallback(DWORD key_id, std::function<void()> callback, std::string key);
	void removeKeyUpCallback(DWORD key_id, std::string key);

	void addKeyPressCallback(DWORD key_id, std::function<void()> callback, std::string key);
	void removeKeyPressCallback(DWORD key_id, std::string key);

	void addLeftClickCallback(std::function<void()> callback, std::string key);
	void removeLeftClickCallback(std::string key);

	void addRightClickCallback(std::function<void()> callback, std::string key);
	void removeRightClickCallback(std::string key);

	void addMouseMoveCallback(std::function<void()> callback, std::string key);
	void removeMouseMoveCallback(std::string key);

	void addResizeCallback(std::function<void()> callback, std::string key);
	void removeResizeCallback(std::string key);

	friend void startEngine(InputEngine* engine);
};

