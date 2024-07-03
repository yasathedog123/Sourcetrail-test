#include "Catch2.hpp"

#include <fstream>

#include "language_packages.h"

#include "AppPath.h"
#include "Application.h"
#include "ApplicationSettings.h"
#include "FileSystem.h"
#include "IndexerCommandCustom.h"
#include "ProjectSettings.h"
#include "SourceGroupCustomCommand.h"
#include "SourceGroupSettingsCustomCommand.h"
#include "TextAccess.h"
#include "Version.h"
#include "utilityApp.h"
#include "utilityPathDetection.h"
#include "utilityString.h"

#if BUILD_CXX_LANGUAGE_PACKAGE
#	include "IndexerCommandCxx.h"
#	include "SourceGroupCxxCdb.h"
#	include "SourceGroupCxxCodeblocks.h"
#	include "SourceGroupCxxEmpty.h"
#	include "SourceGroupSettingsCEmpty.h"
#	include "SourceGroupSettingsCppEmpty.h"
#	include "SourceGroupSettingsCxxCdb.h"
#	include "SourceGroupSettingsCxxCodeblocks.h"
#endif	  // BUILD_CXX_LANGUAGE_PACKAGE

#if BUILD_JAVA_LANGUAGE_PACKAGE
#	include "IndexerCommandJava.h"
#	include "JavaEnvironmentFactory.h"
#	include "SourceGroupJavaEmpty.h"
#	include "SourceGroupJavaGradle.h"
#	include "SourceGroupJavaMaven.h"
#	include "SourceGroupSettingsJavaEmpty.h"
#	include "SourceGroupSettingsJavaGradle.h"
#	include "SourceGroupSettingsJavaMaven.h"
#	include "utilityJava.h"
#endif	  // BUILD_JAVA_LANGUAGE_PACKAGE

using namespace std;
using namespace utility;

