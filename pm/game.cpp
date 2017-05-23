#include "stdafx.h"
#include "game.h"
#include "missile.h"

Game::Game(ConsoleWindowManager* cwm)
{
	this->pCwm = cwm;
	init();
}

Game::~Game()
{	
	delete player;
	delete[] &ghosts;
	delete ghost;
}

void Game::init()
{	
	system("cls");	
	loadMapUnits();
	loadLevel(1);
	runGameLoop = true;
	gameLoop();
	getchar();
}

void Game::restart()
{
	runGameLoop = false;
	player = nullptr;
	delete player;
	if (!ghosts.empty()) {
		for (tmpIdx = 0; tmpIdx != ghosts.size(); tmpIdx++) {
			ghosts[tmpIdx] = nullptr;
			delete ghosts[tmpIdx];
		}
	}	
	ghosts.clear();;
	ghost = nullptr;
	delete ghost;	
	pLevel.clear();	
	init();
}

void Game::loadMapUnits()
{
	std::ifstream file(SCORES_FILE);
	std::string line;
	while (std::getline(file, line)) {
		std::size_t found = line.find(ConsoleWindowManager::SYMBOL_FILE_LINE_SEPARATOR);
		mScores[line.substr(0, found)] = std::stoi(line.substr((found + 1), line.length()));
	}
}

