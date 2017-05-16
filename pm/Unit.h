#pragma once

#ifndef UNIT_H
#define UNIT_H

#include <string>

#include "consoleWindowManager.h"
#include "util.h"
#include "missile.h"
#include "gameObject.h"

class Unit : public GameObject {

	enum DIRECTIONS {
		UP = 0,
		DOWN = 1,
		LEFT = 2,
		RIGHT = 3
	};

private:	
	std::string name;
	unsigned int score;		//player score, if damage this unit	
	unsigned int speed;		//ai unit speed
	unsigned int tmpCoord;
	unsigned int tmpIdx;	
	const std::vector<std::string>* map;
	unsigned int speedCounter;
	std::vector<Missile*> missiles;
	unsigned int selectNewDir();
	void searchNewDir();
	bool getFreeBlock(unsigned int mapY, unsigned int mapX);	
protected:
public:
	Unit::Unit(unsigned int _id, std::string _name, unsigned int _score, unsigned int _x, unsigned int _y, unsigned int _dir, unsigned int _color,
		unsigned int _speed, std::vector<std::string>* _map, char _mapSymbol, wchar_t _screenSymbol) : GameObject(_id, _x, _y, _dir, _mapSymbol, _screenSymbol, _color) {
		this->name = _name;
		this->score = _score;		
		this->speed = _speed; //+ Util::getRandomNum(5, 200);
		currentMode = Mode::MOVE;
		this->map = _map;		
		setMapSymbol(_mapSymbol);
		setScreenSymbol(_screenSymbol);
		this->speedCounter = 0;
		isEmptyMissiles = true;
	};
	
	~Unit() {
		delete[] & missiles;
	}
	
	bool isEmptyMissiles;

	void setScore(unsigned int value) { this->score = value; };
	unsigned int getScore() { return score; };	
	std::vector<Missile*> getMissiles() { return missiles; };
	void behaviourCtrl();
	void addNewMissiles(unsigned int missileId);
	virtual void deleteMissile(unsigned int missileSerialNum);

};

#endif UNIT_H