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
	static_assert(BOOST_ARCH_X86_32 || BOOST_ARCH_X86_64, "Unknown architecture!");

	if constexpr (BOOST_ARCH_X86_64)
		return ApplicationArchitectureType::X86_64;
	else if constexpr (BOOST_ARCH_X86_32)
		return ApplicationArchitectureType::X86_32;
	else
		return ApplicationArchitectureType::UNKNOWN;
}

}

#endif	  // UTILITY_APP_H