void Game::loadLevel(const unsigned int level)
{		
	std::string fileName = LEVEL_FILE_DIR + std::to_string(level) + LEVEL_FILE_EXT;
	std::ifstream file(fileName, std::fstream::in | std::fstream::out | std::fstream::app);
	std::string line;
	while (std::getline(file, line)) {
		pLevel.push_back(line);
	}
	if (pLevel.size() > 0) {
		bool firstWallBlock = true;
		bool isPlayerDone = false;

		for (unsigned int mapY = 0; mapY != pLevel.size(); mapY++) {
			for (unsigned int mapX = 0; mapX != pLevel[mapY].length(); mapX++) {
				//wall
				if (pLevel[mapY][mapX] == ConsoleWindowManager::SYMBOL_MAP_WALL_BLOCK) {
					pCwm->wPos(GAME_LEVEL_LEFT_POS + mapX, GAME_LEVEL_TOP_POS + mapY, ConsoleWindowManager::SYMBOL_SCREEN_WALL_BLOCK, ConsoleWindowManager::COLOR_WALL);
					if (firstWallBlock) {	//ezt a blokkot frissít 'üresen', hogy a villogó kurzor ne legyen 'szem előtt'
						emptyBlockX = mapX;
						emptyBlockY = mapY;
						firstWallBlock = false;
					}					
				}
				//dot
				else if (pLevel[mapY][mapX] == ConsoleWindowManager::SYMBOL_EMPTY_BLOCK) {
					pCwm->wPos(GAME_LEVEL_LEFT_POS + mapX, GAME_LEVEL_TOP_POS + mapY, ConsoleWindowManager::SYMBOL_SCREEN_DOT, ConsoleWindowManager::COLOR_DOT);					
				}
				//ammo box
				else if (pLevel[mapY][mapX] == ConsoleWindowManager::SYMBOL_MAP_AMMO_BOX) {
					pCwm->wPos(GAME_LEVEL_LEFT_POS + mapX, GAME_LEVEL_TOP_POS + mapY, ConsoleWindowManager::SYMBOL_SCREEN_AMMO_BOX, ConsoleWindowManager::COLOR_AMMO_BOX);					
				}
				//player
				else if (pLevel[mapY][mapX] == ConsoleWindowManager::SYMBOL_MAP_PLAYER && !isPlayerDone) {
					player = new Unit(ID_PLAYER, Util::getCustomId(), "", 0, mapX, mapY, 0, ConsoleWindowManager::COLOR_PLAYER, 0, &pLevel, ConsoleWindowManager::SYMBOL_MAP_PLAYER, ConsoleWindowManager::SYMBOL_SCREEN_PLAYER, ConsoleWindowManager::SYMBOL_EMPTY_BLOCK);
					player->setMissileNumber(DEFAULT_MISSILE_NUMBER);
					pCwm->wPos(GAME_LEVEL_LEFT_POS + mapX, GAME_LEVEL_TOP_POS + mapY, ConsoleWindowManager::SYMBOL_SCREEN_PLAYER, ConsoleWindowManager::COLOR_PLAYER);
					isPlayerDone = true;					
				}
				//ghost: Blinky: Red
				else if (pLevel[mapY][mapX] == ConsoleWindowManager::SYMBOL_MAP_GHOST_RED) {
					ghost = new Unit(ID_GHOST, Util::getCustomId(), RED_GHOST_NAME, RED_GHOST_SCORE, mapX, mapY, Util::getRandomNum(0, 3), Game::COLOR_GHOST_RED, Game::SPEED_MAX, &pLevel, ConsoleWindowManager::SYMBOL_MAP_GHOST_RED, ConsoleWindowManager::SYMBOL_SCREEN_GHOST, ConsoleWindowManager::SYMBOL_SCREEN_DOT);
					ghosts.push_back(ghost);
					pCwm->wPos(GAME_LEVEL_LEFT_POS + mapX, GAME_LEVEL_TOP_POS + mapY, ConsoleWindowManager::SYMBOL_SCREEN_GHOST, Game::COLOR_GHOST_RED);					
				}
				//ghost: Pinky: Pink
				else if (pLevel[mapY][mapX] == ConsoleWindowManager::SYMBOL_MAP_GHOST_PINK) {
					ghost = new Unit(ID_GHOST, Util::getCustomId(), PINK_GHOST_NAME, PINK_GHOST_SCORE, mapX, mapY, Util::getRandomNum(0, 3), Game::COLOR_GHOST_PINK, Game::SPEED_NORMAL, &pLevel, ConsoleWindowManager::SYMBOL_MAP_GHOST_PINK, ConsoleWindowManager::SYMBOL_SCREEN_GHOST, ConsoleWindowManager::SYMBOL_SCREEN_DOT);
					ghosts.push_back(ghost);
					pCwm->wPos(GAME_LEVEL_LEFT_POS + mapX, GAME_LEVEL_TOP_POS + mapY, ConsoleWindowManager::SYMBOL_SCREEN_GHOST, Game::COLOR_GHOST_PINK);					
				}
				//ghost: Inky: Blue
				else if (pLevel[mapY][mapX] == ConsoleWindowManager::SYMBOL_MAP_GHOST_BLUE) {
					ghost = new Unit(ID_GHOST, Util::getCustomId(), BLUE_GHOST_NAME, BLUE_GHOST_SCORE, mapX, mapY, Util::getRandomNum(0, 3), Game::COLOR_GHOST_BLUE, Game::SPEED_EASY, &pLevel, ConsoleWindowManager::SYMBOL_MAP_GHOST_BLUE, ConsoleWindowManager::SYMBOL_SCREEN_GHOST, ConsoleWindowManager::SYMBOL_SCREEN_DOT);
					ghosts.push_back(ghost);
					pCwm->wPos(GAME_LEVEL_LEFT_POS + mapX, GAME_LEVEL_TOP_POS + mapY, ConsoleWindowManager::SYMBOL_SCREEN_GHOST, Game::COLOR_GHOST_BLUE);					
				}
				//ghost: Clyde: Orange
				else if (pLevel[mapY][mapX] == ConsoleWindowManager::SYMBOL_MAP_GHOST_ORANGE) {
					ghost = new Unit(ID_GHOST, Util::getCustomId(), ORANGE_GHOST_NAME, ORANGE_GHOST_SCORE, mapX, mapY, Util::getRandomNum(0, 3), Game::COLOR_GHOST_ORANGE, Game::SPEED_SLOW, &pLevel, ConsoleWindowManager::SYMBOL_MAP_GHOST_ORANGE, ConsoleWindowManager::SYMBOL_SCREEN_GHOST, ConsoleWindowManager::SYMBOL_SCREEN_DOT);
					ghosts.push_back(ghost);
					pCwm->wPos(GAME_LEVEL_LEFT_POS + mapX, GAME_LEVEL_TOP_POS + mapY, ConsoleWindowManager::SYMBOL_SCREEN_GHOST, Game::COLOR_GHOST_ORANGE);					
				}
				//unknow character -> SYMBOL_EMPTY_BLOCK
				else {
					pLevel[mapY][mapX] = ConsoleWindowManager::SYMBOL_EMPTY_BLOCK;
					pCwm->wPos(GAME_LEVEL_LEFT_POS + mapX, GAME_LEVEL_TOP_POS + mapY, ConsoleWindowManager::SYMBOL_SCREEN_DOT, ConsoleWindowManager::COLOR_DOT);					
				}
			}
		}		
		refreshPlayerBullets(player->getMissileNumber());
	}
	else {			
		pCwm->sPos(0, 0, Util::getTableText(11), 7);			
		std::cin.ignore();
		exit(EXIT_FAILURE);
	}
}

