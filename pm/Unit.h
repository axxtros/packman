#pragma once

#ifndef UNIT_H
#define UNIT_H

#include <string>

#include "consoleWindowManager.h"
#include "util.h"

class Unit {	
public:
	/*
	ALIVE - él, mûködik
	DEATH - halott, nincs figyelembe véve
	*/
	enum Status { ALIVE, DEATH };
	/*
	MOVE - halad
	SELDIR - irányt választ (ha elágazáshoz ér, vagy az irány már nem tartható tovább, akkor új irány választ)
	WAIT - egyhelyben áll, várakozik
	FOLLOW - követi a játékost, pontosan arra megy, amerre a játékos
	ANGRY - sokkal gyorsabban SEARCH, vagy FOLLOW, de csak egy bizonyos ideig (0-5 sec.)
	*/
	enum Mode { MOVE, SELDIR, WAIT, FOLLOW, ANGRY };

private:
	unsigned int id;		//0 = player, !0 = ai
	std::string name;
	unsigned int score;		//player score, if damage this unit
	unsigned int x;			//x coord on the map
	unsigned int y;			//y coord on the map
	unsigned int dir;		//direction (0-up, 1-down, 2-left, 3-right)
	unsigned int color;		//color
	unsigned int speed;		//ai unit speed
	unsigned int tmpCoord;
	unsigned int tmpIdx;
	Status currentStatus;
	Mode currentMode;
	const std::vector<std::string>* map;	
	char mapSymbol;
	wchar_t screenSymbol;

	unsigned int selectNewDir();
	void searchNewDir();	
	bool getFreeBlock(unsigned int mapY, unsigned int mapX);
	bool isImpasse(unsigned int mapY, unsigned int mapX);
protected:
public:
	Unit::Unit(unsigned int _id, std::string _name, unsigned int _score, unsigned int _x, unsigned int _y, unsigned int _dir, unsigned int _color,
		unsigned int _speed, std::vector<std::string>* _map, char _mapSymbol, wchar_t _screenSymbol);
	~Unit();	

	void setId(unsigned int value) { this->id = value; };
	void setScore(unsigned int value) { this->score = value; };
	void setX(unsigned int value) { this->x = value; };
	void setY(unsigned int value) { this->y = value; };
	void setDir(unsigned int value) { this->dir = value; };
	void setColor(unsigned int value) { this->color = color; };
	void setStatus(Status _status) { this->currentStatus = _status; };
	void setMode(Mode _mode) { this->currentMode = _mode; };
	void setMapSymbol(char value) { this->mapSymbol = value; };
	void setScreenSymbol(wchar_t value) { this->screenSymbol = value; };
	unsigned int getId() { return id; };
	unsigned int getScore() { return score; };
	unsigned int getX() { return x; };
	unsigned int getY() { return y; };
	unsigned int getDir() { return dir; };
	unsigned int getColor() { return color; };
	char getMapSymbol() { return mapSymbol; };
	wchar_t getScreenSymbol() { return screenSymbol; };
	Status getStatus() { return currentStatus; };
	Mode getMode() { return currentMode; };
	void behaviourCtrl();
};

#endif UNIT_H