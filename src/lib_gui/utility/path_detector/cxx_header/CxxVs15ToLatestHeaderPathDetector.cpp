#include "CxxVs15ToLatestHeaderPathDetector.h"

#include <string>

#include "FilePath.h"
#include "FileSystem.h"
#include "utility.h"
#include "utilityApp.h"
#include "utilityCxxHeaderDetection.h"

using namespace std;
using namespace utility;
using namespace boost::chrono;

CxxVs15ToLatestHeaderPathDetector::CxxVs15ToLatestHeaderPathDetector(const wstring &versionRange)
	: PathDetector(utility::encodeToUtf8(getVsWhereProperty(versionRange, L"displayName")))
	, m_versionRange(versionRange)
{
}

std::vector<FilePath> CxxVs15ToLatestHeaderPathDetector::doGetPaths() const
{
	std::vector<FilePath> headerSearchPaths;

	{
		const std::wstring installationPath = getVsWhereProperty(m_versionRange, L"installationPath");

		if (!installationPath.empty())
		{
			const FilePath vsInstallPath(installationPath);
			if (vsInstallPath.exists())
			{
				for (const FilePath& versionPath: FileSystem::getDirectSubDirectories(
							vsInstallPath.getConcatenated(L"VC/Tools/MSVC")))
				{
					if (versionPath.exists())
					{
						headerSearchPaths.push_back(versionPath.getConcatenated(L"include"));
						headerSearchPaths.push_back(
							versionPath.getConcatenated(L"atlmfc/include"));
					}
				}
				headerSearchPaths.push_back(
					vsInstallPath.getConcatenated(L"VC/Auxiliary/VS/include"));
				headerSearchPaths.push_back(
					vsInstallPath.getConcatenated(L"VC/Auxiliary/VS/UnitTest/include"));
			}
		}
	}

	if (!headerSearchPaths.empty())
	{
		std::vector<FilePath> windowsSdkHeaderSearchPaths = utility::getWindowsSdkHeaderSearchPaths(
			Platform::Architecture::BITS_32);
		if (windowsSdkHeaderSearchPaths.empty())
		{
			windowsSdkHeaderSearchPaths = utility::getWindowsSdkHeaderSearchPaths(
				Platform::Architecture::BITS_64);
		}
		utility::append(headerSearchPaths, windowsSdkHeaderSearchPaths);
	}

	return headerSearchPaths;
}

std::wstring CxxVs15ToLatestHeaderPathDetector::getVsWhereProperty(const std::wstring &versionRange, const std::wstring &propertyName)
{
	std::wstring propertyValue;

	// vswhere location: https://github.com/microsoft/vswhere#visual-studio-locator

	const std::vector<FilePath> expandedPaths =
		FilePath(L"%ProgramFiles(x86)%/Microsoft Visual Studio/Installer/vswhere.exe")
			.expandEnvironmentVariables();
	if (!expandedPaths.empty())
	{
		const utility::ProcessOutput out = utility::executeProcess(expandedPaths.front().wstr(),
			{ L"-version", versionRange, L"-property", propertyName },
			FilePath(), false, milliseconds(10000));

		if (out.exitCode == 0)
			propertyValue = out.output;
	}
	return propertyValue;
}

