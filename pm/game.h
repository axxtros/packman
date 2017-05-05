#pragma once

#ifndef _GAME_H_
#define _GAME_H_

#include <windows.h>
#include <fcntl.h>
#include <atlstr.h>
#include <string>
#include <fstream>
#include <map>
#include <cstdlib>
#include <vector>

#include "consoleWindowManager.h"

class Game {
private:
	const std::string SCORES_FILE = "files\\scores.txt";
	const std::string LEVEL_FILE = "files\\level_1.txt";
	const unsigned int GAME_LEVEL_LEFT_POS = 0;
	const unsigned int GAME_LEVEL_TOP_POS = 0;

	//http://www-h.eng.cam.ac.uk/help/tpl/languages/C++/vectormemory.html
	/*std::vector<char> tempLineVec(lines[0].length());
	std::vector<std::vector<char>> tempLevelVec(lines.size(), tempLineVec);*/

	std::vector<std::string> pLevel;
	ConsoleWindowManager* pCwm;
	std::map<std::string, unsigned int> mScores;	
	unsigned long mPlayerPoint;

	void init();
	void loadScores();
	void loadLevel(const unsigned int level);
protected:
public:
	Game(ConsoleWindowManager*);
	~Game();
};

#endif // ! _GAME_H_
