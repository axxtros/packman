#include "stdafx.h"
#include "util.h"

int Util::calcLineCenter(const int & left, const int & lineWidth, const std::string & text)
{
	return ((left + (lineWidth / 2)) - (text.length() / 2));
}
