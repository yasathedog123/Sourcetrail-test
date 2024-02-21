#ifndef MAVEN_PATH_DETECTOR_H
#define MAVEN_PATH_DETECTOR_H

#include "PathDetector.h"

class MavenPathDetector : public PathDetector
{
public:
	MavenPathDetector(const std::string &name);

private:
	std::vector<FilePath> doGetPaths() const override;
};

#endif
