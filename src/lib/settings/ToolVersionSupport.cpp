#include "ToolVersionSupport.h"
#include "Platform.h"
#include "language_packages.h"
#include "utility.h"

#if BUILD_CXX_LANGUAGE_PACKAGE
	#include <llvm/Config/llvm-config.h>
#endif

using namespace std;
using namespace string_literals;
using namespace utility;

namespace
{
// Note: We do the '#if LLVM_VERSION_MAJOR ==' check in case we need to support two different clang
// versions in the system build and the vcpkg build!
//
// From llvm-config.h:
// #define LLVM_VERSION_MAJOR 18
// #define LLVM_VERSION_MAJOR 19
//
// C++
// /usr/bin/clang-19 -std=xxx empty.cpp
// vcpkg_installed/custom-x64-static-md/tools/llvm/clang-18 -std=xxx empty.cpp
//
// Released standards:
// note: use 'c++98' or 'c++03' for 'ISO C++ 1998 with amendments' standard
// note: use 'gnu++98' or 'gnu++03' for 'ISO C++ 1998 with amendments and GNU extensions' standard
// note: use 'c++11' for 'ISO C++ 2011 with amendments' standard
// note: use 'gnu++11' for 'ISO C++ 2011 with amendments and GNU extensions' standard
// note: use 'c++14' for 'ISO C++ 2014 with amendments' standard
// note: use 'gnu++14' for 'ISO C++ 2014 with amendments and GNU extensions' standard
// note: use 'c++17' for 'ISO C++ 2017 with amendments' standard
// note: use 'gnu++17' for 'ISO C++ 2017 with amendments and GNU extensions' standard
// note: use 'c++20' for 'ISO C++ 2020 DIS' standard
// note: use 'gnu++20' for 'ISO C++ 2020 DIS with GNU extensions' standard
// note: use 'c++23' for 'ISO C++ 2023 DIS' standard
// note: use 'gnu++23' for 'ISO C++ 2023 DIS with GNU extensions' standard
//
// Draft standards:
// note: use 'c++2c' or 'c++26' for 'Working draft for C++2c' standard
// note: use 'gnu++2c' or 'gnu++26' for 'Working draft for C++2c with GNU extensions' standard

vector<wstring> getReleasedCppStandards()
{
	const vector<wstring> releasedCppStandards = {
		#ifdef LLVM_VERSION_MAJOR
			#if LLVM_VERSION_MAJOR >= 18
				L"c++23"s, L"gnu++23"s,
				L"c++20"s, L"gnu++20"s,
				L"c++17"s, L"gnu++17"s,
				L"c++14"s, L"gnu++14"s,
				L"c++11"s, L"gnu++11"s,
				L"c++03"s, L"gnu++03"s,
				L"c++98"s, L"gnu++98"s,
			#endif
		#endif
	};
	return releasedCppStandards;
}

vector<wstring> getDraftCppStandards()
{
	const vector<wstring> draftCppStandards = {
		#ifdef LLVM_VERSION_MAJOR
			#if LLVM_VERSION_MAJOR >= 18
				L"c++2c"s, L"c++26"s,
				L"gnu++2c"s, L"gnu++26"s,
			#endif
		#endif
	};
	return draftCppStandards;
}

// C
// /usr/bin/clang-19 -std=xxx empty.c
// vcpkg_installed/custom-x64-static-md/tools/llvm/clang-18 -std=xxx empty.c
//
// Released standards:
// note: use 'c89', 'c90', or 'iso9899:1990' for 'ISO C 1990' standard
// note: use 'iso9899:199409' for 'ISO C 1990 with amendment 1' standard
// note: use 'gnu89' or 'gnu90' for 'ISO C 1990 with GNU extensions' standard
// note: use 'c99' or 'iso9899:1999' for 'ISO C 1999' standard
// note: use 'gnu99' for 'ISO C 1999 with GNU extensions' standard
// note: use 'c11' or 'iso9899:2011' for 'ISO C 2011' standard
// note: use 'gnu11' for 'ISO C 2011 with GNU extensions' standard
// note: use 'c17', 'iso9899:2017', 'c18', or 'iso9899:2018' for 'ISO C 2017' standard
// note: use 'gnu17' or 'gnu18' for 'ISO C 2017 with GNU extensions' standard
//
// Draft standards:
// note: use 'c23' for 'Working Draft for ISO C23' standard
// note: use 'gnu23' for 'Working Draft for ISO C23 with GNU extensions' standard
// note: use 'c2y' for 'Working Draft for ISO C2y' standard
// note: use 'gnu2y' for 'Working Draft for ISO C2y with GNU extensions' standard

vector<wstring> getReleasedCStandards()
{
	const vector<wstring> releasedCStandards = {
		#ifdef LLVM_VERSION_MAJOR
			#if LLVM_VERSION_MAJOR >= 18
				L"c17"s, L"gnu17"s,
				L"c11"s, L"gnu11"s,
				L"c99"s, L"gnu99"s,
				L"c89"s, L"gnu89"s,
			#endif
		#endif
	};
	return releasedCStandards;
}

vector<wstring> getDraftCStandards()
{
	const vector<wstring> draftCStandards = {
		#ifdef LLVM_VERSION_MAJOR
			#if LLVM_VERSION_MAJOR == 18 || LLVM_VERSION_MAJOR == 19
				L"c23"s, L"gnu23"s
			#endif
			#if LLVM_VERSION_MAJOR >= 19
				L"c2y"s, L"gnu2y"s
			#endif
		#endif
	};
	return draftCStandards;
}

}

