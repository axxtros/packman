#pragma once

#ifndef UNIT_H
#define UNIT_H

#include <string>

#include "consoleWindowManager.h"
#include "util.h"
#include "missile.h"
#include "gameObject.h"

class Unit : public GameObject {
public:
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
	unsigned long mMissileNumber;
protected:
public:
	Unit::Unit(unsigned int _id, unsigned int _customId, unsigned int _hitPoint, std::string _name, unsigned int _score, unsigned int _x, unsigned int _y, unsigned int _dir, unsigned int _color,
				unsigned int _speed, std::vector<std::string>* _map, char _mapSymbol, wchar_t _screenSymbol, wchar_t _hiddenMapBlock) :
				GameObject(_id, _customId, _hitPoint, _x, _y, _dir, _mapSymbol, _screenSymbol, _color, _hiddenMapBlock) {
		this->name = _name;
		setHitPoint(_hitPoint);
		this->score = _score;		
		this->speed = _speed;
		currentMode = Mode::MOVE;
		this->map = _map;		
		setMapSymbol(_mapSymbol);
		setScreenSymbol(_screenSymbol);
		this->speedCounter = 0;		
	};
	
	~Unit() {
		delete[] & missiles;
	}
	
	void setScore(unsigned int value) { this->score = value; };
	void setMissileNumber(unsigned int value) { this->mMissileNumber = value; };
	unsigned int getScore() { return score; };	
	unsigned int getMissileNumber() { return mMissileNumber; };
	std::vector<Missile*> getMissiles() { return missiles; };
	void behaviourCtrl();
	void addFireMissile(Missile* missile);
	void addExtraMissile(unsigned int missileNum, const unsigned int maxMissileNum);
	virtual void deleteMissiles();	
};

#endif UNIT_H