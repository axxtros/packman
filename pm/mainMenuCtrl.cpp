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
	//delete cwm;
}

void MainMenuCtrl::loadMenuItems()
{
	pCwm->wPos(12, 10, L'\u25A0');

}