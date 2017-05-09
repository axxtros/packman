#include "stdafx.h"
#include "game.h"

Game::Game(ConsoleWindowManager* cwm)
{
	this->pCwm = cwm;
	init();
}

Game::~Game()
{	
	delete player;
	delete ghostRed;
	delete ghostPink;
	delete ghostBlue;
	delete ghostOrange;
}

void Game::init()
{	
	system("cls");
	mPlayerPoint = 0;
	loadMapUnits();
	loadLevel(1);
	gameLoop();
	getchar();
}

void Game::loadMapUnits()
{
	std::ifstream file(SCORES_FILE);
	std::string line;
	while (std::getline(file, line)) {
		std::size_t found = line.find(ConsoleWindowManager::SYMBOL_FILE_LINE_SEPARATOR);
		mScores[line.substr(0, found)] = std::stoi(line.substr((found + 1), line.length()));
	}
}

void Game::loadLevel(const unsigned int level)
{		
	std::string fileName = LEVEL_FILE_DIR + std::to_string(level) + LEVEL_FILE_EXT;
	std::ifstream file(fileName, std::fstream::in | std::fstream::out | std::fstream::app);
	std::string line;
	while (std::getline(file, line)) {
		pLevel.push_back(line);
	}
	if (pLevel.size() > 0) {
		bool firstWallBlock = true;
		for (unsigned int i = 0; i != pLevel.size(); i++) {
			for (unsigned int j = 0; j != pLevel[i].length(); j++) {
				//wall
				if (pLevel[i][j] == ConsoleWindowManager::SYMBOL_WALL_BLOCK) {
					pCwm->wPos(GAME_LEVEL_LEFT_POS + j, GAME_LEVEL_TOP_POS + i, ConsoleWindowManager::SYMBOL_FULL_BLOCK, ConsoleWindowManager::COLOR_WALL);
					if (firstWallBlock) {	//ezt a blokkot frissít 'üresen', hogy a villogó kurzor ne legyen 'szem elõtt'
						emptyBlockX = j;
						emptyBlockY = i;
						firstWallBlock = false;
					}
				}
				//dot
				else if (pLevel[i][j] == ConsoleWindowManager::SYMBOL_EMPTY_BLOCK) {
					pCwm->wPos(GAME_LEVEL_LEFT_POS + j, GAME_LEVEL_TOP_POS + i, ConsoleWindowManager::SYMBOL_DOT, ConsoleWindowManager::COLOR_DOT);
				}
				//player
				else if (pLevel[i][j] == ConsoleWindowManager::SYMBOL_PLAYER) {
					player = new Unit(ID_PLAYER, "", 0, j, i, 0, ConsoleWindowManager::COLOR_PLAYER, 0, &pLevel);
					pCwm->wPos(GAME_LEVEL_LEFT_POS + j, GAME_LEVEL_TOP_POS + i, ConsoleWindowManager::SYMBOL_GHOST, ConsoleWindowManager::COLOR_PLAYER);
				}
				//ghost: Blinky: Red
				else if (pLevel[i][j] == ConsoleWindowManager::SYMBOL_GHOST_RED) {
					ghostRed = new Unit(ID_GHOST_RED, RED_GHOST_NAME, RED_GHOST_SCORE, j, i, Util::getRandomNum(0, 3), Game::COLOR_GHOST_RED, Game::GHOST_DEFAULT_SPEED, &pLevel);
					pCwm->wPos(GAME_LEVEL_LEFT_POS + j, GAME_LEVEL_TOP_POS + i, ConsoleWindowManager::SYMBOL_GHOST, Game::COLOR_GHOST_RED);
				}
				//ghost: Pinky: Pink
				else if (pLevel[i][j] == ConsoleWindowManager::SYMBOL_GHOST_PINK) {
					ghostPink = new Unit(ID_GHOST_PINK, PINK_GHOST_NAME, PINK_GHOST_SCORE, j, i, Util::getRandomNum(0, 3), Game::COLOR_GHOST_PINK, Game::GHOST_DEFAULT_SPEED, &pLevel);
					pCwm->wPos(GAME_LEVEL_LEFT_POS + j, GAME_LEVEL_TOP_POS + i, ConsoleWindowManager::SYMBOL_GHOST, Game::COLOR_GHOST_PINK);
				}
				//ghost: Inky: Blue
				else if (pLevel[i][j] == ConsoleWindowManager::SYMBOL_GHOST_BLUE) {
					ghostBlue = new Unit(ID_GHOST_BLUE, BLUE_GHOST_NAME, BLUE_GHOST_SCORE, j, i, Util::getRandomNum(0, 3), Game::COLOR_GHOST_BLUE, Game::GHOST_DEFAULT_SPEED, &pLevel);
					pCwm->wPos(GAME_LEVEL_LEFT_POS + j, GAME_LEVEL_TOP_POS + i, ConsoleWindowManager::SYMBOL_GHOST, Game::COLOR_GHOST_BLUE);
				}
				//ghost: Clyde: Orange
				else if (pLevel[i][j] == ConsoleWindowManager::SYMBOL_GHOST_ORANGE) {
					ghostOrange = new Unit(ID_GHOST_ORANGE, ORANGE_GHOST_NAME, ORANGE_GHOST_SCORE, j, i, Util::getRandomNum(0, 3), Game::COLOR_GHOST_ORANGE, Game::GHOST_DEFAULT_SPEED, &pLevel);
					pCwm->wPos(GAME_LEVEL_LEFT_POS + j, GAME_LEVEL_TOP_POS + i, ConsoleWindowManager::SYMBOL_GHOST, Game::COLOR_GHOST_ORANGE);
				}
			}
		}
		refreshPlayerScore(mPlayerPoint);
	}
	else {			
		pCwm->sPos(0, 0, Util::getTableText(11), 7);			
		std::cin.ignore();
		exit(EXIT_FAILURE);
	}
}

