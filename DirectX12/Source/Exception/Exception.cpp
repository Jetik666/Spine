#include "pch.h"
#include "Exception.h"

#include <sstream>

Exception::Exception(int line, const char* file) noexcept : pLine(line), pFile(file) {}

const char* Exception::what() const noexcept
{
	std::ostringstream oss;
	oss << GetType() << std::endl << GetOriginString();
	pErrorBuffer = oss.str();
	return pErrorBuffer.c_str();
}

const char* Exception::GetType() const noexcept
{
	return "Game Exception";
}

int Exception::GetLine() const noexcept
{
	return pLine;
}

const std::string& Exception::GetFile() const noexcept
{
	return pFile;
}

std::string Exception::GetOriginString() const noexcept
{
	std::ostringstream oss;
	oss << "[File] " << pFile << std::endl << "[Line] " << pLine;
	return oss.str();
}
