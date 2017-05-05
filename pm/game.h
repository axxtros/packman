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
#include "util.h"
#include "unit.h"

class Game {
private:
	const std::string SCORES_FILE = "files\\scores.txt";
	const std::string LEVEL_FILE_DIR = "files\\level_";
	const std::string LEVEL_FILE_EXT = ".txt";
	const unsigned int GAME_LEVEL_LEFT_POS = 0;
	const unsigned int GAME_LEVEL_TOP_POS = 0;

	const std::string RED_GHOST_NAME = "Blinky";
	const std::string PINK_GHOST_NAME = "Pink";
	const std::string BLUE_GHOST_NAME = "Inky";
	const std::string ORANGE_GHOST_NAME = "Clyde";

	//http://www-h.eng.cam.ac.uk/help/tpl/languages/C++/vectormemory.html
	/*std::vector<char> tempLineVec(lines[0].length());
	std::vector<std::vector<char>> tempLevelVec(lines.size(), tempLineVec);*/

	std::vector<std::string> pLevel;	//max.: 40x60 karakter
	ConsoleWindowManager* pCwm;
	std::map<std::string, unsigned int> mScores;	
	unsigned long mPlayerPoint;

	Unit* player;
	Unit* redGhost;
	Unit* pinkGhost;
	Unit* blueGhost;
	Unit* orangeGhost;
	
	void init();
	void loadMapUnits();
	void loadLevel(const unsigned int level);
	void gameLoop();
	void refreshScore(const unsigned int score);
	bool isKeydown(const int & key);
protected:
public:
	Game(ConsoleWindowManager*);
	~Game();
};

#endif // ! _GAME_H_
