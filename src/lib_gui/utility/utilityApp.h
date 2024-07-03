#ifndef UTILITY_APP_H
#define UTILITY_APP_H

#include <boost/predef.h>
#include <string>

#include "ApplicationArchitectureType.h"
#include "FilePath.h"
#include <Os.h>

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
