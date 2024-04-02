#include "SourceGroupSettingsWithCppStandard.h"

#include "ProjectSettings.h"
#include "utility.h"
#include "utilityApp.h"
#include <llvm/Config/llvm-config.h>

using namespace std;
using namespace utility;

// From llvm-config.h:
// #define LLVM_VERSION_MAJOR 16
// #define LLVM_VERSION_MAJOR 17

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

namespace
{
// As defined in https://github.com/llvm/llvm-project/blob/main/clang/include/clang/Basic/LangStandards.def

const vector<wstring> draftStandards = {
	#if LLVM_VERSION_MAJOR == 16
		L"c++2b",
		L"gnu++2b",
	#elif LLVM_VERSION_MAJOR == 17
		L"c++2c",
		L"gnu++2c"
	#else
		#error Unhandled LLVM version!
	#endif
};

const vector<wstring> releasedStandards = {
	#if LLVM_VERSION_MAJOR == 16
	#elif LLVM_VERSION_MAJOR == 17
		L"c++23",
		L"gnu++23",
	#else
		#error Unhandled LLVM version!
	#endif
	L"c++20",
	L"gnu++20",
	L"c++17",
	L"gnu++17",
	L"c++14",
	L"gnu++14",
	L"c++11",
	L"gnu++11",
	L"c++98",
	L"gnu++98"
};

}

std::wstring SourceGroupSettingsWithCppStandard::getDefaultCppStandard()
{
	if constexpr (utility::Os::isLinux())
		return releasedStandards[1];
	else
		return releasedStandards[0];
}

std::vector<std::wstring> SourceGroupSettingsWithCppStandard::getAvailableCppStandards()
{
	return concat(draftStandards, releasedStandards);
}

std::wstring SourceGroupSettingsWithCppStandard::getCppStandard() const
{
	if (m_cppStandard.empty())
	{
		return getDefaultCppStandard();
	}
	return m_cppStandard;
}

void SourceGroupSettingsWithCppStandard::setCppStandard(const std::wstring& standard)
{
	m_cppStandard = standard;
}

bool SourceGroupSettingsWithCppStandard::equals(const SourceGroupSettingsBase* other) const
{
	const SourceGroupSettingsWithCppStandard* otherPtr =
		dynamic_cast<const SourceGroupSettingsWithCppStandard*>(other);

	return (otherPtr && m_cppStandard == otherPtr->m_cppStandard);
}

void SourceGroupSettingsWithCppStandard::load(const ConfigManager* config, const std::string& key)
{
	setCppStandard(config->getValueOrDefault<std::wstring>(key + "/cpp_standard", L""));
}

void SourceGroupSettingsWithCppStandard::save(ConfigManager* config, const std::string& key)
{
	config->setValue(key + "/cpp_standard", getCppStandard());
}
