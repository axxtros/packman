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
	/*std::cout << "\a" << std::endl;
	Beep(1000, 1000);*/

	ConsoleWindowManager* cwm = new ConsoleWindowManager();		
	ConsoleWindowManager* &rCwm = cwm;	
	MainMenuCtrl* mmc = new MainMenuCtrl(rCwm);
	
	delete mmc;
	delete cwm;
	
	getchar();	
    return 0;
}

