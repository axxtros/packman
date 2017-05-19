#include "stdafx.h"
#include "gameObject.h"

void GameObject::backToStartPoint()
{
	this->x = this->startX;
	this->y = this->startY;
	this->status = Status::ALIVE;
}