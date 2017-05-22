#pragma once

#ifndef MISSILE_H
#define MISSILE_H

#include "gameObject.h"

class Missile : public GameObject {
private:	
	unsigned int damage;	//ammo damage
	unsigned int serialNum;
protected:
public:
	Missile(unsigned int _id, unsigned int _customId, unsigned int _x, unsigned int _y, unsigned int _dir, unsigned int _damage, char _mapSymbol, wchar_t _screenSymbol, unsigned int _color, unsigned int _serialNum, wchar_t _hiddenMapBlock) : GameObject(_id, _customId, _x, _y, _dir, _mapSymbol, _screenSymbol, _color, _hiddenMapBlock) {
		damage = _damage;
		setMapSymbol(_mapSymbol);
		setScreenSymbol(_screenSymbol);
		this->serialNum = _serialNum;
	};
	~Missile() {
		
	};
	void setDamage(unsigned int value) { this->damage = value; };	
	void setSerialNum(unsigned int value) { this->serialNum = value; };
	unsigned int getDamage() { return damage; };
	unsigned int getSerialNum() { return serialNum; };
};

#endif MISSILE_H
