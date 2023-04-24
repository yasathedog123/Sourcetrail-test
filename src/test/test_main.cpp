#include <iostream>
#include <boost/filesystem.hpp>

#define CATCH_CONFIG_RUNNER
#include "Catch2.hpp"

// IMPORTANT NOTE: removed signal listener for "EXCEPTION_ACCESS_VIOLATION" from catch source code
// because it interferes with the jni interface that emits such a signal on purpose

#include "ApplicationSettings.h"
#include "language_packages.h"
#include "utilityPathDetection.h"

using namespace std;
using namespace boost::filesystem;

struct EventListener : Catch2::EventListenerBase
{
	using Catch2::EventListenerBase::EventListenerBase;	   // inherit constructor

	void testRunStarting(const Catch::TestRunInfo& ) override
	{
#ifdef __linux__
		const std::string homedir = getenv("HOME");

		if (!homedir.empty())
		{
			if (!ApplicationSettings::getInstance()->load(
					FilePath(homedir + "/.config/sourcetrail/ApplicationSettings.xml")))
			{
				std::cout << "no settings" << std::endl;
				return;
			}
		}
		else
		{
			std::cout << "no homedir" << std::endl;
			return;
		}
#else
		ApplicationSettings::getInstance()->load(FilePath(L"data/TestSettings.xml"));
#endif

#if BUILD_JAVA_LANGUAGE_PACKAGE
		if (ApplicationSettings::getInstance()->getJavaPath().empty())
		{
			std::shared_ptr<PathDetector> pathDetector = utility::getJavaRuntimePathDetector();
			const std::vector<FilePath> paths = pathDetector->getPaths();
			if (!paths.empty())
			{
				ApplicationSettings::getInstance()->setJavaPath(paths.front());
				std::cout << "Java path written to settings: "
						  << ApplicationSettings::getInstance()->getJavaPath().str() << std::endl;
			}
			else
			{
				std::cout << "no Java" << std::endl;
			}
		}
		else
		{
			std::cout << "Java path read form settings: "
					  << ApplicationSettings::getInstance()->getJavaPath().str() << std::endl;
		}
#endif
	}
};

CATCH_REGISTER_LISTENER(EventListener)

int main( int argc, char* argv[] )
{
	// Workaround for "Unable to configure working directory in CMake/Catch"
	// https://github.com/catchorg/Catch2/issues/2249
	// Set the 'working directory' manually:

	path workingDirectory = absolute(path(argv[0])).parent_path();
	cout << "Set working directory to '" << workingDirectory << "'" << endl;
	current_path(workingDirectory);

	return Catch::Session().run( argc, argv );
}

