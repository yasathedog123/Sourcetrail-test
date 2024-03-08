#include "AppPath.h"

#include "utilityApp.h"

FilePath AppPath::s_sharedDataDirectoryPath(L"");
FilePath AppPath::s_cxxIndexerDirectoryPath(L"");

FilePath AppPath::getSharedDataDirectoryPath()
{
	return s_sharedDataDirectoryPath;
}

void AppPath::setSharedDataDirectoryPath(const FilePath& path)
{
	s_sharedDataDirectoryPath = path;
}

FilePath AppPath::getCxxIndexerFilePath()
{
	std::wstring cxxIndexerName(L"sourcetrail_indexer");
	if (utility::getOsType() == OS_WINDOWS)
	{
		cxxIndexerName = L"sourcetrail_indexer.exe";
	}

	if (!s_cxxIndexerDirectoryPath.empty())
	{
		return s_cxxIndexerDirectoryPath.getConcatenated(cxxIndexerName);
	}
	return s_sharedDataDirectoryPath.getConcatenated(cxxIndexerName);
}

void AppPath::setCxxIndexerDirectoryPath(const FilePath& path)
{
	s_cxxIndexerDirectoryPath = path;
}
