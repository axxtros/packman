#pragma once

#ifndef _UTIL_H_
#define _UTIL_H_

#include <random>
#include <string>

class Util {		
private:
	static unsigned int currentCustomId;
protected:
public:	
	static int calcLineCenter(const int &, const int &, const std::string &);
	static std::string getTableText(unsigned int stringTableID);
	static bool getRandTrueOrFalse();
	static unsigned int getRandomNum(const unsigned int min, const unsigned int max);
	static unsigned int getCustomId();
};

#endif // ! _UTIL_H_

