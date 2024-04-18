#ifndef CXX_VS_15_TO_LATEST_HEADER_PATH_DETECTOR_H
#define CXX_VS_15_TO_LATEST_HEADER_PATH_DETECTOR_H

#include "PathDetector.h"

class CxxVs15ToLatestHeaderPathDetector: public PathDetector
{
public:
	CxxVs15ToLatestHeaderPathDetector(const std::wstring &versionRange);

private:
	const std::wstring m_versionRange;

	std::vector<FilePath> doGetPaths() const override;

	static std::wstring getVsWhereProperty(const std::wstring &versionRange, const std::wstring &propertyName);
};

#endif
