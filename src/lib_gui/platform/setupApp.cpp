#include <ApplicationSettings.h>
#include <AppPath.h>
#include <FilePath.h>
#include <FileSystem.h>
#include <productVersion.h>
#include <ResourcePaths.h>
#include <UserPaths.h>
#include <utilityApp.h>
#include <utilityQt.h>
#include <Version.h>

#include <QCoreApplication>
#include <QDir>
#include <QDirIterator>
#include <QStandardPaths>

#include <boost/filesystem.hpp>

using namespace utility;
using namespace boost::system;
using namespace boost::filesystem;

Version setupAppDirectories(int argc, char* argv[])
{
	QCoreApplication::setApplicationName(QStringLiteral("Sourcetrail"));

	Version version(PRODUCT_VERSION_MAJOR, PRODUCT_VERSION_MINOR, PRODUCT_VERSION_PATCH);
	QCoreApplication::setApplicationVersion(QString::fromStdString(version.toDisplayString()));

	// Determine application directory (Can't use QCoreApplication::applicationDirPath here, because
	// an instance of QCoreApplication doesn't exist yet!).
	FilePath appPath = FilePath(path(argv[0]).parent_path().wstring() + L"/").getAbsolute();
	AppPath::setSharedDataDirectoryPath(appPath);
	AppPath::setCxxIndexerDirectoryPath(appPath);

	// Determine user directory:
	FilePath userDataPath = FilePath(QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation).toStdWString() + L"/").getAbsolute();
	UserPaths::setUserDataDirectoryPath(userDataPath);

	// Create missing user directory and copy default configurations:
	if (!userDataPath.exists()) {
		FileSystem::createDirectories(userDataPath);

		// This "copyFile" method does nothing if the copy destination already exist.
		FileSystem::copyFile(ResourcePaths::getFallbackDirectoryPath().concatenate(L"ApplicationSettings.xml"),
			UserPaths::getAppSettingsFilePath());

		// The GUI is a mess without a default 'window_settings.ini'!
		// TODO(PMost): Get rid of the need for a default 'window_settings.ini'
		FileSystem::copyFile(ResourcePaths::getFallbackDirectoryPath().concatenate(L"window_settings.ini"),
			UserPaths::getWindowSettingsFilePath());

		// Add u+w permissions because the source files may be marked read-only in some Linux distros:
		for (recursive_directory_iterator it(userDataPath.getPath()); it != recursive_directory_iterator(); ++it) {
			perms currentPermissions = status(*it).permissions();
			permissions(*it, currentPermissions | perms::owner_write);
		}
	}
	return version;
}

void setupAppEnvironment(int argc, char* argv[])
{
	// setupPlatform will be called after setupApp, so UserPaths::setUserDataDirectoryPath has been
	// initialized and UserPaths::getAppSettingsFilePath will return the correct path.

	if constexpr(Os::isLinux()) {
		// Set QT screen scaling factor
		ApplicationSettings appSettings;
		appSettings.load(UserPaths::getAppSettingsFilePath(), true);

		qputenv("QT_AUTO_SCREEN_SCALE_FACTOR_SOURCETRAIL", qgetenv("QT_AUTO_SCREEN_SCALE_FACTOR"));
		qputenv("QT_SCALE_FACTOR_SOURCETRAIL", qgetenv("QT_SCALE_FACTOR"));

		int autoScaling = appSettings.getScreenAutoScaling();
		if (autoScaling != -1)
		{
			QByteArray bytes;
			bytes.setNum(autoScaling);
			qputenv("QT_AUTO_SCREEN_SCALE_FACTOR", bytes);
		}

		float scaleFactor = appSettings.getScreenScaleFactor();
		if (scaleFactor > 0.0)
		{
			QByteArray bytes;
			bytes.setNum(scaleFactor);
			qputenv("QT_SCALE_FACTOR", bytes);
		}
	}
}