void Game::gameLoop()
{
	if (IS_TIMING_VISIBLE) {
		std::thread timeThread([this] { this->timeCounter(); });
		timeThread.detach();
	}	

	isMissileReady = true;	
	while (runGameLoop) {
		//player move
		if (isKeydown(VK_UP)) {			
			player->setDir(0);
			unitMove(player);
		}
		if (isKeydown(VK_DOWN)) {
			player->setDir(1);
			unitMove(player);
		}
		if (isKeydown(VK_LEFT)) {
			player->setDir(2);
			unitMove(player);
		}
		if (isKeydown(VK_RIGHT)) {
			player->setDir(3);
			unitMove(player);
		}
		//player fire
		if (isKeydown(VK_SPACE) && isMissileReady) {
			if (player->getMissileNumber() > 0) {
				isMissileReady = fireMissile(player);
				if (!Game::isInfiniteMissile) {
					player->setMissileNumber(player->getMissileNumber() - 1);
				}					
				refreshPlayerBullets(player->getMissileNumber());
			}			
		}
		//restart game
		if (isKeydown(VK_F1)) {			
			restart();
		}
		//player missile move
		if (!player->getMissiles().empty()) {
			for (tmpIdx = 0; tmpIdx != player->getMissiles().size(); tmpIdx++) {								
				if (player->getMissiles()[tmpIdx]->getStatus() == GameObject::ALIVE ) {
					unitMove(player->getMissiles()[tmpIdx]);
				}				
			}
		}
		//ai ghosts move
		if (!ghosts.empty()) {
			for (tmpIdx = 0; tmpIdx != ghosts.size(); tmpIdx++) {
				if (ghosts[tmpIdx]->getStatus() == GameObject::ALIVE) {
					unitMove(ghosts[tmpIdx]);
					ghostSearchNewDir(ghosts[tmpIdx]);
					ghosts[tmpIdx]->behaviourCtrl();
				} else if (ghosts[tmpIdx]->getStatus() == GameObject::DEATH) {					
					pCwm->wPos(GAME_LEVEL_LEFT_POS + ghosts[tmpIdx]->getX(), GAME_LEVEL_TOP_POS + ghosts[tmpIdx]->getY(), ConsoleWindowManager::SYMBOL_EMPTY_BLOCK, 0);
					pLevel[ghosts[tmpIdx]->getY()][ghosts[tmpIdx]->getX()] = ConsoleWindowManager::SYMBOL_EMPTY_BLOCK;					
					ghosts[tmpIdx]->backToStartPoint();
				}
			}
		}
		//gameloop végén elvégzendő műveletek
		player->deleteMissiles();
		
		Sleep(GAME_SPEED);
	}
}