namespace
{
const bool updateExpectedOutput = false;

static FilePath getInputDirectoryPath(const std::wstring& projectName)
{
	return FilePath(L"data/SourceGroupTestSuite/" + projectName + L"/input")
		.makeAbsolute()
		.makeCanonical();
}

static FilePath getOutputDirectoryPath(const std::wstring& projectName)
{
	return FilePath(L"data/SourceGroupTestSuite/" + projectName + L"/expected_output")
		.makeAbsolute()
		.makeCanonical();
}

#if BUILD_JAVA_LANGUAGE_PACKAGE
std::string setupJavaEnvironmentFactory()
{
	return utility::prepareJavaEnvironment(FilePath(L"../app/data/java/"));
}
#endif	  // BUILD_JAVA_LANGUAGE_PACKAGE

#if BUILD_CXX_LANGUAGE_PACKAGE
std::wstring indexerCommandCxxToString(
	std::shared_ptr<const IndexerCommandCxx> indexerCommand, const FilePath& baseDirectory)
{
	std::wstring result;
	result += L"SourceFilePath: \"" +
		indexerCommand->getSourceFilePath().getRelativeTo(baseDirectory).wstr() + L"\"\n";
	for (const FilePath& indexedPath: indexerCommand->getIndexedPaths())
	{
		result += L"\tIndexedPath: \"" + indexedPath.getRelativeTo(baseDirectory).wstr() + L"\"\n";
	}
	for (std::wstring compilerFlag: indexerCommand->getCompilerFlags())
	{
		FilePath flagAsPath(compilerFlag);
		if (flagAsPath.exists())
		{
			compilerFlag = flagAsPath.getRelativeTo(baseDirectory).wstr();
		}
		result += L"\tCompilerFlag: \"" + compilerFlag + L"\"\n";
	}
	for (const FilePathFilter& filter: indexerCommand->getExcludeFilters())
	{
		result += L"\tExcludeFilter: \"" + filter.wstr() + L"\"\n";
	}
	return result;
}
#endif	  // BUILD_CXX_LANGUAGE_PACKAGE

#if BUILD_JAVA_LANGUAGE_PACKAGE
std::wstring indexerCommandJavaToString(
	std::shared_ptr<const IndexerCommandJava> indexerCommand, const FilePath& baseDirectory)
{
	std::wstring result;
	result += L"SourceFilePath: \"" +
		indexerCommand->getSourceFilePath().getRelativeTo(baseDirectory).wstr() + L"\"\n";
	result += L"\tLanguageStandard: \"" + indexerCommand->getLanguageStandard() + L"\"\n";
	for (const FilePath& classPathItem: indexerCommand->getClassPath())
	{
		result += L"\tClassPathItem: \"" + classPathItem.getRelativeTo(baseDirectory).wstr() +
			L"\"\n";
	}
	return result;
}
#endif	  // BUILD_JAVA_LANGUAGE_PACKAGE

std::wstring indexerCommandCustomToString(
	std::shared_ptr<const IndexerCommandCustom> indexerCommand, const FilePath& baseDirectory)
{
	std::wstring result;
	result += L"IndexerCommandCustom\n";
	result += L"\tSourceFilePath: \"" +
		indexerCommand->getSourceFilePath().getRelativeTo(baseDirectory).wstr() + L"\"\n";
	result += L"\tCustom Command: \"" + indexerCommand->getCommand() + L"\"\n";
	result += L"\tArguments:\n";
	for (const std::wstring& argument: indexerCommand->getArguments())
	{
		result += L"\t\t\"" + argument + L"\"\n";
	}
	return result;
}

std::wstring indexerCommandToString(
	std::shared_ptr<IndexerCommand> indexerCommand, const FilePath& baseDirectory)
{
	if (indexerCommand)
	{
#if BUILD_CXX_LANGUAGE_PACKAGE
		if (std::shared_ptr<const IndexerCommandCxx> indexerCommandCxx =
				std::dynamic_pointer_cast<const IndexerCommandCxx>(indexerCommand))
		{
			return indexerCommandCxxToString(indexerCommandCxx, baseDirectory);
		}
#endif	  // BUILD_CXX_LANGUAGE_PACKAGE
#if BUILD_JAVA_LANGUAGE_PACKAGE
		if (std::shared_ptr<const IndexerCommandJava> indexerCommandJava =
				std::dynamic_pointer_cast<const IndexerCommandJava>(indexerCommand))
		{
			return indexerCommandJavaToString(indexerCommandJava, baseDirectory);
		}
#endif	  // BUILD_JAVA_LANGUAGE_PACKAGE
		if (std::shared_ptr<const IndexerCommandCustom> indexerCommandCustom =
				std::dynamic_pointer_cast<const IndexerCommandCustom>(indexerCommand))
		{
			return indexerCommandCustomToString(indexerCommandCustom, baseDirectory);
		}
		return L"Unsupported indexer command type: " +
			utility::decodeFromUtf8(
				   indexerCommandTypeToString(indexerCommand->getIndexerCommandType()));
	}
	return L"No IndexerCommand provided.";
}

std::shared_ptr<TextAccess> generateExpectedOutput(
	std::wstring projectName, std::shared_ptr<const SourceGroup> sourceGroup)
{
	const FilePath projectDataRoot = getInputDirectoryPath(projectName).makeAbsolute();

	RefreshInfo info;
	info.filesToIndex = sourceGroup->getAllSourceFilePaths();
	std::vector<std::shared_ptr<IndexerCommand>> indexerCommands = sourceGroup->getIndexerCommands(
		info);

	std::sort(
		indexerCommands.begin(),
		indexerCommands.end(),
		[](std::shared_ptr<IndexerCommand> a, std::shared_ptr<IndexerCommand> b) {
			return a->getSourceFilePath().wstr() < b->getSourceFilePath().wstr();
		});

	std::wstring outputString;
	for (const std::shared_ptr<IndexerCommand> &indexerCommand : indexerCommands) {
		outputString += indexerCommandToString(indexerCommand, projectDataRoot);
	}

	return TextAccess::createFromString(utility::encodeToUtf8(outputString));
}

std::wstring getOutputFilename()
{
	if constexpr (Os::isWindows())
		return L"output_windows.txt";
	else
		return L"output_unix.txt";

}
void generateAndCompareExpectedOutput(
	std::wstring projectName, std::shared_ptr<const SourceGroup> sourceGroup)
{
	const std::shared_ptr<const TextAccess> output = generateExpectedOutput(projectName, sourceGroup);
	const std::wstring expectedOutputFileName = getOutputFilename();

	const FilePath expectedOutputFilePath =
		getOutputDirectoryPath(projectName).concatenate(expectedOutputFileName);
	if (updateExpectedOutput || !expectedOutputFilePath.exists())
	{
		std::ofstream expectedOutputFile;
		expectedOutputFile.open(expectedOutputFilePath.str());
		expectedOutputFile << output->getText();
		expectedOutputFile.close();
	}
	else
	{
		const std::shared_ptr<const TextAccess> expectedOutput = TextAccess::createFromFile(
			expectedOutputFilePath);
		REQUIRE_MESSAGE(
			("Output does not match the expected line count for project \"" +
			 utility::encodeToUtf8(projectName) + "\". Output was: " + output->getText())
				.c_str(),
			expectedOutput->getLineCount() == output->getLineCount());
		if (expectedOutput->getLineCount() == output->getLineCount())
		{
			for (unsigned int i = 1; i <= expectedOutput->getLineCount(); i++)
			{
				REQUIRE(expectedOutput->getLine(i) == output->getLine(i));
			}
		}
	}
}
}	 // namespace

