#pragma once

#include <windows.h>
#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <string>
#include <tchar.h>

#ifndef  CONSOLE_WINDOW_MANAGER
#define CONSOLE_WINDOW_MANAGER

class ConsoleWindowManager {

	static const bool FULL_SCREEN_MODE = 0;
	static const unsigned int CONSOLE_WINDOW_WIDTH = 1000;
	static const unsigned int CONSOLE_WINDOW_HEIGHT = 800;
	const unsigned int DEFAULT_CONSOLE_COLOR = 10;

private:
	HANDLE mHConsole;
	HWND mhWnd;
	RECT mRect;
	COORD mCoord;
	void calcPos(const int& x, const int& y, const int& color = 10);
protected:

public:
	ConsoleWindowManager();
	~ConsoleWindowManager();
	void init();
	HANDLE getConsole();	
	void sPos(const int& x, const int& y, const std::string& ch, const int& color = 10);
	void wPos(const int& x, const int& y, const wchar_t &ch, const int& color = 10);
};


#endif // ! CONSOLE_WINDOW_MANAGER
