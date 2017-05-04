#include "stdafx.h"

#include "mainMenuCtrl.h"

MainMenuCtrl::MainMenuCtrl(ConsoleWindowManager* cwm)
{
	this->pCwm = cwm;
	loopMainMenu();
}

MainMenuCtrl::~MainMenuCtrl()
{
	//delete pCwm;
}

void MainMenuCtrl::loopMainMenu()
{	
	writeTitle();
	//system("cls");
	selectedMenu = 1;
	bool isKeyDown = false;
	writeMainMenu();
	while (!isKeydown(VK_RETURN)) {
		if (isKeydown(VK_UP)){
			selectedMenu--;
			isKeyDown = true;
		}
		if (isKeydown(VK_DOWN)) {
			selectedMenu++;
			isKeyDown = true;
		}
		if (selectedMenu == 0)
			selectedMenu = 4;
		if (selectedMenu > 4)
			selectedMenu = 1;
		if (isKeyDown) {
			writeMainMenu();
			Sleep(SLEEP_MENU);
			isKeyDown = false;
		}		
	}
	switch (selectedMenu) {
		//new game
		case 1: break;
		//high score
		case 2: break;
		//difficulty
		case 3: break;
		//exit
		case 4: break;
	}
}

void MainMenuCtrl::writeMainMenu()
{
	printCenterText(20, 4, 0, selectedMenu == 1 ? SELECTED_MENU_COLOR : ConsoleWindowManager::DEFAULT_CONSOLE_COLOR);	//new game
	printCenterText(21, 5, 0, selectedMenu == 2 ? SELECTED_MENU_COLOR : ConsoleWindowManager::DEFAULT_CONSOLE_COLOR);	//high score
	printCenterText(22, 6, 0, selectedMenu == 3 ? SELECTED_MENU_COLOR : ConsoleWindowManager::DEFAULT_CONSOLE_COLOR);	//difficulty
	printCenterText(23, 10, 0, selectedMenu == 4 ? SELECTED_MENU_COLOR : ConsoleWindowManager::DEFAULT_CONSOLE_COLOR);	//exit
}

void MainMenuCtrl::printCenterText(const unsigned int& rowNum, const unsigned int& stringTableID, const unsigned int& leftDistance, const unsigned int& color) {
	std::string text = Util::getTableText(stringTableID);
	pCwm->sPos(Util::calcLineCenter(leftDistance, ConsoleWindowManager::CONSOLE_WINDOW_BUFFER_WIDTH, text), rowNum, text, color);
}

void MainMenuCtrl::writeTitle()
{
	std::ifstream file(LOGO_FILE);
	std::string line;	
	unsigned int lineNum = 0;
	while (std::getline(file, line))
	{		
		if (line.length() > 0) {
			for (unsigned int i = 0; i != line.length(); i++) {
				if (line[i] == ConsoleWindowManager::SYMBOL_WALL_BLOCK) {					
					pCwm->wPos(GAME_TITLE_LEFT_POS + i, GAME_TITLE_TOP_POS + lineNum, ConsoleWindowManager::SYMBOL_FULL_BLOCK, 2);
				}
			}
		}
		lineNum++;		
	}
}

bool MainMenuCtrl::isKeydown(const int & key)
{
	return (GetAsyncKeyState(key) & 0x8000) != 0;
}