void Game::gameLoop()
{
	if (IS_TIMING_VISIBLE) {
		std::thread timeThread([this] { this->timeCounter(); });
		timeThread.detach();
	}	

	bool gameLoop = true;		
	while (gameLoop) {
		//player move
		if (isKeydown(VK_UP)) {			
			player->setDir(0);
			playerMove(player);
		}
		if (isKeydown(VK_DOWN)) {
			player->setDir(1);
			playerMove(player);
		}
		if (isKeydown(VK_LEFT)) {
			player->setDir(2);
			playerMove(player);
		}
		if (isKeydown(VK_RIGHT)) {
			player->setDir(3);
			playerMove(player);
		}

		//ghosts move
		ghostRed->behaviourCtrl();
		aiUnitMove(ghostRed);
		//ghostBlue->behaviourCtrl();
		//unitMove(ghostBlue);
		//ghostPink->behaviourCtrl();
		//unitMove(ghostPink);
		//ghostOrange->behaviourCtrl();
		//unitMove(ghostOrange);

		Sleep(GAME_SPEED);
	}
}

void Game::playerMove(Unit * unit)
{
	pCwm->wPos(GAME_LEVEL_LEFT_POS + unit->getX(), GAME_LEVEL_TOP_POS + unit->getY(), ConsoleWindowManager::SYMBOL_EMPTY_BLOCK, 0);
	pLevel[unit->getY()][unit->getX()] = ConsoleWindowManager::SYMBOL_EMPTY_BLOCK;
	int currentCoord = 0;
	switch (unit->getDir()) {
		case 0:	//up
			currentCoord = unit->getY();
			if (!collisionDetection(unit)) {
				unit->setY(--currentCoord);
			}
			break;
		case 1:	//down
			currentCoord = unit->getY();
			if (!collisionDetection(unit)) {
				unit->setY(++currentCoord);
			}
			break;
		case 2:	//left
			currentCoord = unit->getX();
			if (!collisionDetection(unit)) {
				unit->setX(--currentCoord);
			}
			break;
		case 3:	//right
			currentCoord = unit->getX();
			if (!collisionDetection(unit)) {
				unit->setX(++currentCoord);
			}
			break;
	}
	pCwm->wPos(GAME_LEVEL_LEFT_POS + unit->getX(), GAME_LEVEL_TOP_POS + unit->getY(), ConsoleWindowManager::SYMBOL_GHOST, unit->getColor());
	pLevel[unit->getY()][unit->getX()] = ConsoleWindowManager::SYMBOL_EMPTY_BLOCK;
	if (!IS_TIMING_VISIBLE) {
		refreshEmptyBlock();
	}
}

