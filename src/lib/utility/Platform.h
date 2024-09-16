#ifndef PLATFORM_H
#define PLATFORM_H

#include <boost/predef.h>
#include <string>

enum class ApplicationArchitectureType
{
	UNKNOWN,
	X86_32,
	X86_64
};

namespace utility
{

ApplicationArchitectureType getApplicationArchitectureType();

class Platform final
{
	public:
		static constexpr bool isLinux()
		{
			return BOOST_OS_LINUX;
		}

		static constexpr bool isWindows()
		{
			return BOOST_OS_WINDOWS;
		}

		static constexpr bool isMac()
		{
			return BOOST_OS_MACOS;
		}

		static std::string getName();
};

}

#endif // PLATFORM_H
