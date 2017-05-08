#include "stdafx.h"
#include "Unit.h"

Unit::Unit(std::string _name, unsigned int _score, unsigned int _x, unsigned int _y, unsigned int _dir, unsigned int _color, unsigned int _speed)
{
	this->name = _name;
	this->score = _score;
	this->x = _x;
	this->y = _y;
	this->dir = _dir;
	this->color = _color;
	this->speed = _speed;
	this->currentStatus = Status::ALIVE;
	this->currentMode = Mode::SEARCH;
}

Unit::~Unit()
{

}
