#pragma once

#ifndef MAIN_MENU_CTRL
#define MAIN_MENU_CTRL

#include <windows.h>
#include <fcntl.h>
#include <atlstr.h>
#include <string>
#include <fstream>

#include "consoleWindowManager.h";
#include "util.h"

class MainMenuCtrl {
private:

	static const unsigned int SELECTED_MENU_COLOR = 14;
	static const unsigned int SLEEP_MENU = 300;
	const unsigned int GAME_TITLE_LEFT_POS = 32;
	const unsigned int GAME_TITLE_TOP_POS = 5;
	const std::string LOGO_FILE = "files\\logo.txt";

	ConsoleWindowManager* pCwm;	
	CString mainMenuText;
	void loopMainMenu();
	void writeMainMenu();	
	void printCenterText(const unsigned int& rowNum, const unsigned int& stringTableID, const unsigned int& leftDistance = 0, const unsigned int& color = 10);
	unsigned int selectedMenu;
	void writeTitle();
	bool isKeydown(const int & key);
protected:
public:
	MainMenuCtrl(ConsoleWindowManager*);
	~MainMenuCtrl();
};

#endif // ! MAIN_MENU_CTRL