#if BUILD_JAVA_LANGUAGE_PACKAGE

TEST_CASE("finds all jar dependencies")
{
	for (const std::wstring& jarName: utility::getRequiredJarNames())
	{
		FilePath jarPath = FilePath(L"../app/data/java/lib/").concatenate(jarName);
		REQUIRE_MESSAGE("Jar dependency path does not exist: " + jarPath.str(), jarPath.exists());
	}
}

TEST_CASE("can setup environment factory")
{
	std::vector<FilePath> javaPaths = utility::getJavaRuntimePathDetector()->getPaths();
	if (!javaPaths.empty())
	{
		ApplicationSettings::getInstance()->setJavaPath(javaPaths[0]);
	}
	const std::string errorString = setupJavaEnvironmentFactory();

	REQUIRE("" == errorString);

	// if this one fails, maybe your java_path in the test settings is wrong.
	REQUIRE(JavaEnvironmentFactory::getInstance().use_count() >= 1);
}

#endif	  // BUILD_JAVA_LANGUAGE_PACKAGE

TEST_CASE("can create application instance")
{
	// required to query in SourceGroup for dialog view... this is not a very elegant solution.
	// should be refactored to pass dialog view to SourceGroup on creation.
	Application::createInstance(Version(), nullptr, nullptr);
	REQUIRE(Application::getInstance().use_count() >= 1);
}

