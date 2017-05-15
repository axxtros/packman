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
	this->currentMode = Mode::MOVE;
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
		case Mode::MOVE:
			searchNewDir();
			break;
		case Mode::SELDIR:			
			setDir(selectNewDir());
			//searchNewDir();
			setMode(Mode::MOVE);
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
		if(getFreeBlock(y, --currX)) {
			isOneWay = true;
			oneWayDir = 2;
		}
		currX = x;		
		if (getFreeBlock(y, ++currX)) {
			isTwoWay = true;
			twoWayDir = 3;
		}
	}

	if (this->dir == 2 || this->dir == 3) {	//left or right
		unsigned int currY = y;		
		if (getFreeBlock(--currY, x)) {
			isOneWay = true;
			oneWayDir = 0;
		}
		currY = y;		
		if (getFreeBlock(++currY, x)) {
			isTwoWay = true;
			twoWayDir = 1;
		}
	}

	if (isOneWay || isTwoWay) {
		bool isWantNewDir = false;
		if (getDir() == Mode::SELDIR) {
			isWantNewDir = true;
		}
		else {
			isWantNewDir = Util::getRandTrueOrFalse();
		}		
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
					this->dir = oneWayDir;
				else					
					this->dir = twoWayDir;
			}
		}
	}		
}

unsigned int Unit::selectNewDir()
{
	return Util::getRandomNum(0, 3);
}

bool Unit::getFreeBlock(unsigned int mapY, unsigned int mapX) {
	if ( (map[0][mapY][mapX] == ConsoleWindowManager::SYMBOL_EMPTY_BLOCK) || (map[0][mapY][mapX] == ConsoleWindowManager::SYMBOL_SCREEN_DOT) )
		return true;
	return false;
}