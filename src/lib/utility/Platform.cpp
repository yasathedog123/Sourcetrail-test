#include "Platform.h"

namespace utility
{
using namespace std;
using namespace std::string_literals;

static_assert(BOOST_ARCH_X86_32 || BOOST_ARCH_X86_64, "Unknown architecture!");
static_assert(BOOST_OS_WINDOWS || BOOST_OS_MACOS || BOOST_OS_LINUX, "Unknown operating system!");

static constexpr string X86_32_NAME("32 Bit");
static constexpr string X86_64_NAME("64 Bit");

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
		return X86_32_NAME;
	else if constexpr (BOOST_ARCH_X86_32)
		return X86_64_NAME;
}

string Platform::getArchitectureName(Architecture architecture)
{
	if (architecture == Architecture::X86_32)
		return X86_32_NAME;
	else if (architecture == Architecture::X86_64)
		return X86_64_NAME;
	else
		return "";
}

}