#if BUILD_CXX_LANGUAGE_PACKAGE
TEST_CASE("source group cxx c empty generates expected output")
{
	const std::wstring projectName = L"cxx_c_empty";

	ProjectSettings projectSettings;
	projectSettings.setProjectFilePath(L"non_existent_project", getInputDirectoryPath(projectName));

	std::shared_ptr<SourceGroupSettingsCEmpty> sourceGroupSettings =
		std::make_shared<SourceGroupSettingsCEmpty>("fake_id", &projectSettings);
	sourceGroupSettings->setSourcePaths({getInputDirectoryPath(projectName).concatenate(L"src")});
	sourceGroupSettings->setSourceExtensions({L".c"});
	sourceGroupSettings->setExcludeFilterStrings({L"**/excluded/**"});
	sourceGroupSettings->setTargetOptionsEnabled(true);
	sourceGroupSettings->setTargetArch(L"test_arch");
	sourceGroupSettings->setTargetVendor(L"test_vendor");
	sourceGroupSettings->setTargetSys(L"test_sys");
	sourceGroupSettings->setTargetAbi(L"test_abi");
	sourceGroupSettings->setCStandard(L"c11");
	sourceGroupSettings->setHeaderSearchPaths(
		{getInputDirectoryPath(projectName).concatenate(L"header_search/local")});
	sourceGroupSettings->setFrameworkSearchPaths(
		{getInputDirectoryPath(projectName).concatenate(L"framework_search/local")});
	sourceGroupSettings->setCompilerFlags({L"-local-flag"});

	std::shared_ptr<ApplicationSettings> applicationSettings = ApplicationSettings::getInstance();

	std::vector<FilePath> storedHeaderSearchPaths = applicationSettings->getHeaderSearchPaths();
	std::vector<FilePath> storedFrameworkSearchPaths = applicationSettings->getFrameworkSearchPaths();

	applicationSettings->setHeaderSearchPaths({FilePath(L"test/header/search/path")});
	applicationSettings->setFrameworkSearchPaths({FilePath(L"test/framework/search/path")});

	generateAndCompareExpectedOutput(
		projectName, std::make_shared<SourceGroupCxxEmpty>(sourceGroupSettings));

	applicationSettings->setHeaderSearchPaths(storedHeaderSearchPaths);
	applicationSettings->setFrameworkSearchPaths(storedFrameworkSearchPaths);
}

TEST_CASE("source group cxx cpp empty generates expected output")
{
	const std::wstring projectName = L"cxx_cpp_empty";

	ProjectSettings projectSettings;
	projectSettings.setProjectFilePath(L"non_existent_project", getInputDirectoryPath(projectName));

	std::shared_ptr<SourceGroupSettingsCppEmpty> sourceGroupSettings =
		std::make_shared<SourceGroupSettingsCppEmpty>("fake_id", &projectSettings);
	sourceGroupSettings->setSourcePaths({getInputDirectoryPath(projectName).concatenate(L"/src")});
	sourceGroupSettings->setSourceExtensions({L".cpp"});
	sourceGroupSettings->setExcludeFilterStrings({L"**/excluded/**"});
	sourceGroupSettings->setTargetOptionsEnabled(true);
	sourceGroupSettings->setTargetArch(L"test_arch");
	sourceGroupSettings->setTargetVendor(L"test_vendor");
	sourceGroupSettings->setTargetSys(L"test_sys");
	sourceGroupSettings->setTargetAbi(L"test_abi");
	sourceGroupSettings->setCppStandard(L"c++11");
	sourceGroupSettings->setHeaderSearchPaths(
		{getInputDirectoryPath(projectName).concatenate(L"header_search/local")});
	sourceGroupSettings->setFrameworkSearchPaths(
		{getInputDirectoryPath(projectName).concatenate(L"framework_search/local")});
	sourceGroupSettings->setCompilerFlags({L"-local-flag"});

	std::shared_ptr<ApplicationSettings> applicationSettings = ApplicationSettings::getInstance();

	std::vector<FilePath> storedHeaderSearchPaths = applicationSettings->getHeaderSearchPaths();
	std::vector<FilePath> storedFrameworkSearchPaths = applicationSettings->getFrameworkSearchPaths();

	applicationSettings->setHeaderSearchPaths({FilePath(L"test/header/search/path")});
	applicationSettings->setFrameworkSearchPaths({FilePath(L"test/framework/search/path")});

	generateAndCompareExpectedOutput(
		projectName, std::make_shared<SourceGroupCxxEmpty>(sourceGroupSettings));

	applicationSettings->setHeaderSearchPaths(storedHeaderSearchPaths);
	applicationSettings->setFrameworkSearchPaths(storedFrameworkSearchPaths);
}

