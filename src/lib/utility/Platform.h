#ifndef PLATFORM_H
#define PLATFORM_H

#include <boost/predef.h>
#include <string>

namespace utility
{

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

		enum class Architecture
		{
			BITS_32,
			BITS_64
		};
		
		static Architecture getArchitecture();
		static std::string getArchitectureName();
		static std::string getArchitectureName(Architecture architecture);
};

}

#endif // PLATFORM_H
