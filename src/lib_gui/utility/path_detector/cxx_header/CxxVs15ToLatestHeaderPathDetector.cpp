#include "CxxVs15ToLatestHeaderPathDetector.h"

#include <string>

#include "FilePath.h"
#include "FileSystem.h"
#include "utility.h"
#include "utilityApp.h"
#include "utilityCxxHeaderDetection.h"

// Version table: https://github.com/microsoft/vswhere/wiki/Versions#release-versions

const CxxVs15ToLatestHeaderPathDetector::VisualStudioType CxxVs15ToLatestHeaderPathDetector::VISUAL_STUDIO_2017(L"[15.0, 16.0)");
const CxxVs15ToLatestHeaderPathDetector::VisualStudioType CxxVs15ToLatestHeaderPathDetector::VISUAL_STUDIO_2019(L"[16.0, 17.0)");
const CxxVs15ToLatestHeaderPathDetector::VisualStudioType CxxVs15ToLatestHeaderPathDetector::VISUAL_STUDIO_2022(L"[17.0, 18.0)");

CxxVs15ToLatestHeaderPathDetector::VisualStudioType::VisualStudioType(std::wstring_view versionRange)
	: m_versionRange(versionRange)
{
}

std::wstring CxxVs15ToLatestHeaderPathDetector::VisualStudioType::getVersionRange() const
{
	return std::wstring(m_versionRange);
}



CxxVs15ToLatestHeaderPathDetector::CxxVs15ToLatestHeaderPathDetector(const VisualStudioType &type)
	: PathDetector(utility::encodeToUtf8(getVsWhereProperty(type.getVersionRange(), L"displayName")))
	, m_type(type)
{
}

std::vector<FilePath> CxxVs15ToLatestHeaderPathDetector::doGetPaths() const
{
	std::vector<FilePath> headerSearchPaths;

	{
		const std::wstring installationPath = getVsWhereProperty(m_type.getVersionRange(), L"installationPath");

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
			APPLICATION_ARCHITECTURE_X86_32);
		if (windowsSdkHeaderSearchPaths.empty())
		{
			windowsSdkHeaderSearchPaths = utility::getWindowsSdkHeaderSearchPaths(
				APPLICATION_ARCHITECTURE_X86_64);
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
			FilePath(),
			false,
			10000);

		if (out.exitCode == 0)
			propertyValue = out.output;
	}
	return propertyValue;
}