TEST_CASE("source group cxx codeblocks generates expected output")
{
	const std::wstring projectName = L"cxx_codeblocks";
	const FilePath cbpPath = getInputDirectoryPath(projectName).concatenate(L"project.cbp");
	const FilePath sourceCbpPath =
		getInputDirectoryPath(projectName).concatenate(L"project.cbp.in");

	FileSystem::remove(cbpPath);

	{
		std::ofstream fileStream;
		fileStream.open(cbpPath.str(), std::ios::app);
		fileStream << utility::replace(
			TextAccess::createFromFile(sourceCbpPath)->getText(),
			"<source_path>",
			getInputDirectoryPath(projectName).concatenate(L"src").getAbsolute().str());
		fileStream.close();
	}

	ProjectSettings projectSettings;
	projectSettings.setProjectFilePath(L"non_existent_project", getInputDirectoryPath(projectName));

	std::shared_ptr<SourceGroupSettingsCxxCodeblocks> sourceGroupSettings =
		std::make_shared<SourceGroupSettingsCxxCodeblocks>("fake_id", &projectSettings);
	sourceGroupSettings->setCodeblocksProjectPath(cbpPath);
	sourceGroupSettings->setCppStandard(L"c++11");
	sourceGroupSettings->setCStandard(L"c11");
	sourceGroupSettings->setExcludeFilterStrings({L"**/excluded/**"});
	sourceGroupSettings->setIndexedHeaderPaths({FilePath(L"test/indexed/header/path")});
	sourceGroupSettings->setSourceExtensions({L".cpp", L".c"});
	sourceGroupSettings->setHeaderSearchPaths(
		{getInputDirectoryPath(projectName).concatenate(L"header_search/local")});
	sourceGroupSettings->setFrameworkSearchPaths(
		{getInputDirectoryPath(projectName).concatenate(L"framework_search/local")});
	sourceGroupSettings->setCompilerFlags({L"-local-flag"});

	std::shared_ptr<ApplicationSettings> applicationSettings = ApplicationSettings::getInstance();

	std::vector<FilePath> storedHeaderSearchPaths = applicationSettings->getHeaderSearchPaths();
	std::vector<FilePath> storedFrameworkSearchPaths = applicationSettings->getFrameworkSearchPaths();

	applicationSettings->setHeaderSearchPaths({FilePath(L"test/header/search/path")});
	applicationSettings->setFrameworkSearchPaths({FilePath(L"test/framework/search/path")});

	generateAndCompareExpectedOutput(
		projectName, std::make_shared<SourceGroupCxxCodeblocks>(sourceGroupSettings));

	applicationSettings->setHeaderSearchPaths(storedHeaderSearchPaths);
	applicationSettings->setFrameworkSearchPaths(storedFrameworkSearchPaths);

	FileSystem::remove(cbpPath);
}

TEST_CASE("source group cxx cdb generates expected output")
{
	const std::wstring projectName = L"cxx_cdb";

	ProjectSettings projectSettings;
	projectSettings.setProjectFilePath(L"non_existent_project", getInputDirectoryPath(projectName));

	std::shared_ptr<SourceGroupSettingsCxxCdb> sourceGroupSettings =
		std::make_shared<SourceGroupSettingsCxxCdb>("fake_id", &projectSettings);
	sourceGroupSettings->setIndexedHeaderPaths({FilePath(L"test/indexed/header/path")});
	sourceGroupSettings->setCompilationDatabasePath(
		getInputDirectoryPath(projectName).concatenate(L"compile_commands.json"));
	sourceGroupSettings->setExcludeFilterStrings({L"**/excluded/**"});
	sourceGroupSettings->setHeaderSearchPaths(
		{getInputDirectoryPath(projectName).concatenate(L"header_search/local")});
	sourceGroupSettings->setFrameworkSearchPaths(
		{getInputDirectoryPath(projectName).concatenate(L"framework_search/local")});
	sourceGroupSettings->setCompilerFlags({L"-local-flag"});

	std::shared_ptr<ApplicationSettings> applicationSettings = ApplicationSettings::getInstance();

	std::vector<FilePath> storedHeaderSearchPaths = applicationSettings->getHeaderSearchPaths();
	std::vector<FilePath> storedFrameworkSearchPaths = applicationSettings->getFrameworkSearchPaths();

	applicationSettings->setHeaderSearchPaths({FilePath(L"test/header/search/path")});
	applicationSettings->setFrameworkSearchPaths({FilePath(L"test/framework/search/path")});

	generateAndCompareExpectedOutput(
		projectName, std::make_shared<SourceGroupCxxCdb>(sourceGroupSettings));

	applicationSettings->setHeaderSearchPaths(storedHeaderSearchPaths);
	applicationSettings->setFrameworkSearchPaths(storedFrameworkSearchPaths);
}

