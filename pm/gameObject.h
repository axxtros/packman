#pragma once

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

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
		unsigned int id;		//0 = player, !0 = ai
		unsigned int x;			//x coord on the map
		unsigned int y;			//y coord on the map
		unsigned int dir;		//direction (0-up, 1-down, 2-left, 3-right)
		unsigned int color;
		char mapSymbol;
		wchar_t screenSymbol;
		Status status;			
	public:
		GameObject() { 
			//NOP...
		};
		GameObject(unsigned int _id, unsigned int _x, unsigned int _y, unsigned int _dir, char _mapSymbol, wchar_t _screenSymbol, unsigned int _color) : id(_id), x(x), y(y), dir(dir), mapSymbol(_mapSymbol), screenSymbol(_screenSymbol), color(_color) {
			this->id = _id;
			this->x = _x;
			this->y = _y;
			this->dir = _dir;
			this->color = _color;
			this->mapSymbol = _mapSymbol;
			this->status = Status::ALIVE;
		};
		~GameObject() {
			
		};

		virtual void setId(unsigned int value) { this->id = value; };
		virtual void setX(unsigned int value) { this->x = value; };
		virtual void setY(unsigned int value) { this->y = value; };
		virtual void setDir(unsigned int value) { this->dir = value; };
		void setColor(unsigned int value) { this->color = color; };
		void setMapSymbol(char value) { this->mapSymbol = value; };
		void setScreenSymbol(wchar_t value) { this->screenSymbol = value; };
		virtual void setStatus(Status value) { this->status = value; };
		void setMode(Mode _mode) { this->currentMode = _mode; };		
		virtual unsigned int getId() { return id; };
		virtual unsigned int getX() { return x; };
		virtual unsigned int getY() { return y; };
		virtual unsigned int getDir() { return dir; };
		unsigned int getColor() { return color; };
		char getMapSymbol() { return mapSymbol; };
		wchar_t getScreenSymbol() { return screenSymbol; };
		virtual Status getStatus() { return status; }
		Mode getMode() { return currentMode; };
};

#endif GAMEOBJECT_H
