#include "utilityPathDetection.h"

#include "language_packages.h"

#include "logging.h"
#include "utilityApp.h"

#if BUILD_CXX_LANGUAGE_PACKAGE
#	include "CxxFrameworkPathDetector.h"
#	include "CxxHeaderPathDetector.h"
#	include "CxxVs10To14HeaderPathDetector.h"
#	include "CxxVs15ToLatestHeaderPathDetector.h"
#endif

#if BUILD_JAVA_LANGUAGE_PACKAGE
#	include "JavaPathDetectorLinuxWindowsMac.h"
#	include "JreSystemLibraryPathDetector.h"
#	include "MavenPathDetectorUnixWindows.h"
#endif

std::shared_ptr<CombinedPathDetector> utility::getJavaRuntimePathDetector()
{
	std::shared_ptr<CombinedPathDetector> combinedDetector = std::make_shared<CombinedPathDetector>();

#if BUILD_JAVA_LANGUAGE_PACKAGE
	switch (utility::getOsType())
	{
	case OsType::WINDOWS:
		combinedDetector->addDetector(std::make_shared<JavaPathDetectorLinuxWindowsMac>("Java for Windows"));
		break;
	case OsType::MAC:
		combinedDetector->addDetector(std::make_shared<JavaPathDetectorLinuxWindowsMac>("Java for Mac"));
		break;
	case OsType::LINUX:
		combinedDetector->addDetector(std::make_shared<JavaPathDetectorLinuxWindowsMac>("Java for Linux"));
		break;
	default:
		LOG_WARNING("No suitable Java Runtime path detector found");
		break;
	}
#endif

	return combinedDetector;
}

std::shared_ptr<CombinedPathDetector> utility::getJreSystemLibraryPathsDetector()
{
	std::shared_ptr<CombinedPathDetector> combinedDetector = std::make_shared<CombinedPathDetector>();

#if BUILD_JAVA_LANGUAGE_PACKAGE
	switch (utility::getOsType())
	{
	case OsType::WINDOWS:
		combinedDetector->addDetector(std::make_shared<JreSystemLibraryPathDetector>(
			std::make_shared<JavaPathDetectorLinuxWindowsMac>("Java for Windows")));
		break;
	case OsType::MAC:
		combinedDetector->addDetector(std::make_shared<JreSystemLibraryPathDetector>(
			std::make_shared<JavaPathDetectorLinuxWindowsMac>("Java for Mac")));
		break;
	case OsType::LINUX:
		combinedDetector->addDetector(std::make_shared<JreSystemLibraryPathDetector>(
			std::make_shared<JavaPathDetectorLinuxWindowsMac>("Java for Linux")));
		break;
	default:
		LOG_WARNING("No suitable JRE system library path detector found");
		break;
	}
#endif

	return combinedDetector;
}

std::shared_ptr<CombinedPathDetector> utility::getMavenExecutablePathDetector()
{
	std::shared_ptr<CombinedPathDetector> combinedDetector = std::make_shared<CombinedPathDetector>();

#if BUILD_JAVA_LANGUAGE_PACKAGE
	switch (utility::getOsType())
	{
	case OsType::WINDOWS:
		combinedDetector->addDetector(std::make_shared<MavenPathDetectorUnixWindows>("Maven for Windows"));
		break;
	case OsType::MAC:
	case OsType::LINUX:
		combinedDetector->addDetector(std::make_shared<MavenPathDetectorUnixWindows>("Maven for Unix"));
		break;
	default:
		LOG_WARNING("No suitable Maven path detector found");
		break;
	}
#endif

	return combinedDetector;
}

