#include "MavenPathDetector.h"

#include "FilePath.h"
#include "utilityApp.h"

MavenPathDetector::MavenPathDetector(const std::string &name)
	: PathDetector(name)
{}

std::vector<FilePath> MavenPathDetector::doGetPaths() const
{
	std::vector<FilePath> paths;

	bool ok;
	FilePath mavenPath(utility::searchPath(L"mvn", ok));
	if (ok && !mavenPath.empty() && mavenPath.exists())
	{
		paths.push_back(mavenPath);
	}
	return paths;
}
