#ifndef TOOLVERSIONSUPPORT_H
#define TOOLVERSIONSUPPORT_H

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

class EclipseVersionSupport final : public ToolVersionSupport {
	public:
		static std::wstring getLatestJavaStandard();
		static std::vector<std::wstring> getAvailableJavaStandards();
};

class VisualStudioVersionSupport final : public ToolVersionSupport {
	public:
		static std::vector<std::wstring> getVersionRanges();
};

class WindowsSdkVersionSupport final : public ToolVersionSupport {
	public:
		static std::vector<std::string> getVersions();
};

#endif
