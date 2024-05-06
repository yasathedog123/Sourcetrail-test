#include "ToolVersionData.h"
#include "utility.h"

#include "Os.h"

#include <llvm/Config/llvm-config.h>

using namespace std;
using namespace string_literals;
using namespace utility;

///////////////////////////////////////////////////////////////////////////////
//
// Clang version support:
//
///////////////////////////////////////////////////////////////////////////////

// LLVM 16 (/usr/bin/clang):
// clang -std=xxx empty.cpp
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
// note: use 'c++2b' for 'Working draft for ISO C++ 2023 DIS' standard
// note: use 'gnu++2b' for 'Working draft for ISO C++ 2023 DIS with GNU extensions' standard

// LLVM 17 (vcpkg_installed/custom-x64-linux-static-md/tools/llvm/clang):
// ./clang -std=xxx empty.cpp
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
// note: use 'c++2c' or 'c++26' for 'Working draft for C++2c' standard
// note: use 'gnu++2c' or 'gnu++26' for 'Working draft for C++2c with GNU extensions' standard

// LLVM 16 (/usr/bin/clang):
// clang -std=xxx empty.c
// note: use 'c89', 'c90', or 'iso9899:1990' for 'ISO C 1990' standard
// note: use 'iso9899:199409' for 'ISO C 1990 with amendment 1' standard
// note: use 'gnu89' or 'gnu90' for 'ISO C 1990 with GNU extensions' standard
// note: use 'c99' or 'iso9899:1999' for 'ISO C 1999' standard
// note: use 'gnu99' for 'ISO C 1999 with GNU extensions' standard
// note: use 'c11' or 'iso9899:2011' for 'ISO C 2011' standard
// note: use 'gnu11' for 'ISO C 2011 with GNU extensions' standard
// note: use 'c17', 'iso9899:2017', 'c18', or 'iso9899:2018' for 'ISO C 2017' standard
// note: use 'gnu17' or 'gnu18' for 'ISO C 2017 with GNU extensions' standard
// note: use 'c2x' for 'Working Draft for ISO C2x' standard
// note: use 'gnu2x' for 'Working Draft for ISO C2x with GNU extensions' standard

// LLVM 17 (vcpkg_installed/custom-x64-linux-static-md/tools/llvm/clang):
// ./clang -std=xxx empty.c
// note: use 'c89', 'c90', or 'iso9899:1990' for 'ISO C 1990' standard
// note: use 'iso9899:199409' for 'ISO C 1990 with amendment 1' standard
// note: use 'gnu89' or 'gnu90' for 'ISO C 1990 with GNU extensions' standard
// note: use 'c99' or 'iso9899:1999' for 'ISO C 1999' standard
// note: use 'gnu99' for 'ISO C 1999 with GNU extensions' standard
// note: use 'c11' or 'iso9899:2011' for 'ISO C 2011' standard
// note: use 'gnu11' for 'ISO C 2011 with GNU extensions' standard
// note: use 'c17', 'iso9899:2017', 'c18', or 'iso9899:2018' for 'ISO C 2017' standard
// note: use 'gnu17' or 'gnu18' for 'ISO C 2017 with GNU extensions' standard
// note: use 'c2x' for 'Working Draft for ISO C2x' standard
// note: use 'gnu2x' for 'Working Draft for ISO C2x with GNU extensions' standard

namespace
{
// From llvm-config.h:
// #define LLVM_VERSION_MAJOR 16
// #define LLVM_VERSION_MAJOR 17

const vector<wstring> draftCppStandards = {
	#if LLVM_VERSION_MAJOR == 16
		L"c++2b"s,
		L"gnu++2b"s,
	#elif LLVM_VERSION_MAJOR == 17
		L"c++2c"s,
		L"gnu++2c"s
	#else
		#error Unhandled LLVM version!
	#endif
};

const vector<wstring> releasedCppStandards = {
	#if LLVM_VERSION_MAJOR == 16
	#elif LLVM_VERSION_MAJOR == 17
		L"c++23"s,
		L"gnu++23"s,
	#else
		#error Unhandled LLVM version!
	#endif
	L"c++20"s,
	L"gnu++20"s,
	L"c++17"s,
	L"gnu++17"s,
	L"c++14"s,
	L"gnu++14"s,
	L"c++11"s,
	L"gnu++11"s,
	L"c++98"s,
	L"gnu++98"s
};

const vector<wstring> draftCStandards = {
	#if LLVM_VERSION_MAJOR == 16 || LLVM_VERSION_MAJOR == 17
		L"c2x"s,
		L"gnu2x"s,
	#else
		#error Unhandled LLVM Version!
	#endif
};

const vector<wstring> releasedCStandards = {
	L"c17"s,
	L"gnu17"s,
	L"c11"s,
	L"gnu11"s,
	L"c99"s,
	L"gnu99"s,
	L"c89"s,
	L"gnu89"s
};

}

wstring ClangVersionData::getLatestCppStandard()
{
	if constexpr (Os::isLinux())
		return releasedCppStandards[1];
	else
		return releasedCppStandards[0];
}

vector<wstring> ClangVersionData::getAvailableCppStandards()
{
	return concat(draftCppStandards, releasedCppStandards);
}

wstring ClangVersionData::getLatestCStandard()
{
	if constexpr (Os::isLinux())
		return releasedCStandards[1];
	else
		return releasedCStandards[0];
}

vector<wstring> ClangVersionData::getAvailableCStandards()
{
	return concat(draftCStandards, releasedCStandards);
}

///////////////////////////////////////////////////////////////////////////////
//
// Visual Studio version support:
//
///////////////////////////////////////////////////////////////////////////////

namespace
{
// Version table: https://github.com/microsoft/vswhere/wiki/Versions#release-versions

const vector<wstring> releasedVisualStudioVersionRanges = {
	// Sorted from newest to oldest:
	L"[17.0, 18.0)"s, // 2022
	L"[16.0, 17.0)"s, // 2019
	L"[15.0, 16.0)"s  // 2017
};

}

vector<wstring> VisualStudioVersionData::getVersionRanges()
{
	return releasedVisualStudioVersionRanges;
}
