#ifndef OS_H
#define OS_H

#include <boost/predef.h>
#include <string>

namespace utility
{

class Os final
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

		static constexpr std::string name()
		{
			using namespace std::string_literals;

			if constexpr (isLinux())
				return "Linux"s;
			else if constexpr (isWindows())
				return "Windows"s;
			else if constexpr (isMac())
				return "Mac"s;
		}
};

}

#endif // OS_H
