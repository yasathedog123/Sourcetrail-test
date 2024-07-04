#ifndef ERROR_INFO_H
#define ERROR_INFO_H

#include "StorageError.h"


struct ErrorInfo
{
	ErrorInfo()
		: id(0)
		, 
		 lineNumber(-1)
		, columnNumber(-1)
		, 
		 fatal(false)
		, indexed(false)
	{
	}

	ErrorInfo(
		Id id,
		std::wstring message,
		std::wstring filePath,
		size_t lineNumber,
		size_t columnNumber,
		std::wstring translationUnit,
		bool fatal,
		bool indexed)
		: id(id)
		, message(std::move(message))
		, filePath(std::move(filePath))
		, lineNumber(lineNumber)
		, columnNumber(columnNumber)
		, translationUnit(std::move(translationUnit))
		, fatal(fatal)
		, indexed(indexed)
	{
	}

	Id id;

	std::wstring message;

	std::wstring filePath;
	size_t lineNumber;
	size_t columnNumber;

	std::wstring translationUnit;
	bool fatal;
	bool indexed;
};

#endif	  // ERROR_INFO_H
