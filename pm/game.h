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
#include <thread>

#include "consoleWindowManager.h"
#include "util.h"
#include "unit.h"

class Game {
private:
	const bool IS_TIMING_VISIBLE = false;
	const bool IS_INFINITE_MISSILE = 1;

	const std::string SCORES_FILE = "files\\scores.txt";
	const std::string LEVEL_FILE_DIR = "files\\level_";
	const std::string LEVEL_FILE_EXT = ".txt";
	const unsigned int GAME_LEVEL_LEFT_POS = 0;
	const unsigned int GAME_LEVEL_TOP_POS = 1;

	enum {
		ID_PLAYER = 0,
		ID_GHOST = 1,
		ID_MISSILE = 2
	};

	const std::string RED_GHOST_NAME = "Blinky";
	const std::string PINK_GHOST_NAME = "Pink";
	const std::string BLUE_GHOST_NAME = "Inky";
	const std::string ORANGE_GHOST_NAME = "Clyde";

	const unsigned int RED_GHOST_SCORE = 100;
	const unsigned int PINK_GHOST_SCORE = 200;
	const unsigned int BLUE_GHOST_SCORE = 300;
	const unsigned int ORANGE_GHOST_SCORE = 400;	

	const unsigned int COLOR_GHOST_RED = 12;
	const unsigned int COLOR_GHOST_BLUE = 9;
	const unsigned int COLOR_GHOST_PINK = 13;
	const unsigned int COLOR_GHOST_ORANGE = 14;

	const unsigned int GAME_SPEED = 25;		//50;
	
	enum {
		SPEED_MAX = 0,
		SPEED_NORMAL = 1,
		SPEED_EASY = 2,
		SPEED_SLOW = 3
	};

	//http://www-h.eng.cam.ac.uk/help/tpl/languages/C++/vectormemory.html
	/*std::vector<char> tempLineVec(lines[0].length());
	std::vector<std::vector<char>> tempLevelVec(lines.size(), tempLineVec);*/

	unsigned int emptyBlockX;
	unsigned int emptyBlockY;

	std::vector<std::string> pLevel;	//max.: 40x60 karakter
	ConsoleWindowManager* pCwm;
	std::map<std::string, unsigned int> mScores;	
	unsigned long mPlayerBullet;	

	Unit* player;
	Unit* ghost;
	std::vector<Unit*> ghosts;
	unsigned int tmpIdx;
	std::string bulletStr;
	bool isMissileReady;
	
	void init();
	void loadMapUnits();
	void loadLevel(const unsigned int level);	
	void gameLoop();
	//void unitMove(Unit *unit);
	void unitMove(GameObject * unit);
	bool collisionDetection(GameObject* const unit);
	bool Game::getFreeBlock(unsigned int mapY, unsigned int mapX);
	void refreshPlayerBullets(const unsigned int score);
	bool isKeydown(const int & key);
	void timeCounter();
	void refreshEmptyBlock();
	Unit* getShotUnit(Missile* missile);
protected:
public:
	Game(ConsoleWindowManager*);
	~Game();
};

#endif // ! _GAME_H_