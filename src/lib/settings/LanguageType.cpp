#include "LanguageType.h"

std::string languageTypeToString(LanguageType t)
{
	switch (t)
	{
#if BUILD_CXX_LANGUAGE_PACKAGE
	case LanguageType::C:
		return "C";
	case LanguageType::CXX:
		return "C++";
#endif	  // BUILD_CXX_LANGUAGE_PACKAGE
#if BUILD_JAVA_LANGUAGE_PACKAGE
	case LanguageType::JAVA:
		return "Java";
#endif	  // BUILD_JAVA_LANGUAGE_PACKAGE
#if BUILD_PYTHON_LANGUAGE_PACKAGE
	case LanguageType::PYTHON:
		return "Python";
#endif	  // BUILD_PYTHON_LANGUAGE_PACKAGE
	case LanguageType::CUSTOM:
		return "Custom";
	case LanguageType::UNKNOWN:
		break;
	}
	return "unknown";
}

LanguageType getLanguageTypeForSourceGroupType(SourceGroupType t)
{
	switch (t)
	{
#if BUILD_CXX_LANGUAGE_PACKAGE
	case SOURCE_GROUP_C_EMPTY:
		return LanguageType::C;
	case SOURCE_GROUP_CPP_EMPTY:
		return LanguageType::CXX;
	case SOURCE_GROUP_CXX_CDB:
		return LanguageType::CXX;
	case SOURCE_GROUP_CXX_CODEBLOCKS:
		return LanguageType::CXX;
	case SOURCE_GROUP_CXX_VS:
		return LanguageType::CXX;
#endif	  // BUILD_CXX_LANGUAGE_PACKAGE
#if BUILD_JAVA_LANGUAGE_PACKAGE
	case SOURCE_GROUP_JAVA_EMPTY:
		return LanguageType::JAVA;
	case SOURCE_GROUP_JAVA_MAVEN:
		return LanguageType::JAVA;
	case SOURCE_GROUP_JAVA_GRADLE:
		return LanguageType::JAVA;
#endif	  // BUILD_JAVA_LANGUAGE_PACKAGE
#if BUILD_PYTHON_LANGUAGE_PACKAGE
	case SOURCE_GROUP_PYTHON_EMPTY:
		return LanguageType::PYTHON;
#endif	  // BUILD_PYTHON_LANGUAGE_PACKAGE
	case SOURCE_GROUP_CUSTOM_COMMAND:
		return LanguageType::CUSTOM;
	default:
		break;
	}

	return LanguageType::UNKNOWN;
}
