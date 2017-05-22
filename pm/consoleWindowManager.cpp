#include "stdafx.h"

#include "consoleWindowManager.h"

ConsoleWindowManager::ConsoleWindowManager()
{
	loadStringTable();
	initWindow();	
}

ConsoleWindowManager::~ConsoleWindowManager()
{

}

void ConsoleWindowManager::loadStringTable()
{
	mAppTitle.LoadStringW(1);
	mAppVersion.LoadStringW(2);
	mAppDeveloper.LoadStringW(3);
}


void ConsoleWindowManager::initWindow()
{				
	SetConsoleTitle(mAppTitle + " v." + mAppVersion + " by " + mAppDeveloper);
	mHConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	mhWnd = GetDesktopWindow();
	GetWindowRect(mhWnd, &mRect);	
	SetConsoleScreenBufferSize(mhWnd, mCoord);
	if (FULL_SCREEN_MODE) {
		//https://cboard.cprogramming.com/windows-programming/72624-how-get-your-program-run-fullscreen-console.html
		keybd_event(VK_MENU, 0x38, 0, 0);
		keybd_event(VK_RETURN, 0x1c, 0, 0);
		keybd_event(VK_RETURN, 0x1c, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0);
	}
	else {
		unsigned int screenWidth = mRect.right;
		unsigned int screenHeight = mRect.bottom;
		unsigned int consoleWindowX = ((screenWidth / 2) - (CONSOLE_WINDOW_WIDTH / 2));
		unsigned int consoleWindowY = ((screenHeight / 2) - (CONSOLE_WINDOW_HEIGHT / 2));
		mhWnd = GetConsoleWindow();
		MoveWindow(mhWnd, consoleWindowX, consoleWindowY, CONSOLE_WINDOW_WIDTH, CONSOLE_WINDOW_HEIGHT, TRUE);
	}		
}

HANDLE ConsoleWindowManager::getConsole()
{
	return mHConsole;
}

void ConsoleWindowManager::sPos(const int & x, const int & y, const std::string & ch, const int & color)
{
	calcPos(x, y, color);	
	_setmode(_fileno(stdout), _O_TEXT);				//TEXT mode
	std::cout << ch;
}

void ConsoleWindowManager::wPos(const int & x, const int & y, const wchar_t & ch, const int & color)
{
	calcPos(x, y, color);
	_setmode(_fileno(stdout), _O_U8TEXT);			//UTF-8 mode
	std::wcout << ch;
}

inline void ConsoleWindowManager::calcPos(const int & x, const int & y, const int & color)
{
	mCoord.X = x;
	mCoord.Y = y;
	SetConsoleCursorPosition(mHConsole, mCoord);
	SetConsoleTextAttribute(mHConsole, color);	
}