///////////////////////////////////////////////////////////////////////////////
//
// Clang version support:
//
///////////////////////////////////////////////////////////////////////////////

wstring ClangVersionSupport::getLatestCppStandard()
{
	if constexpr (Platform::isLinux())
		return getReleasedCppStandards()[1];
	else
		return getReleasedCppStandards()[0];
}

vector<wstring> ClangVersionSupport::getAvailableCppStandards()
{
	return concat(getDraftCppStandards(), getReleasedCppStandards());
}

wstring ClangVersionSupport::getLatestCStandard()
{
	if constexpr (Platform::isLinux())
		return getReleasedCStandards()[1];
	else
		return getReleasedCStandards()[0];
}

vector<wstring> ClangVersionSupport::getAvailableCStandards()
{
	return concat(getDraftCStandards(), getReleasedCStandards());
}

///////////////////////////////////////////////////////////////////////////////
//
// Visual Studio version support:
//
///////////////////////////////////////////////////////////////////////////////

vector<wstring> VisualStudioVersionSupport::getVersionRanges()
{
	// Version table: https://github.com/microsoft/vswhere/wiki/Versions#release-versions
	// Sorted from newest to oldest:
	const vector<wstring> releasedVisualStudioVersionRanges = {
		L"[17.0, 18.0)"s, // 2022
		L"[16.0, 17.0)"s, // 2019
		L"[15.0, 16.0)"s  // 2017
	};
	return releasedVisualStudioVersionRanges;
}

///////////////////////////////////////////////////////////////////////////////
//
// Windows SDK version support:
//
///////////////////////////////////////////////////////////////////////////////

vector<string> WindowsSdkVersionSupport::getVersions()
{
	// Adapted from: https://en.wikipedia.org/wiki/Microsoft_Windows_SDK

	const vector<string> sdkVersions = {
		"v10"s,   // Windows Standalone SDK for Windows 10 (Also included in Visual Studio 2015)
		"v8.1A"s, // Included in Visual Studio 2013
		"v8.1"s,  // Windows Software Development Kit (SDK) for Windows 8.1
		"v8.0A"s, // Included in Visual Studio 2012
		"v7.1A"s, // Included in Visual Studio 2012 Update 1 (or later)
		"v7.0A"s  // Included in Visual Studio 2010
	};
	return sdkVersions;
}
