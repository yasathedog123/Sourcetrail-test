#include "ResourcePaths.h"

#include "AppPath.h"

FilePath ResourcePaths::getColorSchemesDirectoryPath()
{
	return AppPath::getSharedDataDirectoryPath().concatenate(L"data/color_schemes/");
}

FilePath ResourcePaths::getSyntaxHighlightingRulesDirectoryPath()
{
	return AppPath::getSharedDataDirectoryPath().concatenate(L"data/syntax_highlighting_rules/");
}

FilePath ResourcePaths::getFallbackDirectoryPath()
{
	return AppPath::getSharedDataDirectoryPath().concatenate(L"data/fallback/");
}

FilePath ResourcePaths::getFontsDirectoryPath()
{
	return AppPath::getSharedDataDirectoryPath().concatenate(L"data/fonts/");
}

FilePath ResourcePaths::getJavaDirectoryPath()
{
	return AppPath::getSharedDataDirectoryPath().concatenate(L"data/java/");
}

FilePath ResourcePaths::getPythonDirectoryPath()
{
	return AppPath::getSharedDataDirectoryPath().concatenate(L"data/python/");
}

FilePath ResourcePaths::getCxxCompilerHeaderDirectoryPath()
{
	return AppPath::getSharedDataDirectoryPath().concatenate(L"data/cxx/include/").getCanonical();
}

FilePath ResourcePaths::getPythonIndexerFilePath()
{
	return getPythonDirectoryPath().concatenate(L"SourcetrailPythonIndexer" + FilePath::getExecutableExtension());
}
