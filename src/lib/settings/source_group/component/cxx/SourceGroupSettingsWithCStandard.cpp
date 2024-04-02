#include "SourceGroupSettingsWithCStandard.h"

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
// As defined in https://github.com/llvm/llvm-project/blob/main/clang/include/clang/Basic/LangStandards.def

const vector<wstring> draftStandards = {
	#if LLVM_VERSION_MAJOR == 16 || LLVM_VERSION_MAJOR == 17
		L"c2x",
		L"gnu2x",
	#else
		#error Unhandled LLVM Version!
	#endif
};

const vector<wstring> releasedStandards = {
	L"c17",
	L"gnu17",
	L"c11",
	L"gnu11",
	L"c99",
	L"gnu99",
	L"c89",
	L"gnu89"
};

}

std::wstring SourceGroupSettingsWithCStandard::getDefaultCStandard()
{
	if constexpr (utility::Os::isLinux())
		return releasedStandards[1];
	else
		return releasedStandards[0];
}

std::vector<std::wstring> SourceGroupSettingsWithCStandard::getAvailableCStandards()
{
	return concat(draftStandards, releasedStandards);
}

std::wstring SourceGroupSettingsWithCStandard::getCStandard() const
{
	if (m_cStandard.empty())
	{
		return getDefaultCStandard();
	}
	return m_cStandard;
}

void SourceGroupSettingsWithCStandard::setCStandard(const std::wstring& standard)
{
	m_cStandard = standard;
}


bool SourceGroupSettingsWithCStandard::equals(const SourceGroupSettingsBase* other) const
{
	const SourceGroupSettingsWithCStandard* otherPtr =
		dynamic_cast<const SourceGroupSettingsWithCStandard*>(other);

	return (otherPtr && m_cStandard == otherPtr->m_cStandard);
}

void SourceGroupSettingsWithCStandard::load(const ConfigManager* config, const std::string& key)
{
	setCStandard(config->getValueOrDefault<std::wstring>(key + "/c_standard", L""));
}

void SourceGroupSettingsWithCStandard::save(ConfigManager* config, const std::string& key)
{
	config->setValue(key + "/c_standard", getCStandard());
}
