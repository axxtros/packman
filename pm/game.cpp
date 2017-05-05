/*
	Blinky: Red
	Pinky: Pink
	Inky: Blue
	Clyde: Orange
*/

#include "stdafx.h"
#include "game.h"

Game::Game(ConsoleWindowManager* cwm)
{
	this->pCwm = cwm;
	init();
}

Game::~Game()
{
}

void Game::init()
{
	system("cls");
	mPlayerPoint = 0;
	loadScores();
	loadLevel(1);

	getchar();
}

void Game::loadScores()
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
		for (unsigned int i = 0; i != pLevel.size(); i++) {
			for (unsigned int j = 0; j != pLevel[i].length(); j++) {
				//wall
				if (pLevel[i][j] == ConsoleWindowManager::SYMBOL_WALL_BLOCK) {
					pCwm->wPos(GAME_LEVEL_LEFT_POS + j, GAME_LEVEL_TOP_POS + i, ConsoleWindowManager::SYMBOL_FULL_BLOCK, ConsoleWindowManager::COLOR_WALL);
				}
				//dot
				else if (pLevel[i][j] == ConsoleWindowManager::SYMBOL_EMPTY_BLOCK) {
					pCwm->wPos(GAME_LEVEL_LEFT_POS + j, GAME_LEVEL_TOP_POS + i, ConsoleWindowManager::SYMBOL_DOT, ConsoleWindowManager::COLOR_DOT);
				}
				//player
				else if (pLevel[i][j] == ConsoleWindowManager::SYMBOL_PLAYER) {
					pCwm->wPos(GAME_LEVEL_LEFT_POS + j, GAME_LEVEL_TOP_POS + i, ConsoleWindowManager::SYMBOL_GHOST, ConsoleWindowManager::COLOR_PLAYER);
				}
				//ghost: Blinky: Red
				else if (pLevel[i][j] == ConsoleWindowManager::SYMBOL_GHOST_RED) {
					pCwm->wPos(GAME_LEVEL_LEFT_POS + j, GAME_LEVEL_TOP_POS + i, ConsoleWindowManager::SYMBOL_GHOST, ConsoleWindowManager::COLOR_GHOST_RED);
				}
				//ghost: Pinky: Pink
				else if (pLevel[i][j] == ConsoleWindowManager::SYMBOL_GHOST_PINK) {
					pCwm->wPos(GAME_LEVEL_LEFT_POS + j, GAME_LEVEL_TOP_POS + i, ConsoleWindowManager::SYMBOL_GHOST, ConsoleWindowManager::COLOR_GHOST_PINK);
				}
				//ghost: Inky: Blue
				else if (pLevel[i][j] == ConsoleWindowManager::SYMBOL_GHOST_BLUE) {
					pCwm->wPos(GAME_LEVEL_LEFT_POS + j, GAME_LEVEL_TOP_POS + i, ConsoleWindowManager::SYMBOL_GHOST, ConsoleWindowManager::COLOR_GHOST_BLUE);
				}
				//ghost: Clyde: Orange
				else if (pLevel[i][j] == ConsoleWindowManager::SYMBOL_GHOST_ORANGE) {
					pCwm->wPos(GAME_LEVEL_LEFT_POS + j, GAME_LEVEL_TOP_POS + i, ConsoleWindowManager::SYMBOL_GHOST, ConsoleWindowManager::COLOR_GHOST_ORANGE);
				}
			}
		}
	}
	else {			
		pCwm->sPos(0, 0, Util::getTableText(11), 7);			
		std::cin.ignore();
		exit(EXIT_FAILURE);
	}
}
