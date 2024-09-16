#include "Platform.h"

namespace utility
{
using namespace std;
using namespace std::string_literals;

static_assert(BOOST_ARCH_X86_32 || BOOST_ARCH_X86_64, "Unknown architecture!");

ApplicationArchitectureType getApplicationArchitectureType()
{
	if constexpr (BOOST_ARCH_X86_64)
		return ApplicationArchitectureType::X86_64;
	else if constexpr (BOOST_ARCH_X86_32)
		return ApplicationArchitectureType::X86_32;
	else
		return ApplicationArchitectureType::UNKNOWN;
}

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

}
