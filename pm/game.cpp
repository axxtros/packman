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
	delete[] &ghosts;
	delete ghost;
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
		bool isPlayerDone = false;
		for (unsigned int i = 0; i != pLevel.size(); i++) {
			for (unsigned int j = 0; j != pLevel[i].length(); j++) {
				//wall
				if (pLevel[i][j] == ConsoleWindowManager::SYMBOL_MAP_WALL_BLOCK) {
					pCwm->wPos(GAME_LEVEL_LEFT_POS + j, GAME_LEVEL_TOP_POS + i, ConsoleWindowManager::SYMBOL_SCREEN_WALL_BLOCK, ConsoleWindowManager::COLOR_WALL);
					if (firstWallBlock) {	//ezt a blokkot friss�t '�resen', hogy a villog� kurzor ne legyen 'szem el�tt'
						emptyBlockX = j;
						emptyBlockY = i;
						firstWallBlock = false;
					}
				}
				//dot
				else if (pLevel[i][j] == ConsoleWindowManager::SYMBOL_EMPTY_BLOCK) {
					pCwm->wPos(GAME_LEVEL_LEFT_POS + j, GAME_LEVEL_TOP_POS + i, ConsoleWindowManager::SYMBOL_SCREEN_DOT, ConsoleWindowManager::COLOR_DOT);
				}
				//player
				else if (pLevel[i][j] == ConsoleWindowManager::SYMBOL_MAP_PLAYER && !isPlayerDone) {
					player = new Unit(ID_PLAYER, "", 0, j, i, 0, ConsoleWindowManager::COLOR_PLAYER, 0, &pLevel, ConsoleWindowManager::SYMBOL_MAP_PLAYER, ConsoleWindowManager::SYMBOL_SCREEN_PLAYER);
					pCwm->wPos(GAME_LEVEL_LEFT_POS + j, GAME_LEVEL_TOP_POS + i, ConsoleWindowManager::SYMBOL_SCREEN_PLAYER, ConsoleWindowManager::COLOR_PLAYER);
					isPlayerDone = true;
				}
				//ghost: Blinky: Red
				else if (pLevel[i][j] == ConsoleWindowManager::SYMBOL_MAP_GHOST_RED) {
					ghost = new Unit(ID_GHOST, RED_GHOST_NAME, RED_GHOST_SCORE, j, i, Util::getRandomNum(0, 3), Game::COLOR_GHOST_RED, Game::GHOST_DEFAULT_SPEED, &pLevel, ConsoleWindowManager::SYMBOL_MAP_GHOST_RED, ConsoleWindowManager::SYMBOL_SCREEN_GHOST);
					ghosts.push_back(ghost);
					pCwm->wPos(GAME_LEVEL_LEFT_POS + j, GAME_LEVEL_TOP_POS + i, ConsoleWindowManager::SYMBOL_SCREEN_GHOST, Game::COLOR_GHOST_RED);
				}
				//ghost: Pinky: Pink
				else if (pLevel[i][j] == ConsoleWindowManager::SYMBOL_MAP_GHOST_PINK) {
					ghost = new Unit(ID_GHOST, PINK_GHOST_NAME, PINK_GHOST_SCORE, j, i, Util::getRandomNum(0, 3), Game::COLOR_GHOST_PINK, Game::GHOST_DEFAULT_SPEED, &pLevel, ConsoleWindowManager::SYMBOL_MAP_GHOST_PINK, ConsoleWindowManager::SYMBOL_SCREEN_GHOST);
					ghosts.push_back(ghost);
					pCwm->wPos(GAME_LEVEL_LEFT_POS + j, GAME_LEVEL_TOP_POS + i, ConsoleWindowManager::SYMBOL_SCREEN_GHOST, Game::COLOR_GHOST_PINK);
				}
				//ghost: Inky: Blue
				else if (pLevel[i][j] == ConsoleWindowManager::SYMBOL_MAP_GHOST_BLUE) {
					ghost = new Unit(ID_GHOST, BLUE_GHOST_NAME, BLUE_GHOST_SCORE, j, i, Util::getRandomNum(0, 3), Game::COLOR_GHOST_BLUE, Game::GHOST_DEFAULT_SPEED, &pLevel, ConsoleWindowManager::SYMBOL_MAP_GHOST_BLUE, ConsoleWindowManager::SYMBOL_SCREEN_GHOST);
					ghosts.push_back(ghost);
					pCwm->wPos(GAME_LEVEL_LEFT_POS + j, GAME_LEVEL_TOP_POS + i, ConsoleWindowManager::SYMBOL_SCREEN_GHOST, Game::COLOR_GHOST_BLUE);
				}
				//ghost: Clyde: Orange
				else if (pLevel[i][j] == ConsoleWindowManager::SYMBOL_MAP_GHOST_ORANGE) {
					ghost = new Unit(ID_GHOST, ORANGE_GHOST_NAME, ORANGE_GHOST_SCORE, j, i, Util::getRandomNum(0, 3), Game::COLOR_GHOST_ORANGE, Game::GHOST_DEFAULT_SPEED, &pLevel, ConsoleWindowManager::SYMBOL_MAP_GHOST_ORANGE, ConsoleWindowManager::SYMBOL_SCREEN_GHOST);
					ghosts.push_back(ghost);
					pCwm->wPos(GAME_LEVEL_LEFT_POS + j, GAME_LEVEL_TOP_POS + i, ConsoleWindowManager::SYMBOL_SCREEN_GHOST, Game::COLOR_GHOST_ORANGE);
				}
				//unknow character -> SYMBOL_EMPTY_BLOCK
				else {
					pLevel[i][j] = ConsoleWindowManager::SYMBOL_EMPTY_BLOCK;
					pCwm->wPos(GAME_LEVEL_LEFT_POS + j, GAME_LEVEL_TOP_POS + i, ConsoleWindowManager::SYMBOL_SCREEN_DOT, ConsoleWindowManager::COLOR_DOT);					
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
			unitMove(player);
		}
		if (isKeydown(VK_DOWN)) {
			player->setDir(1);
			unitMove(player);
		}
		if (isKeydown(VK_LEFT)) {
			player->setDir(2);
			unitMove(player);
		}
		if (isKeydown(VK_RIGHT)) {
			player->setDir(3);
			unitMove(player);
		}

		//ghosts move
		if (!ghosts.empty()) {
			for (ghostsIdx = 0; ghostsIdx != ghosts.size(); ghostsIdx++) {
				unitMove(ghosts[ghostsIdx]);
				ghosts[ghostsIdx]->behaviourCtrl();
			}
		}	

		Sleep(GAME_SPEED);
	}
}

