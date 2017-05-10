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

unsigned int Unit::selectNewDir()
{
	return Util::getRandomNum(0, 3);	
}