TEST_CASE("source gropup cxx c correct default standard")
{
	wstring defaultCStandard = SourceGroupSettingsWithCStandard::getDefaultCStandard();
	wstring defaultCppStandard = SourceGroupSettingsWithCppStandard::getDefaultCppStandard();

	if constexpr (Os::isLinux()) {
		REQUIRE(  defaultCStandard.substr(0, 3) == L"gnu");
		REQUIRE(defaultCppStandard.substr(0, 5) == L"gnu++");
	} else {
		REQUIRE(  defaultCStandard.substr(0, 1) == L"c");
		REQUIRE(defaultCppStandard.substr(0, 3) == L"c++");
	}
}

#endif	  // BUILD_CXX_LANGUAGE_PACKAGE

#if BUILD_JAVA_LANGUAGE_PACKAGE

TEST_CASE("sourcegroup java empty generates expected output")
{
	const std::wstring projectName = L"java_empty";

	ProjectSettings projectSettings;
	projectSettings.setProjectFilePath(L"non_existent_project", getInputDirectoryPath(projectName));

	std::shared_ptr<SourceGroupSettingsJavaEmpty> sourceGroupSettings =
		std::make_shared<SourceGroupSettingsJavaEmpty>("fake_id", &projectSettings);
	sourceGroupSettings->setSourceExtensions({L".java"});
	sourceGroupSettings->setExcludeFilterStrings({L"**/Foo.java"});
	sourceGroupSettings->setJavaStandard({L"10"});
	sourceGroupSettings->setSourcePaths({getInputDirectoryPath(projectName).concatenate(L"src")});
	sourceGroupSettings->setUseJreSystemLibrary(true);
	sourceGroupSettings->setClasspath(
		{getInputDirectoryPath(projectName).concatenate(L"lib/dependency.jar"),
		 getInputDirectoryPath(projectName).concatenate(L"classpath_dir")});

	std::shared_ptr<ApplicationSettings> applicationSettings = ApplicationSettings::getInstance();

	std::vector<FilePath> storedJreSystemLibraryPaths =
		applicationSettings->getJreSystemLibraryPaths();

	applicationSettings->setJreSystemLibraryPaths({FilePath(L"test/jre/system/library/path.jar")});

	generateAndCompareExpectedOutput(
		projectName, std::make_shared<SourceGroupJavaEmpty>(sourceGroupSettings));

	applicationSettings->setJreSystemLibraryPaths(storedJreSystemLibraryPaths);
}