void Game::aiUnitMove(Unit* unit)
{		
	if (unit->getMode() == Unit::SEARCH || unit->getMode() == Unit::FOLLOW || unit->getMode() == Unit::ANGRY) {
		int currentCoord = 0;
		switch (unit->getDir()) {
		case 0:		//up
			pCwm->wPos(GAME_LEVEL_LEFT_POS + unit->getX(), GAME_LEVEL_TOP_POS + unit->getY() + 1, ConsoleWindowManager::SYMBOL_EMPTY_BLOCK, 0);
			pLevel[unit->getY() + 1][unit->getX()] = ConsoleWindowManager::SYMBOL_EMPTY_BLOCK;
			currentCoord = unit->getY();
			unit->setY(currentCoord--);
			if (collisionDetection(unit)) {
				unit->setMode(Unit::Mode::SELDIR);
			}
			break;
		case 1:		//down
			pCwm->wPos(GAME_LEVEL_LEFT_POS + unit->getX(), GAME_LEVEL_TOP_POS + unit->getY() - 1, ConsoleWindowManager::SYMBOL_EMPTY_BLOCK, 0);
			pLevel[unit->getY() - 1][unit->getX()] = ConsoleWindowManager::SYMBOL_EMPTY_BLOCK;
			currentCoord = unit->getY();
			unit->setY(currentCoord++);
			if (collisionDetection(unit)) {
				unit->setMode(Unit::Mode::SELDIR);
			}
			break;
		case 2:		//left
			pCwm->wPos(GAME_LEVEL_LEFT_POS + unit->getX() + 1, GAME_LEVEL_TOP_POS + unit->getY(), ConsoleWindowManager::SYMBOL_EMPTY_BLOCK, 0);
			pLevel[unit->getY()][unit->getX() + 1] = ConsoleWindowManager::SYMBOL_EMPTY_BLOCK;
			currentCoord = unit->getX();
			unit->setX(currentCoord--);
			if (collisionDetection(unit)) {
				unit->setMode(Unit::Mode::SELDIR);
			}
			break;
		case 3:		//right
			pCwm->wPos(GAME_LEVEL_LEFT_POS + unit->getX() - 1, GAME_LEVEL_TOP_POS + unit->getY(), ConsoleWindowManager::SYMBOL_EMPTY_BLOCK, 0);
			pLevel[unit->getY()][unit->getX() - 1] = ConsoleWindowManager::SYMBOL_EMPTY_BLOCK;
			currentCoord = unit->getX();
			unit->setX(currentCoord++);
			if (collisionDetection(unit)) {
				unit->setMode(Unit::Mode::SELDIR);
			}
			break;
		}
		pCwm->wPos(GAME_LEVEL_LEFT_POS + unit->getX(), GAME_LEVEL_TOP_POS + unit->getY(), ConsoleWindowManager::SYMBOL_GHOST, unit->getColor());
		switch (unit->getId()) {
		case Game::ID_GHOST_RED:
			pLevel[unit->getY()][unit->getX()] = ConsoleWindowManager::SYMBOL_GHOST_RED;
			break;
		case Game::ID_GHOST_PINK:
			pLevel[unit->getY()][unit->getX()] = ConsoleWindowManager::SYMBOL_GHOST_PINK;
			break;
		case Game::ID_GHOST_BLUE:
			pLevel[unit->getY()][unit->getX()] = ConsoleWindowManager::SYMBOL_GHOST_BLUE;
			break;
		case Game::ID_GHOST_ORANGE:
			pLevel[unit->getY()][unit->getX()] = ConsoleWindowManager::SYMBOL_GHOST_ORANGE;
			break;
		}
		if (!IS_TIMING_VISIBLE) {
			refreshEmptyBlock();
		}
	}	
}

bool Game::collisionDetection(Unit* const unit)
{
	switch (unit->getDir()) {
		case 0: //up
			if (pLevel[unit->getY() - 1][unit->getX()] != ConsoleWindowManager::SYMBOL_EMPTY_BLOCK)
				return true;
			break;
		case 1: //down
			if (pLevel[unit->getY() + 1][unit->getX()] != ConsoleWindowManager::SYMBOL_EMPTY_BLOCK)
				return true;
			break;
		case 2: //left
			if (pLevel[unit->getY()][unit->getX() - 1] != ConsoleWindowManager::SYMBOL_EMPTY_BLOCK)
				return true;
			break;
		case 3: //right
			if (pLevel[unit->getY()][unit->getX() + 1] != ConsoleWindowManager::SYMBOL_EMPTY_BLOCK)
				return true;
			break;
	}	
	return false;
}

void Game::refreshPlayerScore(const unsigned int score)
{
	pCwm->sPos(GAME_LEVEL_LEFT_POS, pLevel.size(), Util::getTableText(12) + " " + std::to_string(score));	//score
}

inline bool Game::isKeydown(const int & key)
{
	return (GetAsyncKeyState(key) & 0x8000) != 0;
}

void Game::timeCounter()
{
	int hour = 0;
	int min = 0;
	int sec = 0;
	while (true) {
		std::string timeStr = std::to_string(hour) + ":" + std::to_string(min) + ":" + std::to_string(sec++);
		pCwm->sPos((GAME_LEVEL_LEFT_POS + pLevel[0].length() - timeStr.length()), pLevel.size(), timeStr);
		if (sec == 60) {
			++min;
			sec = 0;
		}
		if (min == 60) {
			++hour;
			min = 0;
		}
		Sleep(1000);
	}
}

/*
	Csak azért frissíti az adott fal blokkot, hogy a villogó kurzor ne látszódjon.
 */
void Game::refreshEmptyBlock()
{
	pCwm->wPos(GAME_LEVEL_LEFT_POS + emptyBlockX, GAME_LEVEL_TOP_POS + emptyBlockY, ConsoleWindowManager::SYMBOL_FULL_BLOCK, ConsoleWindowManager::COLOR_WALL);
}


