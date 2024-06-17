#ifndef CATCH2_HPP
#define CATCH2_HPP

// To prevent Catch2 V3 from intercepting JVM signals;
// (https://github.com/catchorg/Catch2/blob/devel/docs/cmake-integration.md#catch_config_-customization-options-in-cmake)
// See the vcpkg tripplet files in 'vcpkg-custom-tripplets/'

#include <catch2/catch_all.hpp>

namespace Catch2
{
	using Catch::Approx;
	using Catch::EventListenerBase;
}

#define SKIP_TEST(reason) \
	SKIP("Skipping Test: " reason)

#define REQUIRE_MESSAGE(msg, cond) \
	do \
	{ \
		INFO(msg); \
		REQUIRE(cond); \
	} while ((void)0, 0)

#endif
