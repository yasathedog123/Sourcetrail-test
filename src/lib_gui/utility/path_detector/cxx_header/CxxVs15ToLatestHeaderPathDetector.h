#ifndef CXX_VS_15_TO_LATEST_HEADER_PATH_DETECTOR_H
#define CXX_VS_15_TO_LATEST_HEADER_PATH_DETECTOR_H

#include "PathDetector.h"

class CxxVs15ToLatestHeaderPathDetector: public PathDetector
{
public:
	class VisualStudioType {
	public:
		VisualStudioType(std::wstring_view versionRange);

		std::wstring getVersionRange() const;

	private:
		const std::wstring_view m_versionRange;
	};

	static const VisualStudioType VISUAL_STUDIO_2017;
	static const VisualStudioType VISUAL_STUDIO_2019;
	static const VisualStudioType VISUAL_STUDIO_2022;

	CxxVs15ToLatestHeaderPathDetector(const VisualStudioType &type);

private:
	const VisualStudioType m_type;

	std::vector<FilePath> doGetPaths() const override;

	static std::wstring getVsWhereProperty(const std::wstring &versionRange, const std::wstring &propertyName);
};

#endif
