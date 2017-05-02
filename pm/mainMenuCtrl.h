#pragma once

#ifndef MAIN_MENU_CTRL
#define MAIN_MENU_CTRL

#include <atlstr.h>
#include "consoleWindowManager.h";

class MainMenuCtrl {
private:
	ConsoleWindowManager* pCwm;
	void loadMenuItems();
protected:
public:
	MainMenuCtrl(ConsoleWindowManager*);
	~MainMenuCtrl();
};

#endif // ! MAIN_MENU_CTRL
