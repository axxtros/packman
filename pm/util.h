#pragma once

#ifndef _UTIL_H_
#define _UTIL_H_

#include <string>

class Util {		
private:
protected:
public:
	static int calcLineCenter(const int &, const int &, const std::string &);
	static std::string getTableText(unsigned int stringTableID);
};

#endif // ! _UTIL_H_