void Game::unitMove(GameObject * unit)
{	
	bool isCollision = false;
	if ((unit->getId() == ID_GHOST && (unit->getMode() == Unit::MOVE) && (unit->getStatus() == Unit::ALIVE))  || (unit->getId() == ID_PLAYER) ) {
		
		if (unit->getId() == ID_GHOST) {
			pCwm->wPos(GAME_LEVEL_LEFT_POS + unit->getX(), GAME_LEVEL_TOP_POS + unit->getY(), unit->getHiddenSymbolMapBlock(), unit->getHiddenSymbolMapBlockColor());
			pLevel[unit->getY()][unit->getX()] = unit->getHiddenSymbolMapBlock();
		}
		else if (unit->getId() == ID_PLAYER) {
			pCwm->wPos(GAME_LEVEL_LEFT_POS + unit->getX(), GAME_LEVEL_TOP_POS + unit->getY(), ConsoleWindowManager::SYMBOL_EMPTY_BLOCK, ConsoleWindowManager::COLOR_EMPTY);
			pLevel[unit->getY()][unit->getX()] = ConsoleWindowManager::SYMBOL_EMPTY_BLOCK;
		}
		
		int currentCoord = 0;
		switch (unit->getDir()) {
		case 0:	//up
			currentCoord = unit->getY();
			if (!collisionDetection(unit)) {
				unit->setY(--currentCoord);								
			}
			else {
				isCollision = true;
			}
			break;
		case 1:	//down
			currentCoord = unit->getY();
			if (!collisionDetection(unit)) {
				unit->setY(++currentCoord);						
			}
			else {
				isCollision = true;
			}
			break;
		case 2:	//left
			currentCoord = unit->getX();
			if (!collisionDetection(unit)) {
				unit->setX(--currentCoord);				
			}
			else {
				isCollision = true;
			}
			break;
		case 3:	//right
			currentCoord = unit->getX();
			if (!collisionDetection(unit)) {
				unit->setX(++currentCoord);				
			}
			else {
				isCollision = true;
			}
			break;		
		}
				
		//ghos esetében eltárolja, hogy milyen térkép block-ot takar el aktuálisan a unit (+ a szinét), hogy a következő lépésnél azt vissza állíthassuk
		if (unit->getId() == ID_GHOST) {			
			unit->setHiddenSymbolMapBlock(pLevel[unit->getY()][unit->getX()]);
			switch (pLevel[unit->getY()][unit->getX()]) {
			case ConsoleWindowManager::SYMBOL_MAP_AMMO_BOX:
				unit->setHiddenSymbolMapBlockColor(ConsoleWindowManager::COLOR_AMMO_BOX);
				break;
			default:
				unit->setHiddenSymbolMapBlockColor(ConsoleWindowManager::COLOR_EMPTY);
				break;
			}
		}

		pCwm->wPos(GAME_LEVEL_LEFT_POS + unit->getX(), GAME_LEVEL_TOP_POS + unit->getY(), unit->getScreenSymbol(), unit->getColor());
		pLevel[unit->getY()][unit->getX()] = unit->getMapSymbol();
		
		if (isCollision) {
			if (unit->getId() == ID_GHOST) {
				unit->setMode(Unit::Mode::SELDIR);
			}
		}
		if (!IS_TIMING_VISIBLE) {
			refreshEmptyBlock();
		}
	}
	else if ((unit->getId() == ID_GHOST && (unit->getMode() == Unit::SELDIR) && (unit->getStatus() == Unit::ALIVE))) {
		ghostSearchNewDir(unit);
	}

	if (unit->getId() == ID_MISSILE) {
		
		pCwm->wPos(GAME_LEVEL_LEFT_POS + unit->getX(), GAME_LEVEL_TOP_POS + unit->getY(), unit->getHiddenSymbolMapBlock(), unit->getHiddenSymbolMapBlockColor());
		pLevel[unit->getY()][unit->getX()] = unit->getHiddenSymbolMapBlock();

		if (!collisionDetection(unit)) {
			unsigned int curr = 0;
			switch (unit->getDir()) {
			case 0: 
				curr = unit->getY();
				unit->setY(--curr);
				break;
			case 1: 				
				curr = unit->getY();
				unit->setY(++curr);
				break;
			case 2: 
				curr = unit->getX();
				unit->setX(--curr);
				break;
			case 3: 
				curr = unit->getX();
				unit->setX(++curr);
				break;
			}			
		}
		else {
			isCollision = true;
		}						
		if (!isCollision) {
			unit->setHiddenSymbolMapBlock(pLevel[unit->getY()][unit->getX()]);
			switch (pLevel[unit->getY()][unit->getX()]) {
			case ConsoleWindowManager::SYMBOL_MAP_AMMO_BOX:
				unit->setHiddenSymbolMapBlockColor(ConsoleWindowManager::COLOR_AMMO_BOX);
				break;
			default:
				unit->setHiddenSymbolMapBlockColor(ConsoleWindowManager::COLOR_EMPTY);
				break;
			}

			pCwm->wPos(GAME_LEVEL_LEFT_POS + unit->getX(), GAME_LEVEL_TOP_POS + unit->getY(), unit->getScreenSymbol(), unit->getColor());
			pLevel[unit->getY()][unit->getX()] = unit->getMapSymbol();
		}
		else {
			Missile * rMissile = dynamic_cast<Missile*>(unit);
			rMissile->setStatus(rMissile->DEATH);			
			
			ghost = getShotUnit(rMissile);
			if (ghost != nullptr) {				
				ghost->setStatus(Unit::Status::DEATH);
			}
			pCwm->wPos(GAME_LEVEL_LEFT_POS + unit->getX(), GAME_LEVEL_TOP_POS + unit->getY(), ConsoleWindowManager::SYMBOL_EMPTY_BLOCK, 0);
			pLevel[unit->getY()][unit->getX()] = ConsoleWindowManager::SYMBOL_EMPTY_BLOCK;			
			//player->deleteMissile(rMissile->getSerialNum());
			isMissileReady = true;
		}
	}
}

