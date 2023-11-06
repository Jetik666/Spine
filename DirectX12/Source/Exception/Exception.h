#pragma once

#include <exception>
#include <string>

class Exception : public std::exception
{
public:
	Exception(int line, const char* file) noexcept;
	const char* what() const noexcept override;
	virtual const char* GetType() const noexcept;
	int GetLine() const noexcept;
	const std::string& GetFile() const noexcept;
	std::string GetOriginString() const noexcept;

private:
	int pLine;
	std::string pFile;

	mutable std::string pErrorBuffer;
};

