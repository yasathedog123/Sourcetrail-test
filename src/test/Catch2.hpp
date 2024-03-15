#ifndef CATCH2_HPP
#define CATCH2_HPP

// See https://github.com/catchorg/Catch2/blob/devel/docs/migrate-v2-to-v3.md

#if defined(HAVE_CATCH2_V2)
	// Prevent Catch2 from intercepting JVM signals:
	// (https://github.com/catchorg/Catch2/blob/devel/docs/configuration.md#other-toggles)
	#define CATCH_CONFIG_NO_WINDOWS_SEH
	#define CATCH_CONFIG_NO_POSIX_SIGNALS

	#define CATCH_CONFIG_EXTERNAL_INTERFACES
	#include <catch2/catch.hpp>

	namespace Catch2 {
		using Catch::Detail::Approx;

		using EventListenerBase = Catch::TestEventListenerBase;
	}
#elif defined(HAVE_CATCH2_V3)
	// To prevent Catch2 V3 from intercepting JVM signals;
	// (https://github.com/catchorg/Catch2/blob/devel/docs/cmake-integration.md#catch_config_-customization-options-in-cmake)
	// See the vcpkg tripplet files in 'vcpkg-custom-tripplets/'
	#include <catch2/catch_all.hpp>

	namespace Catch2 {
		using Catch::Approx;

		using Catch::EventListenerBase;
	}
#else
	#error Unknown Catch2 version!
#endif

// Note: Catch2 V3 supports a SKIP() command, but V2 doesn't. So as a workaround we just write
// a message:
#define TEST_DISABLED(reason) \
	WARN("Test disabled: " reason)

#define REQUIRE_MESSAGE(msg, cond) \
		do \
		{ \
			INFO(msg); \
			REQUIRE(cond); \
		} while ((void)0, 0)

#endif
