#pragma once

#ifndef UNIT_H
#define UNIT_H

#include <string>

#include "consoleWindowManager.h"
#include "util.h"

class Unit {	
public:
	/*
	ALIVE - �l, m�k�dik
	DEATH - halott, nincs figyelembe v�ve
	*/
	enum Status { ALIVE, DEATH };
	/*
	SEARCH - keres, k�veti az aktu�lis ir�ny�t
	SELDIR - ir�nyt v�laszt (ha el�gaz�shoz �r, vagy az ir�ny m�r nem tarthat� tov�bb, akkor �j ir�ny v�laszt)
	WAIT - egyhelyben �ll, v�rakozik
	FOLLOW - k�veti a j�t�kost, pontosan arra megy, amerre a j�t�kos
	ANGRY - sokkal gyorsabban SEARCH, vagy FOLLOW, de csak egy bizonyos ideig (0-5 sec.)
	*/
	enum Mode { SEARCH, SELDIR, WAIT, FOLLOW, ANGRY };

private:
	unsigned int id;		//0 = player, !0 = ai
	std::string name;
	unsigned int score;		//player score, if damage this unit
	unsigned int x;			//x coord on the map
	unsigned int y;			//y coord on the map
	unsigned int dir;		//direction (0-up, 1-down, 2-left, 3-right)
	unsigned int color;		//color
	unsigned int speed;		//ai unit speed
	Status currentStatus;
	Mode currentMode;

	std::vector<std::string>* map;	
	//bool isNextFreeBlock();

	char mapSymbol;
	wchar_t screenSymbol;

	unsigned int searchNewDir();
protected:
public:
	Unit(unsigned int, std::string, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, std::vector<std::string>*, char, wchar_t);
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