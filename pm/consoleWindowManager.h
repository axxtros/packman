#pragma once

#ifndef  CONSOLE_WINDOW_MANAGER
#define CONSOLE_WINDOW_MANAGER

#include <windows.h>
#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <string>
#include <tchar.h>
#include <atlstr.h>

class ConsoleWindowManager {

	static const bool FULL_SCREEN_MODE = 0;		

private:
	HANDLE mHConsole;
	HWND mhWnd;
	RECT mRect;
	COORD mCoord;
	CString mAppTitle;
	CString mAppVersion;
	CString mAppDeveloper;
	void calcPos(const int& x, const int& y, const int& color = 10);
protected:

public:
	static const unsigned int DEFAULT_CONSOLE_COLOR = 10;
	static const unsigned int CONSOLE_WINDOW_WIDTH = 1000;
	static const unsigned int CONSOLE_WINDOW_HEIGHT = 800;
	static const unsigned int CONSOLE_WINDOW_BUFFER_WIDTH = (CONSOLE_WINDOW_WIDTH / 8);	//kb. 8.3 pixel egy karakter oszlop

	//symbols
	static const char SYMBOL_FILE_LINE_SEPARATOR = '#';
	static const char SYMBOL_WALL_BLOCK = 'X';
	static const char SYMBOL_PLAYER = '0';
	static const char SYMBOL_GHOST_RED = 'R';
	static const char SYMBOL_GHOST_BLUE = 'B';
	static const char SYMBOL_GHOST_PINK = 'P';
	static const char SYMBOL_GHOST_ORANGE = 'O';
	static const char SYMBOL_EMPTY_BLOCK = ' ';
	static const wchar_t SYMBOL_FULL_BLOCK = L'\u2588';
	static const wchar_t SYMBOL_DOT = L'\u2219';
	static const wchar_t SYMBOL_GHOST = L'\u2588';

	static const unsigned int COLOR_PLAYER = 15;
	static const unsigned int COLOR_WALL = 2;
	static const unsigned int COLOR_DOT = 8;
	static const unsigned int COLOR_GHOST_RED = 12;
	static const unsigned int COLOR_GHOST_BLUE = 9;
	static const unsigned int COLOR_GHOST_PINK = 13;
	static const unsigned int COLOR_GHOST_ORANGE = 14;

	ConsoleWindowManager();
	~ConsoleWindowManager();
	void loadStringTable();
	void initWindow();	
	HANDLE getConsole();	
	void sPos(const int& x, const int& y, const std::string& ch, const int& color = 10);
	void wPos(const int& x, const int& y, const wchar_t &ch, const int& color = 10);
};

#endif // ! CONSOLE_WINDOW_MANAGER
