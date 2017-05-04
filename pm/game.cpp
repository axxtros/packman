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
	unsigned int lineNum = 0;
	std::ifstream file(LEVEL_FILE);
	std::string line;
	while (std::getline(file, line)) {
		if (line.length() > 0) {
			for (unsigned int i = 0; i != line.length(); i++) {
				//wall
				if (line[i] == ConsoleWindowManager::SYMBOL_WALL_BLOCK) {
					//pLevelVector[lineNum][i] = ConsoleWindowManager::SYMBOL_WALL_BLOCK;
					//pLevelVector[lineNum].push_back(ConsoleWindowManager::SYMBOL_WALL_BLOCK);
					pCwm->wPos(GAME_LEVEL_LEFT_POS + i, GAME_LEVEL_TOP_POS + lineNum, ConsoleWindowManager::SYMBOL_FULL_BLOCK, ConsoleWindowManager::COLOR_WALL);
				}
				//dot
				else if (line[i] == ConsoleWindowManager::SYMBOL_EMPTY_BLOCK) {
					//pLevelVector[lineNum][i] = ConsoleWindowManager::SYMBOL_EMPTY_BLOCK;
					pCwm->wPos(GAME_LEVEL_LEFT_POS + i, GAME_LEVEL_TOP_POS + lineNum, ConsoleWindowManager::SYMBOL_DOT, ConsoleWindowManager::COLOR_DOT);
				}
				//player
				else if (line[i] == ConsoleWindowManager::SYMBOL_PLAYER) {
					//pLevelVector[lineNum][i] = ConsoleWindowManager::SYMBOL_PLAYER;
					pCwm->wPos(GAME_LEVEL_LEFT_POS + i, GAME_LEVEL_TOP_POS + lineNum, ConsoleWindowManager::SYMBOL_GHOST, ConsoleWindowManager::COLOR_PLAYER);
				}
				//ghost: Blinky: Red
				else if (line[i] == ConsoleWindowManager::SYMBOL_GHOST_RED) {
					//pLevelVector[lineNum][i] = ConsoleWindowManager::SYMBOL_GHOST_RED;
					pCwm->wPos(GAME_LEVEL_LEFT_POS + i, GAME_LEVEL_TOP_POS + lineNum, ConsoleWindowManager::SYMBOL_GHOST, ConsoleWindowManager::COLOR_GHOST_RED);
				}
				//ghost: Pinky: Pink
				else if (line[i] == ConsoleWindowManager::SYMBOL_GHOST_PINK) {
					//pLevelVector[lineNum][i] = ConsoleWindowManager::SYMBOL_GHOST_PINK;
					pCwm->wPos(GAME_LEVEL_LEFT_POS + i, GAME_LEVEL_TOP_POS + lineNum, ConsoleWindowManager::SYMBOL_GHOST, ConsoleWindowManager::COLOR_GHOST_PINK);
				}
				//ghost: Inky: Blue
				else if (line[i] == ConsoleWindowManager::SYMBOL_GHOST_BLUE) {
					//pLevelVector[lineNum][i] = ConsoleWindowManager::SYMBOL_GHOST_BLUE;
					pCwm->wPos(GAME_LEVEL_LEFT_POS + i, GAME_LEVEL_TOP_POS + lineNum, ConsoleWindowManager::SYMBOL_GHOST, ConsoleWindowManager::COLOR_GHOST_BLUE);
				}
				//ghost: Clyde: Orange
				else if (line[i] == ConsoleWindowManager::SYMBOL_GHOST_ORANGE) {
					//pLevelVector[lineNum][i] = ConsoleWindowManager::SYMBOL_GHOST_ORANGE;
					pCwm->wPos(GAME_LEVEL_LEFT_POS + i, GAME_LEVEL_TOP_POS + lineNum, ConsoleWindowManager::SYMBOL_GHOST, ConsoleWindowManager::COLOR_GHOST_ORANGE);
				}
			}
		}
		lineNum++;
	}
}
