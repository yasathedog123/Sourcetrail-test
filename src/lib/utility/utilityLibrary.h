#ifndef UTILITY_LIBRARY_H
#define UTILITY_LIBRARY_H

#include <boost/dll.hpp>
#include <functional>
#include <string>

#include "FilePath.h"

namespace utility
{
template <typename Ret, typename... Args>
std::function<Ret(Args...)> loadFunctionFromLibrary(boost::dll::shared_library *sharedLibrary,
	const FilePath& libraryPath, const std::string& functionName, std::string *errorString)
{
	try {
		sharedLibrary->load(libraryPath.getPath());
	}
	catch (const boost::dll::fs::system_error &systemError) {
		*errorString = "Cannot load library '" + libraryPath.str() + "': " + systemError.what();
		return nullptr;
	}
	try {
		std::function<Ret(Args...)> functionId = sharedLibrary->get<Ret(Args...)>(functionName);
		return functionId;
	}
	catch (const boost::dll::fs::system_error &systemError) {
		*errorString = "Cannot get symbol '" + functionName + "' from library '" + libraryPath.str() + "': " + systemError.what();
		return nullptr;
	}
}

}

#endif
