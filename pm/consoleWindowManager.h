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
		
	static const char SYMBOL_FILE_LINE_SEPARATOR = '#';

	//symbols - map (ezek a térképen jelennek meg)
	static const char SYMBOL_MAP_WALL_BLOCK = 'X';
	static const char SYMBOL_MAP_PLAYER = '0';
	static const char SYMBOL_MAP_GHOST_RED = 'R';
	static const char SYMBOL_MAP_GHOST_BLUE = 'B';
	static const char SYMBOL_MAP_GHOST_PINK = 'P';
	static const char SYMBOL_MAP_GHOST_ORANGE = 'O';
	static const char SYMBOL_MAP_GHOST_TEST = 'T';
	static const char SYMBOL_MAP_MISSILE = 'M';
	static const char SYMBOL_MAP_AMMO_BOX = 'A';
	
	//symbols - screen (ezek a felületen jelennek meg)
	static const wchar_t SYMBOL_SCREEN_WALL_BLOCK = L'\u2588';
	static const wchar_t SYMBOL_SCREEN_DOT = ' ';//L'\u2219';	
	//static const char SYMBOL_SCREEN_DOT = ' ';
	static const wchar_t SYMBOL_SCREEN_PLAYER = L'\u2588';//L'\u2587';//L'\u2588';
	static const wchar_t SYMBOL_SCREEN_GHOST = L'\u2588';
	static const wchar_t SYMBOL_SCREEN_AMMO_BOX = 'A';
	static const wchar_t SYMBOL_MISSILE = 'o';//L'\u0398';	

	//symbols - universals (map and screen)
	static const wchar_t SYMBOL_EMPTY_BLOCK = ' ';				//universal, screen and map
	static const wchar_t SYMBOL_INFINITY = L'\u221E';

	static const unsigned int COLOR_EMPTY = 0;
	static const unsigned int COLOR_PLAYER = 15;
	static const unsigned int COLOR_WALL = 2;
	static const unsigned int COLOR_DOT = 8;
	static const unsigned int COLOR_MISSILE = 15;
	static const unsigned int COLOR_AMMO_BOX = 7;

	ConsoleWindowManager();
	~ConsoleWindowManager();
	void loadStringTable();
	void initWindow();	
	HANDLE getConsole();	
	void sPos(const int& x, const int& y, const std::string& ch, const int& color = 10);
	void wPos(const int& x, const int& y, const wchar_t &ch, const int& color = 10);
};

#endif // ! CONSOLE_WINDOW_MANAGER
