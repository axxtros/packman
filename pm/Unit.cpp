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
	step = 0;
}

Unit::~Unit()
{

}

void Unit::behaviourCtrl()
{
	switch (currentMode) {
		case Mode::SEARCH:
			step++;
			if (step == 3) {
				searchNewDir();
				step = 0;
			}			
			break;
		case Mode::SELDIR:
			setDir(selectNewDir());
			setMode(Mode::SEARCH);
			break;
		case Mode::WAIT: 
			break;
		case Mode::FOLLOW: 
			break;
		case Mode::ANGRY: 
			break;
	}	
}

void Unit::searchNewDir() {		
	unsigned int possDirs[] = { 0, 0, 0, 0 };
	tmpIdx = 0;
	tmpCoord = y;
	if (dir != 1 && map[0][--tmpCoord][x] == ConsoleWindowManager::SYMBOL_EMPTY_BLOCK) {
		possDirs[0] = 0;
		tmpIdx++;
	}
	tmpCoord = y;
	if (dir != 0 && map[0][++tmpCoord][x] == ConsoleWindowManager::SYMBOL_EMPTY_BLOCK) {
		possDirs[1] = 1;
		tmpIdx++;
	}
	tmpCoord = x;
	if (dir != 3 && map[0][y][--tmpCoord] == ConsoleWindowManager::SYMBOL_EMPTY_BLOCK) {
		possDirs[0] = 2;
		tmpIdx++;
	}
	tmpCoord = x;
	if (dir != 2 && map[0][y][++tmpCoord] == ConsoleWindowManager::SYMBOL_EMPTY_BLOCK) {
		possDirs[1] = 3;
		tmpIdx++;
	}
	//if (dir == 0 || dir == 1) {			//up or down
	//	
	//}
	//else if (dir == 2 || dir == 3) {	//left or right
	//	tmpIdx = 0;
	//	
	//}
	if (tmpIdx != 0 && Util::getRandDecide()) {
		dir = possDirs[Util::getRandomNum(0, tmpIdx)];
	}
}

unsigned int Unit::selectNewDir()
{
	return Util::getRandomNum(0, 3);
}
