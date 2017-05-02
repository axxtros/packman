// pm.cpp : Simple packman game console application.
//https://www.youtube.com/watch?v=bfR-Rx4oEn8

#include "stdafx.h"

#include "consoleWindowManager.h";
#include "mainMenuCtrl.h"

int main()
{	
	ConsoleWindowManager* cwm = new ConsoleWindowManager();
	
	//cwm->sPos(0, 0, "H");
	//wchar_t ch2 = L'\u25A0';
	//cwm->wPos(236,1, ch2);
	
	ConsoleWindowManager* &rCwm = cwm;
	//ConsoleWindowManager& rCwm = *cwm;			
	MainMenuCtrl* mmc = new MainMenuCtrl(rCwm);

	getchar();
	delete cwm;
    return 0;
}

