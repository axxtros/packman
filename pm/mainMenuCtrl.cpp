#include "stdafx.h"
#include <fcntl.h>

#include "mainMenuCtrl.h"

MainMenuCtrl::MainMenuCtrl(ConsoleWindowManager* cwm)
{
	this->pCwm = cwm;
	loadMenuItems();
}

MainMenuCtrl::~MainMenuCtrl()
{
	//delete pCwm;
}

void MainMenuCtrl::loadMenuItems()
{
	std::string text = "This is a text!";	
	pCwm->sPos(Util::calcLineCenter(0, 100, text), 2, text);
	pCwm->wPos(12, 10, L'\u25A0');
}