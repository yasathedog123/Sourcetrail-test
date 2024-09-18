#ifndef TOOLVERSIONDATA_H
#define TOOLVERSIONDATA_H

#include <string>
#include <vector>

// This is an attempt to centralize all the version information which is most likely to change:

class ToolVersionSupport { // Just a 'marker' interface
};

class ClangVersionSupport final : public ToolVersionSupport {
	public:
		static std::wstring getLatestCppStandard();
		static std::vector<std::wstring> getAvailableCppStandards();

		static std::wstring getLatestCStandard();
		static std::vector<std::wstring> getAvailableCStandards();
};

class VisualStudioVersionSupport final : public ToolVersionSupport {
	public:
		static std::vector<std::wstring> getVersionRanges();
};

class WindowsSdkVersionSupport final : public ToolVersionSupport {
	public:
		static std::vector<std::string> getVersions();
};

#endif // TOOLVERSIONDATA_H
