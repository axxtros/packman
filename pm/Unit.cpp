#include "stdafx.h"
#include "Unit.h"

//Unit::Unit(unsigned int _id, std::string _name, unsigned int _score, unsigned int _x, unsigned int _y, unsigned int _dir, unsigned int _color, 
//	unsigned int _speed, std::vector<std::string>* _map, char _mapSymbol, wchar_t _screenSymbol)
//{
//	this->id = _id;
//	this->name = _name;
//	this->score = _score;
//	this->x = _x;
//	this->y = _y;
//	this->dir = _dir;
//	this->color = _color;
//	this->speed = _speed; //+ Util::getRandomNum(5, 200);
//	this->currentStatus = Status::ALIVE;
//	this->currentMode = Mode::MOVE;
//	this->map = _map;
//	this->mapSymbol = _mapSymbol;
//	this->screenSymbol = _screenSymbol;
//	this->speedCounter = 0;
//}

//Unit::~Unit()
//{
//	delete[] &missiles;
//}

void Unit::behaviourCtrl()
{	
	switch (currentMode) {
		case Mode::MOVE:
			searchNewDir();
			if (this->speed != 0 && speedCounter < speed) {		//ha speed = 0, akkor nincs figyelve
				setMode(Mode::WAIT);
			}			
			break;
		case Mode::SELDIR:			
			//setDir(selectNewDir());
			searchNewDir();
			setMode(Mode::MOVE);
			break;
		case Mode::WAIT:
			++speedCounter;
			if (speedCounter == speed) {
				setMode(Mode::MOVE);
				speedCounter = 0;
			}
			break;
		case Mode::FOLLOW: 
			break;
		case Mode::ANGRY: 
			break;
	}	
}

/*
	Ha fel, vagy lefelé megy, akkor csak balra, vagy jobbra keres új irányt.
	Ha balra, vagy jobbra megy, akkor csak felfelé, vagy lefelé keres új irányt.
	Lehetõleg visszafelé nem választ irány, csak akkor, ha beszorul egy olyan helyre, 
	ahonnan nincs más út, csak visszafelé.
	Lehetséges irányváltásnál elöszõr eldönti, hogy legyen-e irányváltás. És ha igen, akkor merre 
	- ha több lehetõség áll fent.
*/
void Unit::searchNewDir() {
	bool isOneWay = false;
	bool isTwoWay = false;
	unsigned int oneWayDir = 0;
	unsigned int twoWayDir = 0;
	
	if (getDir() == DIRECTIONS::UP || getDir() == DIRECTIONS::DOWN) {	//up or down
		unsigned int currX = getX();		
		if(getFreeBlock(getY(), --currX)) {
			isOneWay = true;
			oneWayDir = DIRECTIONS::LEFT;
		}
		currX = getX();		
		if (getFreeBlock(getY(), ++currX)) {
			isTwoWay = true;
			twoWayDir = DIRECTIONS::RIGHT;
		}
	}

	if (getDir() == DIRECTIONS::LEFT || getDir() == DIRECTIONS::RIGHT) {	//left or right
		unsigned int currY = getY();		
		if (getFreeBlock(--currY, getX())) {
			isOneWay = true;
			oneWayDir = DIRECTIONS::UP;
		}
		currY = getY();		
		if (getFreeBlock(++currY, getX())) {
			isTwoWay = true;
			twoWayDir = DIRECTIONS::DOWN;
		}
	}

	if (isOneWay || isTwoWay) {
		bool isWantNewDir = false;									//akar-e irány váltani, vagy sem
		if (getDir() == Mode::SELDIR) {
			isWantNewDir = true;
		}
		else {
			isWantNewDir = Util::getRandTrueOrFalse();
		}		
		if (isWantNewDir) {
			if (isOneWay && isTwoWay) {
				bool selectRandNewDir = Util::getRandTrueOrFalse();
				if (selectRandNewDir)
					setDir(twoWayDir);					
				else
					setDir(oneWayDir);
			}
			else if (isOneWay || isTwoWay) {
				if (isOneWay)
					setDir(oneWayDir);
				else					
					setDir(twoWayDir);
			}
		}
	}	
	else if (!isOneWay && !isTwoWay && getMode() == Mode::SELDIR) {	//ha beszorulna egy olyan helyre, ahonnan csak visszafelé lehet menni
		if (getDir() == DIRECTIONS::UP)
			setDir(DIRECTIONS::DOWN);
		else if(getDir() == DIRECTIONS::DOWN)
			setDir(DIRECTIONS::UP);
		else if (getDir() == DIRECTIONS::LEFT)
			setDir(DIRECTIONS::RIGHT);
		else if (getDir() == DIRECTIONS::RIGHT)
			setDir(DIRECTIONS::LEFT);
	}
}

unsigned int Unit::selectNewDir()
{	
	return Util::getRandomNum(0, 3);
}

bool Unit::addNewMissiles(unsigned int missileId)
{
	unsigned int missileX = getX();
	unsigned int missileY = getY();
	switch (getDir()) {
	case DIRECTIONS::UP: 
		--missileY;
		break;
	case DIRECTIONS::DOWN:
		++missileY;
		break;
	case DIRECTIONS::LEFT:
		--missileX;
		break;
	case DIRECTIONS::RIGHT:
		++missileX;
		break;
	}
	if (getFreeBlock(missileY, missileX)) {
		Missile* missile = new Missile(missileId, Util::getCustomId(), missileX, missileY, getDir(), 10, ConsoleWindowManager::SYMBOL_MAP_MISSILE, ConsoleWindowManager::SYMBOL_MISSILE, ConsoleWindowManager::COLOR_MISSILE, missiles.size());
		missiles.push_back(missile);
		return false;
	}
	return true;
}

bool Unit::getFreeBlock(unsigned int mapY, unsigned int mapX) {
	if ((map[0][mapY][mapX] == ConsoleWindowManager::SYMBOL_EMPTY_BLOCK) || (map[0][mapY][mapX] == ConsoleWindowManager::SYMBOL_SCREEN_DOT))
		return true;
	return false;
}

void Unit::deleteMissiles()
{
	if (!missiles.empty()) {		
		//http://stackoverflow.com/questions/8628951/remove-elements-of-a-vector-inside-the-loop
		for (std::vector<Missile*>::iterator it = missiles.begin(); it != missiles.end(); /*++it*/) {
			if ((*it)->getStatus() == GameObject::DEATH) {
				//delete (*it);
				it = missiles.erase(it);				
			}
			else {
				++it;
			}			
		}
		//missiles.erase(missiles.begin());
	}	
}

