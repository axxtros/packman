#include "stdafx.h"

#include <windows.h>
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
	printCenterText(20, 4, 0);
	printCenterText(21, 5, 0);	
	printCenterText(22, 6, 0);
	pCwm->sPos(50, 23, Util::getTableText(7));
	printCenterText(23, 8, 0);
	pCwm->sPos(70, 23, Util::getTableText(9));
	printCenterText(24, 10, 0);	
}

void MainMenuCtrl::printCenterText(const unsigned int& rowNum, const unsigned int& stringTableID, const unsigned int& leftDistance, const unsigned int& color) {
	std::string text = Util::getTableText(stringTableID);
	pCwm->sPos(Util::calcLineCenter(leftDistance, ConsoleWindowManager::CONSOLE_WINDOW_BUFFER_WIDTH, text), rowNum, text, color);
}
