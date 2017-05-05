// pm.cpp : Simple packman game console application.

//sample:
//https://www.youtube.com/watch?v=bfR-Rx4oEn8
//unicode characters:
//http://ascii-table.com/ascii-extended-pc-list.php
//console colors:
//http://stackoverflow.com/questions/4053837/colorizing-text-in-the-console-with-c
//vector
//http://www-h.eng.cam.ac.uk/help/tpl/languages/C++/vectormemory.html

#include "stdafx.h"

#include "consoleWindowManager.h"
#include "mainMenuCtrl.h"

int main()
{	
	ConsoleWindowManager* cwm = new ConsoleWindowManager();	
	/*cwm->sPos(0, 0, "H");
	wchar_t ch2 = L'\u25A0';
	cwm->wPos(2,2, ch2);*/	
	ConsoleWindowManager* &rCwm = cwm;
	//ConsoleWindowManager& rCwm = *cwm;			
	MainMenuCtrl* mmc = new MainMenuCtrl(rCwm);

	getchar();
	delete mmc;
	delete cwm;
    return 0;
}

