#pragma once
#include"myhelp.h"
#include"shell.h"
#include "elib/fnshare.h"
VECTORBYTE GetEbin(unsigned char* pEbin) {
	VECTORBYTE ret( *(size_t*)(pEbin + sizeof(size_t)), pEbin + sizeof(size_t) * 2);
	return ret ;
}

inline std::string Wstr2Astr(std::wstring wstr)
{
	int asciisize = ::WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, NULL, 0, NULL, NULL);
	if (asciisize == ERROR_NO_UNICODE_TRANSLATION)
	{
		throw std::exception("Invalid UTF-8 sequence.");
	}
	if (asciisize == 0)
	{
		throw std::exception("Error in conversion.");
	}
	char* resultstring = new char[asciisize];

	int convresult = ::WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, resultstring, asciisize, NULL, NULL);
	if (convresult != asciisize)
	{
		throw std::exception("La falla!");
	}
	std::string Ret(resultstring);
	delete[]resultstring;
	return Ret;
}
char* W2Estr(std::wstring wstr) {
	return shell_CloneTextData(const_cast<char*>(Wstr2Astr(wstr).c_str()));
}
char* A2Estr(std::string str) {
	return shell_CloneTextData(const_cast<char*>(str.c_str()));
}