void Game::ghostSearchNewDir(GameObject * unit)
{
	bool isOneWay = false;
	bool isTwoWay = false;
	unsigned int oneWayDir = 0;
	unsigned int twoWayDir = 0;

	if (unit->getDir() == Unit::DIRECTIONS::UP || unit->getDir() == Unit::DIRECTIONS::DOWN) {	//up or down
		unsigned int currX = unit->getX();
		if (checkNextBlock(unit, unit->getY(), --currX)) {
			isOneWay = true;
			oneWayDir = Unit::DIRECTIONS::LEFT;
		}
		currX = unit->getX();
		if (checkNextBlock(unit, unit->getY(), ++currX)) {
			isTwoWay = true;
			twoWayDir = Unit::DIRECTIONS::RIGHT;
		}
	} else if (unit->getDir() == Unit::DIRECTIONS::LEFT || unit->getDir() == Unit::DIRECTIONS::RIGHT) {	//left or right
		unsigned int currY = unit->getY();
		if (checkNextBlock(unit, --currY, unit->getX())) {
			isOneWay = true;
			oneWayDir = Unit::DIRECTIONS::UP;
		}
		currY = unit->getY();
		if (checkNextBlock(unit, ++currY, unit->getX())) {
			isTwoWay = true;
			twoWayDir = Unit::DIRECTIONS::DOWN;
		}
	}
	if (isOneWay || isTwoWay) {
		bool isWantNewDir = false;									//akar-e irány váltani, vagy sem
		if (unit->getDir() == Unit::Mode::SELDIR) {
			isWantNewDir = true;
		}
		else {
			isWantNewDir = Util::getRandTrueOrFalse();
		}
		if (isWantNewDir) {
			if (isOneWay && isTwoWay) {
				bool selectRandNewDir = Util::getRandTrueOrFalse();
				if (selectRandNewDir)
					unit->setDir(twoWayDir);
				else
					unit->setDir(oneWayDir);
			}
			else if (isOneWay || isTwoWay) {
				if (isOneWay)
					unit->setDir(oneWayDir);
				else
					unit->setDir(twoWayDir);
			}
		}
	}
	else if (!isOneWay && !isTwoWay && unit->getMode() == Unit::Mode::SELDIR) {	//ha beszorulna egy olyan helyre, ahonnan csak visszafelé lehet menni
		if (unit->getDir() == Unit::DIRECTIONS::UP)
			unit->setDir(Unit::DIRECTIONS::DOWN);
		else if (unit->getDir() == Unit::DIRECTIONS::DOWN)
			unit->setDir(Unit::DIRECTIONS::UP);
		else if (unit->getDir() == Unit::DIRECTIONS::LEFT)
			unit->setDir(Unit::DIRECTIONS::RIGHT);
		else if (unit->getDir() == Unit::DIRECTIONS::RIGHT)
			unit->setDir(Unit::DIRECTIONS::LEFT);
	}
}

bool Game::fireMissile(Unit * unit)
{
	unsigned int missileX = unit->getX();
	unsigned int missileY = unit->getY();
	switch (unit->getDir()) {
	case Unit::DIRECTIONS::UP:
		--missileY;
		break;
	case Unit::DIRECTIONS::DOWN:
		++missileY;
		break;
	case Unit::DIRECTIONS::LEFT:
		--missileX;
		break;
	case Unit::DIRECTIONS::RIGHT:
		++missileX;
		break;
	}
	if (checkNextBlock(nullptr, missileY, missileX)) {
		Missile* missile = new Missile(ID_MISSILE, Util::getCustomId(), missileX, missileY, unit->getDir(), 10, ConsoleWindowManager::SYMBOL_MAP_MISSILE, ConsoleWindowManager::SYMBOL_MISSILE, ConsoleWindowManager::COLOR_MISSILE, unit->getMissiles().size(), ConsoleWindowManager::COLOR_EMPTY);
		unit->addFireMissile(missile);
		return false;
	}
	return true;
}

