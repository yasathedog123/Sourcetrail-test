#ifndef UTILITY_CXX_HEADER_DETECTION_H
#define UTILITY_CXX_HEADER_DETECTION_H

#include <string>
#include <vector>

#include "Platform.h"
#include "FilePath.h"

namespace utility
{
std::vector<std::wstring> getCxxHeaderPaths(const std::string& compilerName);

std::vector<FilePath> getWindowsSdkHeaderSearchPaths(Platform::Architecture architecture);

FilePath getWindowsSdkRootPathUsingRegistry(Platform::Architecture architecture, const std::string& sdkVersion);
}	 // namespace utility

#endif	  // UTILITY_CXX_HEADER_DETECTION_H