void Game::unitMove(Unit * unit)
{
	if ( (unit->getId() == ID_PLAYER) || (unit->getId() == ID_GHOST && (unit->getMode() == Unit::MOVE)) ) {
		
		pCwm->wPos(GAME_LEVEL_LEFT_POS + unit->getX(), GAME_LEVEL_TOP_POS + unit->getY(), ConsoleWindowManager::SYMBOL_EMPTY_BLOCK, 0);
		pLevel[unit->getY()][unit->getX()] = ConsoleWindowManager::SYMBOL_EMPTY_BLOCK;
		
		int currentCoord = 0;
		bool isCollision = false;
		switch (unit->getDir()) {
		case 0:	//up
			currentCoord = unit->getY();
			if (!collisionDetection(unit)) {
				unit->setY(--currentCoord);				
			}
			else {
				isCollision = true;
			}
			break;
		case 1:	//down
			currentCoord = unit->getY();
			if (!collisionDetection(unit)) {
				unit->setY(++currentCoord);				
			}
			else {
				isCollision = true;
			}
			break;
		case 2:	//left
			currentCoord = unit->getX();
			if (!collisionDetection(unit)) {
				unit->setX(--currentCoord);				
			}
			else {
				isCollision = true;
			}
			break;
		case 3:	//right
			currentCoord = unit->getX();
			if (!collisionDetection(unit)) {
				unit->setX(++currentCoord);				
			}
			else {
				isCollision = true;
			}
			break;
		}
		
		pCwm->wPos(GAME_LEVEL_LEFT_POS + unit->getX(), GAME_LEVEL_TOP_POS + unit->getY(), unit->getScreenSymbol(), unit->getColor());
		pLevel[unit->getY()][unit->getX()] = unit->getMapSymbol();
		
		if (isCollision) {
			if (unit->getId() == ID_GHOST) {
				unit->setMode(Unit::Mode::SELDIR);
			}
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

void Game::selectNewDirection(Unit * unit)
{
	if (unit->getId() == ID_GHOST && unit->getMode() == Unit::SELDIR) {
		unsigned int idx = 0;
		unsigned int possibleDirs[] = { 0, 0, 0, 0 };
		
	}
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
	Csak az�rt friss�ti az adott fal blokkot, hogy a villog� kurzor ne l�tsz�djon.
 */
void Game::refreshEmptyBlock()
{
	pCwm->wPos(GAME_LEVEL_LEFT_POS + emptyBlockX, GAME_LEVEL_TOP_POS + emptyBlockY, ConsoleWindowManager::SYMBOL_SCREEN_WALL_BLOCK, ConsoleWindowManager::COLOR_WALL);
}

//copies -------

//void Game::playerMove(Unit * unit)
//{
//	pCwm->wPos(GAME_LEVEL_LEFT_POS + unit->getX(), GAME_LEVEL_TOP_POS + unit->getY(), ConsoleWindowManager::SYMBOL_EMPTY_BLOCK, 0);
//	pLevel[unit->getY()][unit->getX()] = ConsoleWindowManager::SYMBOL_EMPTY_BLOCK;
//	int currentCoord = 0;
//	switch (unit->getDir()) {
//	case 0:	//up
//		currentCoord = unit->getY();
//		if (!collisionDetection(unit)) {
//			unit->setY(--currentCoord);
//		}
//		break;
//	case 1:	//down
//		currentCoord = unit->getY();
//		if (!collisionDetection(unit)) {
//			unit->setY(++currentCoord);
//		}
//		break;
//	case 2:	//left
//		currentCoord = unit->getX();
//		if (!collisionDetection(unit)) {
//			unit->setX(--currentCoord);
//		}
//		break;
//	case 3:	//right
//		currentCoord = unit->getX();
//		if (!collisionDetection(unit)) {
//			unit->setX(++currentCoord);
//		}
//		break;
//	}
//	pCwm->wPos(GAME_LEVEL_LEFT_POS + unit->getX(), GAME_LEVEL_TOP_POS + unit->getY(), ConsoleWindowManager::SYMBOL_SCREEN_PLAYER, unit->getColor());
//	pLevel[unit->getY()][unit->getX()] = ConsoleWindowManager::SYMBOL_MAP_PLAYER;
//	if (!IS_TIMING_VISIBLE) {
//		refreshEmptyBlock();
//	}
//}