#pragma once

#ifndef UNIT_H
#define UNIT_H

#include <string>

class Unit {
private:
	std::string name;
	unsigned int score;		//player score, if damage this unit
	unsigned int x;			//x coord on the map
	unsigned int y;			//y coord on the map
	unsigned int dir;		//direction (0-up, 1-down, 2-left, 3-right)
	unsigned int color;		//color
protected:
public:
	Unit(std::string, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);
	~Unit();
	void setScore(unsigned int value) { this->score = value; };
	void setX(unsigned int value) { this->x = value; };
	void setY(unsigned int value) { this->y = value; };
	void setDir(unsigned int value) { this->dir = value; };
	void setColor(unsigned int value) { this->color = color; };
	unsigned int getScore() { return score; };
	unsigned int getX() { return x; };
	unsigned int getY() { return y; };
	unsigned int getDir() { return dir; };
	unsigned int getColor() { return color; };
};

#endif UNIT_H