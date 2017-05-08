#pragma once

#ifndef _UTIL_H_
#define _UTIL_H_

#include <random>
#include <string>

class Util {		
private:
protected:
public:
	static int calcLineCenter(const int &, const int &, const std::string &);
	static std::string getTableText(unsigned int stringTableID);
	static unsigned int getRandomNum(const unsigned int min, const unsigned int max);
};

#endif // ! _UTIL_H_

