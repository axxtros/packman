#include "stdafx.h"
#include "Unit.h"

Unit::Unit(unsigned int _id, std::string _name, unsigned int _score, unsigned int _x, unsigned int _y, unsigned int _dir, unsigned int _color, 
	unsigned int _speed, std::vector<std::string>* _map, char _mapSymbol, wchar_t _screenSymbol)
{
	this->id = _id;
	this->name = _name;
	this->score = _score;
	this->x = _x;
	this->y = _y;
	this->dir = _dir;
	this->color = _color;
	this->speed = _speed;
	this->currentStatus = Status::ALIVE;
	this->currentMode = Mode::SEARCH;
	this->map = _map;
	this->mapSymbol = _mapSymbol;
	this->screenSymbol = _screenSymbol;
}

Unit::~Unit()
{

}

void Unit::behaviourCtrl()
{
	switch (currentMode) {
		case Mode::SEARCH:			
				this;
			break;
		case Mode::SELDIR:
			break;
		case Mode::WAIT: 
			break;
		case Mode::FOLLOW: 
			break;
		case Mode::ANGRY: 
			break;
	}	
}

//bool Unit::isNextFreeBlock()
//{	
//	std::string nextBlock = "";	
//	switch (dir) {
//		case 0:	//up			
//			if (y > 0) {
//				--y;
//			}
//			nextBlock = this->map[0][y][x];
//			break;
//		case 1: //down
//			if (y < this->map[0].size()) {
//				++y;
//			}
//			nextBlock = this->map[0][y][x];
//			break;
//		case 2: //left
//			if (x > 0) {
//				--x;
//			}
//			nextBlock = this->map[0][y][x];
//			break;
//		case 3: //right
//			nextBlock = this->map[0][y][++x];
//			break;
//	}
//	if (nextBlock[0] == ConsoleWindowManager::SYMBOL_EMPTY_BLOCK)
//		return true;
//	return false;
//}

unsigned int Unit::searchNewDir()
{
	unsigned int idx = 0;
	unsigned int possibleDirs[4];
	std::string currentBlock = map[x][y];
	if (map[x][--y][0] == ConsoleWindowManager::SYMBOL_EMPTY_BLOCK) {	//up
		possibleDirs[idx] = 0;
		idx++;
	}
	if (map[x][++y][0] == ConsoleWindowManager::SYMBOL_EMPTY_BLOCK) {	//down
		possibleDirs[idx] = 1;
		idx++;
	}
	if (map[--x][y][0] == ConsoleWindowManager::SYMBOL_EMPTY_BLOCK) {	//left
		possibleDirs[idx] = 2;
		idx++;
	}
	if (map[++x][y][0] == ConsoleWindowManager::SYMBOL_EMPTY_BLOCK) {	//right
		possibleDirs[idx] = 3;
		idx++;
	}	
	return Util::getRandomNum(0, idx);
}
