#pragma once

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "util.h"

class GameObject {	
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
	protected:		
		Mode currentMode;
	private:
		unsigned int id;		//ID_PLAYER = 0, ID_GHOST = 1, ID_MISSILE = 2
		unsigned int customId;	
		unsigned int x;			//x coord on the map
		unsigned int y;			//y coord on the map
		unsigned int startX;	//starting x coord on the map
		unsigned int startY;	//starting y coord on the map
		unsigned int dir;		//direction (0-up, 1-down, 2-left, 3-right)
		unsigned int color;
		char mapSymbol;
		wchar_t screenSymbol;
		Status status;
		wchar_t hiddenMapBlock;	//annak a térkép mezõnek a kódja, amit aktuálisan letakar az adott unit
	public:
		GameObject() { 
			//NOP...
		};
		GameObject(unsigned int _id, unsigned int _customId, unsigned int _x, unsigned int _y, unsigned int _dir, char _mapSymbol, wchar_t _screenSymbol, unsigned int _color, wchar_t _hiddenMapBlock) : id(_id), customId(_customId), x(x), y(y), dir(dir), mapSymbol(_mapSymbol), screenSymbol(_screenSymbol), color(_color), hiddenMapBlock(_hiddenMapBlock) {
			this->id = _id;			
			this->customId = _customId;
			this->x = _x;
			this->y = _y;
			this->startX = _x;
			this->startY = _y;
			this->dir = _dir;
			this->color = _color;
			this->mapSymbol = _mapSymbol;
			this->status = Status::ALIVE;
			this->hiddenMapBlock = _hiddenMapBlock;
		};
		~GameObject() {
			
		};

		virtual void setId(unsigned int value) { this->id = value; };
		virtual void setCustomId(unsigned int value) { this->customId = value; };
		virtual void setX(unsigned int value) { this->x = value; };
		virtual void setY(unsigned int value) { this->y = value; };
		virtual void setDir(unsigned int value) { this->dir = value; };
		void setColor(unsigned int value) { this->color = color; };
		void setMapSymbol(char value) { this->mapSymbol = value; };
		void setScreenSymbol(wchar_t value) { this->screenSymbol = value; };
		virtual void setStatus(Status value) { this->status = value; };
		void setMode(Mode _mode) { this->currentMode = _mode; };
		void setHiddenMapBlock(wchar_t value) { this->hiddenMapBlock = value; };
		virtual unsigned int getId() { return id; };
		virtual unsigned int getCustomId() { return customId; };
		virtual unsigned int getX() { return x; };
		virtual unsigned int getY() { return y; };
		virtual unsigned int getDir() { return dir; };
		unsigned int getColor() { return color; };
		char getMapSymbol() { return mapSymbol; };
		wchar_t getScreenSymbol() { return screenSymbol; };
		virtual Status getStatus() { return status; }
		Mode getMode() { return currentMode; };
		void backToStartPoint();
		wchar_t getHiddenMapBlock() { return this->hiddenMapBlock; };
};

#endif GAMEOBJECT_H
