#include "Platform.h"

namespace utility
{
using namespace std;
using namespace std::string_literals;

static_assert(BOOST_ARCH_X86_32 || BOOST_ARCH_X86_64, "Unknown architecture!");
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

string Platform::getArchitectureName()
{
	if constexpr (BOOST_ARCH_X86_64)
		return "32 Bit"s;
	else if constexpr (BOOST_ARCH_X86_32)
		return "64 Bit"s;

}

}
