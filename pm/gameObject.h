#pragma once

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "util.h"

class GameObject {	
	public:
		/*
		ALIVE - �l, m�k�dik
		DEATH - halott, nincs figyelembe v�ve
		*/
		enum Status { ALIVE, DEATH };

		/*
		MOVE - halad
		SELDIR - ir�nyt v�laszt (ha el�gaz�shoz �r, vagy az ir�ny m�r nem tarthat� tov�bb, akkor �j ir�ny v�laszt)
		WAIT - egyhelyben �ll, v�rakozik
		FOLLOW - k�veti a j�t�kost, pontosan arra megy, amerre a j�t�kos
		ANGRY - sokkal gyorsabban SEARCH, vagy FOLLOW, de csak egy bizonyos ideig (0-5 sec.)
		*/
		enum Mode { MOVE, SELDIR, WAIT, FOLLOW, ANGRY };		
	protected:		
		Mode currentMode;
	private:
		unsigned int id;		//ID_PLAYER = 0, ID_GHOST = 1, ID_MISSILE = 2
		unsigned int customId;	//egy�ni sorsz�m	
		unsigned int hitPoint;	//�leter�
		unsigned int x;			//x coord on the map
		unsigned int y;			//y coord on the map
		unsigned int startX;	//starting x coord on the map
		unsigned int startY;	//starting y coord on the map
		unsigned int dir;		//direction (0-up, 1-down, 2-left, 3-right)
		unsigned int color;
		char mapSymbol;
		wchar_t screenSymbol;
		Status status;
		wchar_t hiddenSymbolMapBlock;				//annak a t�rk�p mez�nek a k�dja, amit aktu�lisan letakar az adott unit
		unsigned int hiddenSymbolMapBlockColor;		//annak a t�rk�p mez�nek a szine, amit aktu�lisan letakar az adott unit
		unsigned int keyCounter;
	public:
		GameObject() { 
			//NOP...
		};
		GameObject(unsigned int _id, unsigned int _customId, unsigned int _hitPoint, unsigned int _x, unsigned int _y, unsigned int _dir, char _mapSymbol, wchar_t _screenSymbol, unsigned int _color, wchar_t _hiddenMapBlock) : id(_id), customId(_customId), hitPoint(_hitPoint), x(x), y(y), dir(dir), mapSymbol(_mapSymbol), screenSymbol(_screenSymbol), color(_color), hiddenSymbolMapBlock(_hiddenMapBlock) {
			this->id = _id;			
			this->customId = _customId;
			this->hitPoint = _hitPoint;
			this->x = _x;
			this->y = _y;
			this->startX = _x;
			this->startY = _y;
			this->dir = _dir;
			this->color = _color;
			this->mapSymbol = _mapSymbol;
			this->status = Status::ALIVE;
			this->hiddenSymbolMapBlock = _hiddenMapBlock;
			this->keyCounter = 0;
		};
		~GameObject() {
			
		};

		virtual void setId(unsigned int value) { this->id = value; };
		virtual void setCustomId(unsigned int value) { this->customId = value; };
		virtual void setHitPoint(unsigned int value) { this->hitPoint = value; };
		virtual void setX(unsigned int value) { this->x = value; };
		virtual void setY(unsigned int value) { this->y = value; };
		virtual void setDir(unsigned int value) { this->dir = value; };
		void setColor(unsigned int value) { this->color = color; };
		void setMapSymbol(char value) { this->mapSymbol = value; };
		void setScreenSymbol(wchar_t value) { this->screenSymbol = value; };
		virtual void setStatus(Status value) { this->status = value; };
		void setMode(Mode _mode) { this->currentMode = _mode; };
		void setHiddenSymbolMapBlock(wchar_t value) { this->hiddenSymbolMapBlock = value; };
		void setHiddenSymbolMapBlockColor(unsigned int value) { this->hiddenSymbolMapBlockColor = value; };
		void setKeyCounter(unsigned int value) { this->keyCounter = value; };

		virtual unsigned int getId() { return id; };
		virtual unsigned int getCustomId() { return customId; };
		virtual unsigned int getHitPoint() { return hitPoint; };
		virtual unsigned int getX() { return x; };
		virtual unsigned int getY() { return y; };
		virtual unsigned int getDir() { return dir; };
		unsigned int getColor() { return color; };
		char getMapSymbol() { return mapSymbol; };
		wchar_t getScreenSymbol() { return screenSymbol; };
		virtual Status getStatus() { return status; }
		Mode getMode() { return currentMode; };
		void backToStartPoint();
		wchar_t getHiddenSymbolMapBlock() { return this->hiddenSymbolMapBlock; };
		unsigned int getHiddenSymbolMapBlockColor() { return this->hiddenSymbolMapBlockColor; };
		unsigned int getKeyCounter() { return this->keyCounter; };
};

#endif GAMEOBJECT_H
