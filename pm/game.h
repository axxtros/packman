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
	
	ConsoleWindowManager* pCwm;
	std::map<std::string, unsigned int> mScores;
	std::vector<std::vector<char>> pLevelVector;
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
