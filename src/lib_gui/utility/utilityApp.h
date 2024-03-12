#ifndef UTILITY_APP_H
#define UTILITY_APP_H

#include <string>
#include <boost/predef.h>

#include "ApplicationArchitectureType.h"
#include "FilePath.h"

enum class OsType
{
	UNKNOWN,
	LINUX,
	MAC,
	WINDOWS
};

namespace utility
{
struct ProcessOutput
{
	std::wstring output;
	std::wstring error;
	int exitCode;
};

std::string getDocumentationLink();

std::wstring searchPath(const std::wstring& bin, bool& ok);

std::wstring searchPath(const std::wstring& bin);

ProcessOutput executeProcess(
	const std::wstring& command,
	const std::vector<std::wstring>& arguments,
	const FilePath& workingDirectory = FilePath(),
	const bool waitUntilNoOutput = false,
	const int timeout = 30000,
	bool logProcessOutput = false);

void killRunningProcesses();

int getIdealThreadCount();

constexpr OsType getOsType()
{
	static_assert(BOOST_OS_WINDOWS || BOOST_OS_MACOS || BOOST_OS_LINUX, "Unknown operating system!");

	if constexpr (BOOST_OS_WINDOWS)
		return OsType::WINDOWS;
	else if constexpr (BOOST_OS_MACOS)
		return OsType::MAC;
	else if constexpr (BOOST_OS_LINUX)
		return OsType::LINUX;
	else
		return OsType::UNKNOWN;
}

std::string getOsTypeString();

constexpr ApplicationArchitectureType getApplicationArchitectureType()
{
#if defined(__x86_64) || defined(__x86_64__) || defined(__amd64) || defined(_M_X64) ||             \
	defined(WIN64)
	return APPLICATION_ARCHITECTURE_X86_64;
#else
	return APPLICATION_ARCHITECTURE_X86_32;
#endif
	return APPLICATION_ARCHITECTURE_UNKNOWN;
}
}	 // namespace utility

#endif	  // UTILITY_APP_H
