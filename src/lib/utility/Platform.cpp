#include "Platform.h"

namespace utility
{
using namespace std;
using namespace std::string_literals;

// Can't use BOOST_ARCH_WORD_BITS_32/BOOST_ARCH_WORD_BITS_64 because they are *both* defined!
static_assert(BOOST_ARCH_WORD_BITS == 32 || BOOST_ARCH_WORD_BITS == 64, "Unknown architecture!");
static_assert(BOOST_OS_WINDOWS || BOOST_OS_MACOS || BOOST_OS_LINUX, "Unknown operating system!");

string Platform::getName()
{
	if constexpr (isLinux())
		return "Linux"s;
	else if constexpr (isWindows())
		return "Windows"s;
	else if constexpr (isMac())
		return "Mac"s;
}

Platform::Architecture Platform::getArchitecture()
{
	if constexpr (BOOST_ARCH_WORD_BITS == 32)
		return Architecture::BITS_32;
	else if constexpr (BOOST_ARCH_WORD_BITS == 64)
		return Architecture::BITS_64;
}

string Platform::getArchitectureName()
{
	return getArchitectureName(getArchitecture());
}

string Platform::getArchitectureName(Architecture architecture)
{
	switch (architecture)
	{
		case Architecture::BITS_32:
			return "32 Bit"s;
		case Architecture::BITS_64:
			return "64 Bit"s;
		default:
			return ""s;
	}
}

}
