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
