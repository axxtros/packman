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
#include "templates.h"

template<typename T>
T f(T s1, T s2)
{
	std::cout << tmax(s1, s2) << '\n';
	return tmax(s1, s2);
}

template <typename T>
T tmax(T value1, T value2) {
	return value1 >= value2 ? value1 : value2;
}

template <>
const char* tmax<const char*>(const char* value1, const char* value2) {
	return (strcmp(value1, value2) > 0) ? value1 : value2;
}

int main()
{	
	/*std::cout << "\a" << std::endl;
	Beep(1000, 1000);*/

	/*ConsoleWindowManager* cwm = new ConsoleWindowManager();		
	ConsoleWindowManager* &rCwm = cwm;	
	MainMenuCtrl* mmc = new MainMenuCtrl(rCwm);	
	delete mmc;
	delete cwm;*/
	
	//template gyakorlás
	f(5, 7);
	f(5.5, 7.0);
	double e = f<double>(2, 3);
	f("abc", "cde");

	Fifo<int> fifo;							//template osztályból létrehozott automatikus objektum
	fifo.setFifoData(1);
	fifo.writeDataToConsole();

	Fifo<int>* fifo2 = new Fifo<int>();		//template osztályból létrehozott dinamikus objektum
	fifo2->setFifoData(5);
	fifo2->writeDataToConsole();
	delete fifo2;

	typedef Fifo<std::string> stringFifo;	//typedef használatával létrehozott templte osztály

	stringFifo sf;
	sf.setFifoData("ABCDEFGH");
	sf.writeDataToConsole();

	getchar();	
    return 0;
}
