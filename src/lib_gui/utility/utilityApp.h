#ifndef UTILITY_APP_H
#define UTILITY_APP_H

#include <string>

#include <boost/chrono/duration.hpp>

#include "FilePath.h"
#include <Platform.h>

namespace utility
{
constexpr boost::chrono::milliseconds DEFAULT_TIMEOUT(30000);
constexpr boost::chrono::milliseconds INFINITE_TIMEOUT(boost::chrono::milliseconds::max());

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
	const boost::chrono::milliseconds &timeout = DEFAULT_TIMEOUT,
	bool logProcessOutput = false);

void killRunningProcesses();

int getIdealThreadCount();

}

#endif	  // UTILITY_APP_H
