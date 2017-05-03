#pragma once

#ifndef MAIN_MENU_CTRL
#define MAIN_MENU_CTRL

#include <atlstr.h>
#include <string>
#include "consoleWindowManager.h";
#include "util.h"

class MainMenuCtrl {
private:
	ConsoleWindowManager* pCwm;	
	CString mainMenuText;
	void loadMenuItems();
	void printCenterText(const unsigned int& rowNum, const unsigned int& stringTableID, const unsigned int& leftDistance = 0, const unsigned int& color = 10);
protected:
public:
	MainMenuCtrl(ConsoleWindowManager*);
	~MainMenuCtrl();
};

#endif // ! MAIN_MENU_CTRL