TEST_CASE("sourcegroup java gradle generates expected output")
{
	if constexpr (utility::Os::isWindows()) {
		const std::wstring projectName = L"java_gradle";

		ProjectSettings projectSettings;
		projectSettings.setProjectFilePath(L"non_existent_project", getInputDirectoryPath(projectName));

		std::shared_ptr<SourceGroupSettingsJavaGradle> sourceGroupSettings =
			std::make_shared<SourceGroupSettingsJavaGradle>("fake_id", &projectSettings);
		sourceGroupSettings->setSourceExtensions({L".java"});
		sourceGroupSettings->setExcludeFilterStrings({L"**/HelloWorld.java"});
		sourceGroupSettings->setJavaStandard({L"10"});
		sourceGroupSettings->setGradleProjectFilePath(
			{getInputDirectoryPath(projectName).concatenate(L"build.gradle")});
		sourceGroupSettings->setShouldIndexGradleTests(true);

		std::shared_ptr<ApplicationSettings> applicationSettings = ApplicationSettings::getInstance();

		const FilePath storedAppPath = AppPath::getSharedDataDirectoryPath();
		AppPath::setSharedDataDirectoryPath(storedAppPath.getConcatenated(L"../app").makeAbsolute());

		std::vector<FilePath> storedJreSystemLibraryPaths =
			applicationSettings->getJreSystemLibraryPaths();
		applicationSettings->setJreSystemLibraryPaths({FilePath(L"test/jre/system/library/path.jar")});

		generateAndCompareExpectedOutput(
			projectName, std::make_shared<SourceGroupJavaGradle>(sourceGroupSettings));

		applicationSettings->setJreSystemLibraryPaths(storedJreSystemLibraryPaths);
		AppPath::setSharedDataDirectoryPath(storedAppPath);
	} else
		FAIL("TODO: Why does it fail under Linux?");
}

TEST_CASE("sourcegroup java maven generates expected output")
{
	std::vector<FilePath> mavenPaths = utility::getMavenExecutablePathDetector()->getPaths();

	REQUIRE(!mavenPaths.empty());

	if (!mavenPaths.empty())
	{
		ApplicationSettings::getInstance()->setMavenPath(mavenPaths.front());
	}

	const std::wstring projectName = L"java_maven";

	ProjectSettings projectSettings;
	projectSettings.setProjectFilePath(L"non_existent_project", getInputDirectoryPath(projectName));

	std::shared_ptr<SourceGroupSettingsJavaMaven> sourceGroupSettings =
		std::make_shared<SourceGroupSettingsJavaMaven>("fake_id", &projectSettings);
	sourceGroupSettings->setSourceExtensions({L".java"});
	sourceGroupSettings->setExcludeFilterStrings({L"**/Foo.java"});
	sourceGroupSettings->setJavaStandard({L"10"});
	sourceGroupSettings->setMavenProjectFilePath(
		{getInputDirectoryPath(projectName).concatenate(L"my-app/pom.xml")});
	sourceGroupSettings->setShouldIndexMavenTests(true);

	std::shared_ptr<ApplicationSettings> applicationSettings = ApplicationSettings::getInstance();

	std::vector<FilePath> storedJreSystemLibraryPaths =
		applicationSettings->getJreSystemLibraryPaths();

	applicationSettings->setJreSystemLibraryPaths({FilePath(L"test/jre/system/library/path.jar")});

	generateAndCompareExpectedOutput(
		projectName, std::make_shared<SourceGroupJavaMaven>(sourceGroupSettings));

	applicationSettings->setJreSystemLibraryPaths(storedJreSystemLibraryPaths);
}

#endif	  // BUILD_JAVA_LANGUAGE_PACKAGE

// fixme: test python source group here

TEST_CASE("source group custom command generates expected output")
{
	const std::wstring projectName = L"custom_command";

	ProjectSettings projectSettings;
	projectSettings.setProjectFilePath(L"non_existent_project", getInputDirectoryPath(projectName));

	std::shared_ptr<SourceGroupSettingsCustomCommand> sourceGroupSettings =
		std::make_shared<SourceGroupSettingsCustomCommand>("fake_id", &projectSettings);
	sourceGroupSettings->setCustomCommand(L"echo \"Hello World\"");
	sourceGroupSettings->setSourcePaths({getInputDirectoryPath(projectName).concatenate(L"/src")});
	sourceGroupSettings->setSourceExtensions({L".txt"});
	sourceGroupSettings->setExcludeFilterStrings({L"**/excluded/**"});

	generateAndCompareExpectedOutput(
		projectName, std::make_shared<SourceGroupCustomCommand>(sourceGroupSettings));
}

TEST_CASE("can destroy application instance")
{
	Application::destroyInstance();
	REQUIRE(0 == Application::getInstance().use_count());
}
