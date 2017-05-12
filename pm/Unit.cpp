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
	this->speed = _speed; // +Util::getRandomNum(5, 20);
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
			searchNewDir();
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
	bool isOneWay = false;
	bool isTwoWay = false;
	unsigned int oneWayDir = 0;
	unsigned int twoWayDir = 0;
	
	if (this->dir == 0 || this->dir == 1) {	//up or down
		unsigned int currX = x;
		if (map[0][y][--currX] == ConsoleWindowManager::SYMBOL_EMPTY_BLOCK) {
			isOneWay = true;
			oneWayDir = 2;
		}
		currX = x;
		if (map[0][y][++currX] == ConsoleWindowManager::SYMBOL_EMPTY_BLOCK) {
			isOneWay = true;
			oneWayDir = 3;
		}
	}

	if (this->dir == 2 || this->dir == 3) {	//left or right
		unsigned int currY = y;
		if (map[0][--currY][x] == ConsoleWindowManager::SYMBOL_EMPTY_BLOCK) {
			isOneWay = true;
			oneWayDir = 0;
		}
		currY = y;
		if (map[0][++currY][x] == ConsoleWindowManager::SYMBOL_EMPTY_BLOCK) {
			isTwoWay = true;
			oneWayDir = 1;
		}
	}

	if (isOneWay || isTwoWay) {
		bool isWantNewDir = Util::getRandTrueOrFalse();
		if (isWantNewDir) {
			if (isOneWay && isTwoWay) {
				bool selectRandNewDir = Util::getRandTrueOrFalse();
				if(selectRandNewDir)
					this->dir = twoWayDir;
					
				else
					this->dir = oneWayDir;
			}
			else if (isOneWay || isTwoWay) {
				if (isOneWay)
					this->dir = twoWayDir;
				else
					
				this->dir = oneWayDir;
			}
		}
	}		
}

unsigned int Unit::selectNewDir()
{
	return Util::getRandomNum(0, 3);
}
