#include "JavaPathDetectorLinuxWindowsMac.h"

#include "FilePath.h"
#include "utilityApp.h"

using namespace std;
using namespace utility;

namespace
{

FilePath getFilePathRelativeToJavaExecutable(const FilePath& javaExecutablePath)
{
	wstring relativeJvmLibPath;

	// If those paths change then adjust:
	// - The place holder hints in QtProjectWizardContentPreferences.cpp
	// - The documentation in DOCUMENTATION.md

	if constexpr (Os::isLinux())
		relativeJvmLibPath = L"/../lib/server/libjvm.so";
	else if constexpr (Os::isWindows())
		relativeJvmLibPath = L"/./server/jvm.dll";
	else if constexpr (Os::isMac())
		relativeJvmLibPath = L"/../lib/server/libjvm.dylib";

	FilePath jvmLibPath = javaExecutablePath.getParentDirectory().concatenate(relativeJvmLibPath);
	if (jvmLibPath.exists())
		return jvmLibPath.makeCanonical();

	return FilePath();
}

FilePath getJavaInPath()
{
	bool ok;
	FilePath javaPath(searchPath(L"java", ok));
	if (ok && !javaPath.empty() && javaPath.exists())
	{
		return javaPath;
	}
	return FilePath();
}

FilePath getJavaInJavaHome()
{
	string command = "";
	char* p = getenv("JAVA_HOME");
	if (p == nullptr)
	{
		return FilePath();
	}

	FilePath javaPath(p);
	javaPath.concatenate(FilePath("/bin/java"));
	if (!javaPath.empty() && javaPath.exists())
	{
		return javaPath;
	}
	return FilePath();
}

FilePath readLink(const FilePath& path)
{
	return path.getCanonical().getAbsolute();
}

}

JavaPathDetectorLinuxWindowsMac::JavaPathDetectorLinuxWindowsMac(const string &name)
	: JavaPathDetector(name)
{
}

vector<FilePath> JavaPathDetectorLinuxWindowsMac::doGetPaths() const
{
	vector<FilePath> paths;
	FilePath p = getJavaInPath();
	if (!p.empty())
	{
		paths.push_back(p);
	}
	p = getJavaInJavaHome();
	if (!p.empty())
	{
		paths.push_back(p);
	}
	for (const FilePath& path: paths)
	{
		FilePath absoluteJavaPath = readLink(path);
		FilePath jvmLibrary = getFilePathRelativeToJavaExecutable(absoluteJavaPath);
		if (jvmLibrary.exists())
		{
			vector<FilePath> foundPath = {jvmLibrary};
			return foundPath;
		}
	}
	return vector<FilePath>();
}

