#include "stdafx.h"

#include <cstring>
#include <atlstr.h>

#include "util.h"

int Util::calcLineCenter(const int & left, const int & lineWidth, const std::string & text)
{
	return ((left + (lineWidth / 2)) - (text.length() / 2));
}

std::string Util::getTableText(unsigned int stringTableID)
{
	CString result;
	result.LoadStringW(stringTableID);
	return CStringA(result);
}

bool Util::getRandDecide()
{
	return getRandomNum(0, 1);	
}

unsigned int Util::getRandomNum(const unsigned int min, const unsigned int max)
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<double> dist(min, (max + 1));
	return dist(mt);
}
