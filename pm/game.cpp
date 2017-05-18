#include "stdafx.h"
#include "game.h"
#include "missile.h"

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
		for (unsigned int mapY = 0; mapY != pLevel.size(); mapY++) {
			for (unsigned int mapX = 0; mapX != pLevel[mapY].length(); mapX++) {
				//wall
				if (pLevel[mapY][mapX] == ConsoleWindowManager::SYMBOL_MAP_WALL_BLOCK) {
					pCwm->wPos(GAME_LEVEL_LEFT_POS + mapX, GAME_LEVEL_TOP_POS + mapY, ConsoleWindowManager::SYMBOL_SCREEN_WALL_BLOCK, ConsoleWindowManager::COLOR_WALL);
					if (firstWallBlock) {	//ezt a blokkot frissít 'üresen', hogy a villogó kurzor ne legyen 'szem elõtt'
						emptyBlockX = mapX;
						emptyBlockY = mapY;
						firstWallBlock = false;
					}
				}
				//dot
				else if (pLevel[mapY][mapX] == ConsoleWindowManager::SYMBOL_EMPTY_BLOCK) {
					pCwm->wPos(GAME_LEVEL_LEFT_POS + mapX, GAME_LEVEL_TOP_POS + mapY, ConsoleWindowManager::SYMBOL_SCREEN_DOT, ConsoleWindowManager::COLOR_DOT);
				}
				//player
				else if (pLevel[mapY][mapX] == ConsoleWindowManager::SYMBOL_MAP_PLAYER && !isPlayerDone) {
					player = new Unit(ID_PLAYER, "", 0, mapX, mapY, 0, ConsoleWindowManager::COLOR_PLAYER, 0, &pLevel, ConsoleWindowManager::SYMBOL_MAP_PLAYER, ConsoleWindowManager::SYMBOL_SCREEN_PLAYER);
					pCwm->wPos(GAME_LEVEL_LEFT_POS + mapX, GAME_LEVEL_TOP_POS + mapY, ConsoleWindowManager::SYMBOL_SCREEN_PLAYER, ConsoleWindowManager::COLOR_PLAYER);
					isPlayerDone = true;
				}
				//ghost: Blinky: Red
				else if (pLevel[mapY][mapX] == ConsoleWindowManager::SYMBOL_MAP_GHOST_RED) {
					ghost = new Unit(ID_GHOST, RED_GHOST_NAME, RED_GHOST_SCORE, mapX, mapY, Util::getRandomNum(0, 3), Game::COLOR_GHOST_RED, Game::SPEED_MAX, &pLevel, ConsoleWindowManager::SYMBOL_MAP_GHOST_RED, ConsoleWindowManager::SYMBOL_SCREEN_GHOST);
					ghosts.push_back(ghost);
					pCwm->wPos(GAME_LEVEL_LEFT_POS + mapX, GAME_LEVEL_TOP_POS + mapY, ConsoleWindowManager::SYMBOL_SCREEN_GHOST, Game::COLOR_GHOST_RED);
				}
				//ghost: Pinky: Pink
				else if (pLevel[mapY][mapX] == ConsoleWindowManager::SYMBOL_MAP_GHOST_PINK) {
					ghost = new Unit(ID_GHOST, PINK_GHOST_NAME, PINK_GHOST_SCORE, mapX, mapY, Util::getRandomNum(0, 3), Game::COLOR_GHOST_PINK, Game::SPEED_NORMAL, &pLevel, ConsoleWindowManager::SYMBOL_MAP_GHOST_PINK, ConsoleWindowManager::SYMBOL_SCREEN_GHOST);
					ghosts.push_back(ghost);
					pCwm->wPos(GAME_LEVEL_LEFT_POS + mapX, GAME_LEVEL_TOP_POS + mapY, ConsoleWindowManager::SYMBOL_SCREEN_GHOST, Game::COLOR_GHOST_PINK);
				}
				//ghost: Inky: Blue
				else if (pLevel[mapY][mapX] == ConsoleWindowManager::SYMBOL_MAP_GHOST_BLUE) {
					ghost = new Unit(ID_GHOST, BLUE_GHOST_NAME, BLUE_GHOST_SCORE, mapX, mapY, Util::getRandomNum(0, 3), Game::COLOR_GHOST_BLUE, Game::SPEED_EASY, &pLevel, ConsoleWindowManager::SYMBOL_MAP_GHOST_BLUE, ConsoleWindowManager::SYMBOL_SCREEN_GHOST);
					ghosts.push_back(ghost);
					pCwm->wPos(GAME_LEVEL_LEFT_POS + mapX, GAME_LEVEL_TOP_POS + mapY, ConsoleWindowManager::SYMBOL_SCREEN_GHOST, Game::COLOR_GHOST_BLUE);
				}
				//ghost: Clyde: Orange
				else if (pLevel[mapY][mapX] == ConsoleWindowManager::SYMBOL_MAP_GHOST_ORANGE) {
					ghost = new Unit(ID_GHOST, ORANGE_GHOST_NAME, ORANGE_GHOST_SCORE, mapX, mapY, Util::getRandomNum(0, 3), Game::COLOR_GHOST_ORANGE, Game::SPEED_SLOW, &pLevel, ConsoleWindowManager::SYMBOL_MAP_GHOST_ORANGE, ConsoleWindowManager::SYMBOL_SCREEN_GHOST);
					ghosts.push_back(ghost);
					pCwm->wPos(GAME_LEVEL_LEFT_POS + mapX, GAME_LEVEL_TOP_POS + mapY, ConsoleWindowManager::SYMBOL_SCREEN_GHOST, Game::COLOR_GHOST_ORANGE);
				}
				//unknow character -> SYMBOL_EMPTY_BLOCK
				else {
					pLevel[mapY][mapX] = ConsoleWindowManager::SYMBOL_EMPTY_BLOCK;
					pCwm->wPos(GAME_LEVEL_LEFT_POS + mapX, GAME_LEVEL_TOP_POS + mapY, ConsoleWindowManager::SYMBOL_SCREEN_DOT, ConsoleWindowManager::COLOR_DOT);					
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

	isMissileReady = true;
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
		//fire
		if (isKeydown(VK_SPACE) && isMissileReady) { 			
 			isMissileReady = player->addNewMissiles(ID_MISSILE);
		}
		//player missile move
		if (!player->getMissiles().empty()) {
			for (tmpIdx = 0; tmpIdx != player->getMissiles().size(); tmpIdx++) {								
				if (player->getMissiles()[tmpIdx]->getStatus() == GameObject::ALIVE ) {
					unitMove(player->getMissiles()[tmpIdx]);
				}				
			}
		}
		//ai ghosts move
		if (!ghosts.empty()) {
			for (tmpIdx = 0; tmpIdx != ghosts.size(); tmpIdx++) {
				unitMove(ghosts[tmpIdx]);
				ghosts[tmpIdx]->behaviourCtrl();
			}
		}
		//gameloop végén elvégzendõ mûveletek
		player->deleteMissiles();

		Sleep(GAME_SPEED);
	}
}

void Game::unitMove(GameObject * unit)
{	
	bool isCollision = false;
	if ((unit->getId() == ID_GHOST && (unit->getMode() == Unit::MOVE))  || (unit->getId() == ID_PLAYER) ) {
		
		pCwm->wPos(GAME_LEVEL_LEFT_POS + unit->getX(), GAME_LEVEL_TOP_POS + unit->getY(), ConsoleWindowManager::SYMBOL_EMPTY_BLOCK, 0);
		pLevel[unit->getY()][unit->getX()] = ConsoleWindowManager::SYMBOL_EMPTY_BLOCK;
		
		int currentCoord = 0;
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

	if (unit->getId() == ID_MISSILE) {

		pCwm->wPos(GAME_LEVEL_LEFT_POS + unit->getX(), GAME_LEVEL_TOP_POS + unit->getY(), ConsoleWindowManager::SYMBOL_EMPTY_BLOCK, 0);
		pLevel[unit->getY()][unit->getX()] = ConsoleWindowManager::SYMBOL_EMPTY_BLOCK;

		if (!collisionDetection(unit)) {
			unsigned int curr = 0;
			switch (unit->getDir()) {
			case 0: 
				curr = unit->getY();
				unit->setY(--curr);
				break;
			case 1: 				
				curr = unit->getY();
				unit->setY(++curr);
				break;
			case 2: 
				curr = unit->getX();
				unit->setX(--curr);
				break;
			case 3: 
				curr = unit->getX();
				unit->setX(++curr);
				break;
			}			
		}
		else {
			isCollision = true;
		}
		pCwm->wPos(GAME_LEVEL_LEFT_POS + unit->getX(), GAME_LEVEL_TOP_POS + unit->getY(), unit->getScreenSymbol(), unit->getColor());
		pLevel[unit->getY()][unit->getX()] = unit->getMapSymbol();
		if (isCollision) {						
			pCwm->wPos(GAME_LEVEL_LEFT_POS + unit->getX(), GAME_LEVEL_TOP_POS + unit->getY(), ConsoleWindowManager::SYMBOL_EMPTY_BLOCK, 0);
			pLevel[unit->getY()][unit->getX()] = ConsoleWindowManager::SYMBOL_EMPTY_BLOCK;
		 	
			Missile * rMissile = dynamic_cast<Missile*>(unit);
			rMissile->setStatus(rMissile->DEATH);			
			//player->deleteMissile(rMissile->getSerialNum());
			isMissileReady = true;
		}
	}
}

bool Game::collisionDetection(GameObject* const unit)
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
	pCwm->sPos(GAME_LEVEL_LEFT_POS, GAME_LEVEL_TOP_POS + pLevel.size(), Util::getTableText(12) + " " + std::to_string(score));	//score
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