std::shared_ptr<CombinedPathDetector> utility::getCxxVsHeaderPathDetector()
{
	std::shared_ptr<CombinedPathDetector> combinedDetector = std::make_shared<CombinedPathDetector>();

	if (utility::getOsType() != OsType::WINDOWS)
	{
		return combinedDetector;
	}

#if BUILD_CXX_LANGUAGE_PACKAGE
	combinedDetector->addDetector(std::make_shared<CxxVs15ToLatestHeaderPathDetector>(
		CxxVs15ToLatestHeaderPathDetector::VISUAL_STUDIO_2022));
	combinedDetector->addDetector(std::make_shared<CxxVs15ToLatestHeaderPathDetector>(
		CxxVs15ToLatestHeaderPathDetector::VISUAL_STUDIO_2019));
	combinedDetector->addDetector(std::make_shared<CxxVs15ToLatestHeaderPathDetector>(
		CxxVs15ToLatestHeaderPathDetector::VISUAL_STUDIO_2017));

	combinedDetector->addDetector(std::make_shared<CxxVs10To14HeaderPathDetector>(
		CxxVs10To14HeaderPathDetector::VISUAL_STUDIO_2015, false, APPLICATION_ARCHITECTURE_X86_32));
	combinedDetector->addDetector(std::make_shared<CxxVs10To14HeaderPathDetector>(
		CxxVs10To14HeaderPathDetector::VISUAL_STUDIO_2015, false, APPLICATION_ARCHITECTURE_X86_64));
	combinedDetector->addDetector(std::make_shared<CxxVs10To14HeaderPathDetector>(
		CxxVs10To14HeaderPathDetector::VISUAL_STUDIO_2015, true, APPLICATION_ARCHITECTURE_X86_32));
	combinedDetector->addDetector(std::make_shared<CxxVs10To14HeaderPathDetector>(
		CxxVs10To14HeaderPathDetector::VISUAL_STUDIO_2015, true, APPLICATION_ARCHITECTURE_X86_64));
	combinedDetector->addDetector(std::make_shared<CxxVs10To14HeaderPathDetector>(
		CxxVs10To14HeaderPathDetector::VISUAL_STUDIO_2013, false, APPLICATION_ARCHITECTURE_X86_32));
	combinedDetector->addDetector(std::make_shared<CxxVs10To14HeaderPathDetector>(
		CxxVs10To14HeaderPathDetector::VISUAL_STUDIO_2013, false, APPLICATION_ARCHITECTURE_X86_64));
	combinedDetector->addDetector(std::make_shared<CxxVs10To14HeaderPathDetector>(
		CxxVs10To14HeaderPathDetector::VISUAL_STUDIO_2013, true, APPLICATION_ARCHITECTURE_X86_32));
	combinedDetector->addDetector(std::make_shared<CxxVs10To14HeaderPathDetector>(
		CxxVs10To14HeaderPathDetector::VISUAL_STUDIO_2013, true, APPLICATION_ARCHITECTURE_X86_64));
	combinedDetector->addDetector(std::make_shared<CxxVs10To14HeaderPathDetector>(
		CxxVs10To14HeaderPathDetector::VISUAL_STUDIO_2012, false, APPLICATION_ARCHITECTURE_X86_32));
	combinedDetector->addDetector(std::make_shared<CxxVs10To14HeaderPathDetector>(
		CxxVs10To14HeaderPathDetector::VISUAL_STUDIO_2012, false, APPLICATION_ARCHITECTURE_X86_64));
	combinedDetector->addDetector(std::make_shared<CxxVs10To14HeaderPathDetector>(
		CxxVs10To14HeaderPathDetector::VISUAL_STUDIO_2012, true, APPLICATION_ARCHITECTURE_X86_32));
	combinedDetector->addDetector(std::make_shared<CxxVs10To14HeaderPathDetector>(
		CxxVs10To14HeaderPathDetector::VISUAL_STUDIO_2012, true, APPLICATION_ARCHITECTURE_X86_64));
	combinedDetector->addDetector(std::make_shared<CxxVs10To14HeaderPathDetector>(
		CxxVs10To14HeaderPathDetector::VISUAL_STUDIO_2010, false, APPLICATION_ARCHITECTURE_X86_32));
	combinedDetector->addDetector(std::make_shared<CxxVs10To14HeaderPathDetector>(
		CxxVs10To14HeaderPathDetector::VISUAL_STUDIO_2010, false, APPLICATION_ARCHITECTURE_X86_64));
	combinedDetector->addDetector(std::make_shared<CxxVs10To14HeaderPathDetector>(
		CxxVs10To14HeaderPathDetector::VISUAL_STUDIO_2010, true, APPLICATION_ARCHITECTURE_X86_32));
	combinedDetector->addDetector(std::make_shared<CxxVs10To14HeaderPathDetector>(
		CxxVs10To14HeaderPathDetector::VISUAL_STUDIO_2010, true, APPLICATION_ARCHITECTURE_X86_64));
#endif

	return combinedDetector;
}

std::shared_ptr<CombinedPathDetector> utility::getCxxHeaderPathDetector()
{
	std::shared_ptr<CombinedPathDetector> combinedDetector = getCxxVsHeaderPathDetector();
#if BUILD_CXX_LANGUAGE_PACKAGE
	combinedDetector->addDetector(std::make_shared<CxxHeaderPathDetector>("clang"));
	combinedDetector->addDetector(std::make_shared<CxxHeaderPathDetector>("gcc"));
#endif
	return combinedDetector;
}

std::shared_ptr<CombinedPathDetector> utility::getCxxFrameworkPathDetector()
{
	std::shared_ptr<CombinedPathDetector> combinedDetector = std::make_shared<CombinedPathDetector>();
#if BUILD_CXX_LANGUAGE_PACKAGE
	combinedDetector->addDetector(std::make_shared<CxxFrameworkPathDetector>("clang"));
	combinedDetector->addDetector(std::make_shared<CxxFrameworkPathDetector>("gcc"));
#endif
	return combinedDetector;
}
