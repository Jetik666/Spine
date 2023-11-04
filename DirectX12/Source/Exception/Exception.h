#pragma once

#include <exception>
#include <string>

class Exception : public std::exception
{
public:
	Exception(int line, const char* file);

private:
	int pLine;
	std::string pFile;
	
	std::string pErrorBuffer;
};

