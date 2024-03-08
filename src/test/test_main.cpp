#include <iostream>
#include <boost/filesystem.hpp>

#define CATCH_CONFIG_RUNNER
#include "Catch2.hpp"

// IMPORTANT NOTE: removed signal listener for "EXCEPTION_ACCESS_VIOLATION" from catch source code
// because it interferes with the jni interface that emits such a signal on purpose

#include <AppPath.h>
#include "ApplicationSettings.h"
#include "language_packages.h"
#include "utilityPathDetection.h"
#include <setupApp.h>
#include <UserPaths.h>

using namespace std;
using namespace boost::filesystem;

static int g_argc;
static char **g_argv;

struct EventListener : Catch2::EventListenerBase
{
	using Catch2::EventListenerBase::EventListenerBase;	   // inherit constructor

	void testRunStarting(const Catch::TestRunInfo& ) override
	{
		setupAppDirectories(g_argc, g_argv);

		// The tests assume an empty shared data directory, so unset it:
		AppPath::setSharedDataDirectoryPath(FilePath());

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

int main(int argc, char* argv[])
{
	g_argc = argc;
	g_argv = argv;

	// Workaround for "Unable to configure working directory in CMake/Catch"
	// https://github.com/catchorg/Catch2/issues/2249
	// Set the 'working directory' manually:

	path workingDirectory = absolute(path(argv[0])).parent_path();
	cout << "Set working directory to '" << workingDirectory << "'" << endl;
	current_path(workingDirectory);

	return Catch::Session().run( argc, argv );
}

