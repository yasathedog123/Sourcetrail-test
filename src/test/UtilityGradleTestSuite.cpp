#include "Catch2.hpp"

#include "language_packages.h"

#if BUILD_JAVA_LANGUAGE_PACKAGE

#include "FilePath.h"
#include "FileSystem.h"
#include "utility.h"
#include "utilityGradle.h"

#include <utilityApp.h>

using namespace utility;

namespace
{

FilePath tmpFolder = FilePath(L"data/UtilityGradleTestSuite/tmp");

void cleanup()
{
	if (tmpFolder.recheckExists())
	{
		for (const FilePath& path: FileSystem::getFilePathsFromDirectory(tmpFolder))
		{
			FileSystem::remove(path);
		}
		FileSystem::remove(tmpFolder);
	}
}

}

TEST_CASE("gradle wrapper detects source directories of simple projects")
{
	if constexpr (Os::isWindows()) {
		std::vector<FilePath> result = utility::gradleGetAllSourceDirectories(
			FilePath(L"data/UtilityGradleTestSuite/simple_gradle_project"), false);

		REQUIRE(utility::containsElement<FilePath>(
			result,
			FilePath(L"data/UtilityGradleTestSuite/simple_gradle_project/src/main/java").makeAbsolute()));

		REQUIRE(!utility::containsElement<FilePath>(
			result,
			FilePath(L"data/UtilityGradleTestSuite/simple_gradle_project/src/test/java").makeAbsolute()));
	} else
		FAIL("TODO: Why does it fail under Linux?");

}

TEST_CASE("gradle wrapper detects source and test directories of simple projects")
{
	if constexpr (Os::isWindows()) {
		std::vector<FilePath> result = utility::gradleGetAllSourceDirectories(
			FilePath(L"data/UtilityGradleTestSuite/simple_gradle_project"), true);

		REQUIRE(utility::containsElement<FilePath>(
			result,
			FilePath(L"data/UtilityGradleTestSuite/simple_gradle_project/src/main/java").makeAbsolute()));

		REQUIRE(utility::containsElement<FilePath>(
			result,
			FilePath(L"data/UtilityGradleTestSuite/simple_gradle_project/src/test/java").makeAbsolute()));
	} else
		FAIL("TODO: Why does it fail under Linux?");
}

TEST_CASE("gradle wrapper detects source dependencies of simple projects")
{
	if constexpr (Os::isWindows()) {
		std::vector<std::wstring> requiredDependencies = {L"joda-time-2.2.jar"};

		cleanup();
		REQUIRE(utility::gradleCopyDependencies(
			FilePath(L"data/UtilityGradleTestSuite/simple_gradle_project"),
			tmpFolder.makeAbsolute(),
			false));

		const std::vector<FilePath> copiedDependencies = FileSystem::getFilePathsFromDirectory(tmpFolder);

		for (const std::wstring requiredDependency: requiredDependencies)
		{
			REQUIRE(utility::containsElement(
				copiedDependencies, tmpFolder.getConcatenated(requiredDependency)));
		}
		cleanup();
	} else
		FAIL("TODO: Why does it fail under Linux?");
}

TEST_CASE("gradle wrapper detects source and test dependencies of simple projects")
{
	if constexpr (Os::isWindows()) {
		std::vector<std::wstring> requiredDependencies = {
			L"joda-time-2.2.jar", L"hamcrest-core-1.3.jar", L"junit-4.12.jar"};

		cleanup();
		REQUIRE(utility::gradleCopyDependencies(
			FilePath(L"data/UtilityGradleTestSuite/simple_gradle_project"),
			tmpFolder.makeAbsolute(),
			true));

		const std::vector<FilePath> copiedDependencies = FileSystem::getFilePathsFromDirectory(tmpFolder);

		for (const std::wstring requiredDependency: requiredDependencies)
		{
			REQUIRE(utility::containsElement(
				copiedDependencies, tmpFolder.getConcatenated(requiredDependency)));
		}
		cleanup();
	} else
		FAIL("TODO: Why does it fail under Linux?");
}

#endif
