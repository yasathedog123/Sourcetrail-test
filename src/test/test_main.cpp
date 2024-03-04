#include <iostream>
#include <boost/filesystem.hpp>

#define CATCH_CONFIG_RUNNER
#include "Catch2.hpp"

// IMPORTANT NOTE: removed signal listener for "EXCEPTION_ACCESS_VIOLATION" from catch source code
// because it interferes with the jni interface that emits such a signal on purpose

#include "ApplicationSettings.h"
#include "language_packages.h"
#include "utilityPathDetection.h"
#include <setupPlatform.h>
#include <UserPaths.h>

using namespace std;
using namespace boost::filesystem;

struct EventListener : Catch2::EventListenerBase
{
	using Catch2::EventListenerBase::EventListenerBase;	   // inherit constructor

	void testRunStarting(const Catch::TestRunInfo& ) override
	{
		FilePath settingsFilePath = UserPaths::getAppSettingsFilePath();
		cout << "Loading settings from " << settingsFilePath.str() << endl;
		ApplicationSettings::getInstance()->load(settingsFilePath, true);

#if BUILD_JAVA_LANGUAGE_PACKAGE
		if (ApplicationSettings::getInstance()->getJavaPath().empty())
		{
			shared_ptr<PathDetector> pathDetector = utility::getJavaRuntimePathDetector();
			const vector<FilePath> paths = pathDetector->getPaths();
			if (!paths.empty())
			{
				ApplicationSettings::getInstance()->setJavaPath(paths.front());
				cout << "Java path written to settings: "
						  << ApplicationSettings::getInstance()->getJavaPath().str() << endl;
			}
			else
			{
				cout << "no Java" << endl;
			}
		}
		else
		{
			cout << "Java path read from settings: "
					  << ApplicationSettings::getInstance()->getJavaPath().str() << endl;
		}
#endif
	}
};

CATCH_REGISTER_LISTENER(EventListener)

int main( int argc, char* argv[] )
{
	setupApp(argc, argv);

	// Workaround for "Unable to configure working directory in CMake/Catch"
	// https://github.com/catchorg/Catch2/issues/2249
	// Set the 'working directory' manually:

	path workingDirectory = absolute(path(argv[0])).parent_path();
	cout << "Set working directory to '" << workingDirectory << "'" << endl;
	current_path(workingDirectory);

	return Catch::Session().run( argc, argv );
}

