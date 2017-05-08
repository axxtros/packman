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
	delete redGhost;
	delete pinkGhost;
	delete blueGhost;
	delete orangeGhost;
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
					player = new Unit("", 0, j, i, 0, ConsoleWindowManager::COLOR_PLAYER, 0);
					pCwm->wPos(GAME_LEVEL_LEFT_POS + j, GAME_LEVEL_TOP_POS + i, ConsoleWindowManager::SYMBOL_GHOST, ConsoleWindowManager::COLOR_PLAYER);
				}
				//ghost: Blinky: Red
				else if (pLevel[i][j] == ConsoleWindowManager::SYMBOL_GHOST_RED) {
					redGhost = new Unit(RED_GHOST_NAME, RED_GHOST_SCORE, j, i, Util::getRandomNum(0, 3), Game::COLOR_GHOST_RED, Game::GHOST_DEFAULT_SPEED);
					pCwm->wPos(GAME_LEVEL_LEFT_POS + j, GAME_LEVEL_TOP_POS + i, ConsoleWindowManager::SYMBOL_GHOST, Game::COLOR_GHOST_RED);
				}
				//ghost: Pinky: Pink
				else if (pLevel[i][j] == ConsoleWindowManager::SYMBOL_GHOST_PINK) {
					pinkGhost = new Unit(PINK_GHOST_NAME, PINK_GHOST_SCORE, j, i, Util::getRandomNum(0, 3), Game::COLOR_GHOST_PINK, Game::GHOST_DEFAULT_SPEED);
					pCwm->wPos(GAME_LEVEL_LEFT_POS + j, GAME_LEVEL_TOP_POS + i, ConsoleWindowManager::SYMBOL_GHOST, Game::COLOR_GHOST_PINK);
				}
				//ghost: Inky: Blue
				else if (pLevel[i][j] == ConsoleWindowManager::SYMBOL_GHOST_BLUE) {
					blueGhost = new Unit(BLUE_GHOST_NAME, BLUE_GHOST_SCORE, j, i, Util::getRandomNum(0, 3), Game::COLOR_GHOST_BLUE, Game::GHOST_DEFAULT_SPEED);
					pCwm->wPos(GAME_LEVEL_LEFT_POS + j, GAME_LEVEL_TOP_POS + i, ConsoleWindowManager::SYMBOL_GHOST, Game::COLOR_GHOST_BLUE);
				}
				//ghost: Clyde: Orange
				else if (pLevel[i][j] == ConsoleWindowManager::SYMBOL_GHOST_ORANGE) {
					orangeGhost = new Unit(ORANGE_GHOST_NAME, ORANGE_GHOST_SCORE, j, i, Util::getRandomNum(0, 3), Game::COLOR_GHOST_ORANGE, Game::GHOST_DEFAULT_SPEED);
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
	//player move
	while (gameLoop) {
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
		Sleep(GAME_SPEED);
	}
}

void Game::unitMove(Unit* unit)
{		
	int currentCoord = 0;
	pCwm->wPos(GAME_LEVEL_LEFT_POS + unit->getX(), GAME_LEVEL_TOP_POS + unit->getY(), ConsoleWindowManager::SYMBOL_EMPTY_BLOCK, 0);
	switch (unit->getDir()) {
		case 0:		//up
			currentCoord = unit->getY();
			unit->setY(--currentCoord);
			if (collisionWall(unit)) {
				unit->setY(++currentCoord);				
			}
			break;
		case 1:		//down
			currentCoord = unit->getY();
			unit->setY(++currentCoord);
			if (collisionWall(unit)) {
				unit->setY(--currentCoord);
			}				
			break;
		case 2:		//left
			currentCoord = unit->getX();
			unit->setX(--currentCoord);
			if (collisionWall(unit)) {
				unit->setX(++currentCoord);
			}				
			break;
		case 3:		//right
			currentCoord = unit->getX();
			unit->setX(++currentCoord);
			if (collisionWall(unit)) {
				unit->setX(--currentCoord);
			}				
			break;
	}
	pCwm->wPos(GAME_LEVEL_LEFT_POS + unit->getX(), GAME_LEVEL_TOP_POS + unit->getY(), ConsoleWindowManager::SYMBOL_GHOST, unit->getColor());
	if (!IS_TIMING_VISIBLE) {
		refreshEmptyBlock();
	}
}

bool Game::collisionWall(Unit* const unit)
{
	if (pLevel[unit->getY()][unit->getX()] == ConsoleWindowManager::SYMBOL_WALL_BLOCK)
		return true;
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