bool Game::collisionDetection(GameObject* const unit)
{
	switch (unit->getDir()) {
		case 0:			
			return !checkNextBlock(unit, unit->getY() - 1, unit->getX());
			break;
		case 1: 			
			return !checkNextBlock(unit, unit->getY() + 1, unit->getX());
			break;
		case 2: 			
			return !checkNextBlock(unit, unit->getY(), unit->getX() - 1);
			break;
		case 3: 			
			return !checkNextBlock(unit, unit->getY(), unit->getX() + 1);
			break;
	}	
	return false;
}

bool Game::checkNextBlock(GameObject * const unit, unsigned int mapY, unsigned int mapX) {

	//ammo box
	if (unit != nullptr && !isInfiniteMissile && unit->getId() == ID_PLAYER && pLevel[mapY][mapX] == ConsoleWindowManager::SYMBOL_MAP_AMMO_BOX) {
		Unit * _player = dynamic_cast<Unit*>(unit);
		_player->addExtraMissile(DEFAULT_MISSILE_NUMBER);
		refreshPlayerBullets(_player->getMissileNumber());
	}
	//keys
	//collision ghost with player -> end game

	//check isfree the next mapblock
	if ((pLevel[mapY][mapX] == ConsoleWindowManager::SYMBOL_EMPTY_BLOCK) ||
		(pLevel[mapY][mapX] == ConsoleWindowManager::SYMBOL_SCREEN_DOT) ||
		(pLevel[mapY][mapX] == ConsoleWindowManager::SYMBOL_MAP_AMMO_BOX) )
		return true;
	return false;
}

void Game::refreshPlayerBullets(const unsigned int bulletNum)
{
	if (!isInfiniteMissile) {
		bulletStr = bulletNum >= 10 ? (Util::getTableText(12) + " " + std::to_string(bulletNum)) : (Util::getTableText(12) + " " + std::to_string(bulletNum) + " ");
	}
	else {
		bulletStr = (Util::getTableText(12) + " -");		
	}	
	pCwm->sPos(GAME_LEVEL_LEFT_POS, GAME_LEVEL_TOP_POS - 1, bulletStr);
}

inline bool Game::isKeydown(const int & key)
{
	return (GetAsyncKeyState(key) & 0x8000) != 0;
}

void Game::timeCounter()
{
	int hour = 0;
	int min = 0;
	int sec = 0;
	while (true) {
		std::string timeStr = std::to_string(hour) + ":" + std::to_string(min) + ":" + std::to_string(sec++);
		pCwm->sPos((GAME_LEVEL_LEFT_POS + pLevel[0].length() - timeStr.length()), pLevel.size(), timeStr);
		if (sec == 60) {
			++min;
			sec = 0;
		}
		if (min == 60) {
			++hour;
			min = 0;
		}
		Sleep(1000);
	}
}

/*
	Csak azért frissíti az adott fal blokkot, hogy a villogó kurzor ne látszódjon.
 */
void Game::refreshEmptyBlock()
{
	pCwm->wPos(GAME_LEVEL_LEFT_POS + emptyBlockX, GAME_LEVEL_TOP_POS + emptyBlockY, ConsoleWindowManager::SYMBOL_SCREEN_WALL_BLOCK, ConsoleWindowManager::COLOR_WALL);
}

Unit * Game::getShotUnit(Missile* missile)
{
	if (!ghosts.empty() && missile != nullptr) {
		unsigned int searchX = missile->getX();
		unsigned int searchY = missile->getY();
		switch (missile->getDir()) {
		case 0: 
			--searchY;
			break;
		case 1: 
			++searchY;
			break;
		case 2: 
			--searchX;
			break;
		case 3: 
			++searchX;
			break;
		}
		for (unsigned int i = 0; i != ghosts.size(); i++) {
			if (ghosts[i]->getX() == searchX && ghosts[i]->getY() == searchY) {
				return ghosts[i];
			}
		}
	}
	return nullptr;
}

unsigned int Game::getHiddenMapSymbolColor(GameObject * unit)
{
	if (unit->getHiddenSymbolMapBlock() == ConsoleWindowManager::SYMBOL_SCREEN_DOT)
		return ConsoleWindowManager::COLOR_DOT;
	else if (unit->getHiddenSymbolMapBlock() == ConsoleWindowManager::SYMBOL_EMPTY_BLOCK)
		return 0;
	return 0;
}