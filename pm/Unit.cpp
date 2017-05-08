#include "stdafx.h"
#include "Unit.h"

Unit::Unit(std::string _name, unsigned int _score, unsigned int _x, unsigned int _y, unsigned int _dir, unsigned int _color)
{
	this->name = _name;
	this->score = _score;
	this->x = _x;
	this->y = _y;
	this->dir = _dir;
	this->color = _color;
	this->currentMode = SEARCH;
}

Unit::~Unit()
{

}
