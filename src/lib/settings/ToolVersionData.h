#ifndef TOOLVERSIONDATA_H
#define TOOLVERSIONDATA_H

#include <string>
#include <vector>

class ToolVersionData {
};

class ClangVersionData : public ToolVersionData {
	public:
		static std::wstring getLatestCppStandard();
		static std::vector<std::wstring> getAvailableCppStandards();

		static std::wstring getLatestCStandard();
		static std::vector<std::wstring> getAvailableCStandards();
};

class VisualStudioVersionData : public ToolVersionData {
	public:
		static std::vector<std::wstring> getVersionRanges();
};

#endif // TOOLVERSIONDATA_H
