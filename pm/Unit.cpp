#include "stdafx.h"
#include "Unit.h"

void Unit::behaviourCtrl()
{	
	switch (currentMode) {
		case Mode::MOVE:
			//searchNewDir();
			if (this->speed != 0 && speedCounter < speed) {		//ha speed = 0, akkor nincs figyelve
				setMode(Mode::WAIT);
			}			
			break;
		case Mode::SELDIR:			
			//setDir(selectNewDir());
			//searchNewDir();
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

void Unit::addFireMissile(Missile * missile)
{
	missiles.push_back(missile);
}

unsigned int Unit::selectNewDir()
{	
	return Util::getRandomNum(0, 3);
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

