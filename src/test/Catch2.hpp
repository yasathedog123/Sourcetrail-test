#ifndef CATCH2_HPP
#define CATCH2_HPP

// See https://github.com/catchorg/Catch2/blob/devel/docs/migrate-v2-to-v3.md
// for the rational behind these header checks.

#if __has_include(<catch2/catch_all.hpp>) // V3?
	#include <catch2/catch_all.hpp>
#elif __has_include(<catch2/catch.hpp>) // V2?
	// Prevent Catch2 from intercepting JVM signals:
	// (https://github.com/catchorg/Catch2/blob/devel/docs/configuration.md#other-toggles)
	#define CATCH_CONFIG_NO_WINDOWS_SEH
	#define CATCH_CONFIG_NO_POSIX_SIGNALS

	#define CATCH_CONFIG_EXTERNAL_INTERFACES
	#include <catch2/catch.hpp>
#else
	#error "Unknown Catch2 version!"
#endif

#if CATCH_VERSION_MAJOR == 2
	namespace Catch2 {
		using Catch::Detail::Approx;

		using EventListenerBase = Catch::TestEventListenerBase;
	}
#elif CATCH_VERSION_MAJOR >= 3
	namespace Catch2 {
		using Catch::Approx;

		using Catch::EventListenerBase;
	}
#endif

#endif
