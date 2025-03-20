#ifndef ACCESS_KIND_H
#define ACCESS_KIND_H

#include "utilityEnum.h"

#include <string>

// these values need to be the same as AccessKind in Java code
enum AccessKind
{	 
	ACCESS_NONE = 0,
	ACCESS_PUBLIC = 1,
	ACCESS_PROTECTED = 2,
	ACCESS_PRIVATE = 3,
	ACCESS_DEFAULT = 4,
	ACCESS_TEMPLATE_PARAMETER = 5,
	ACCESS_TYPE_PARAMETER = 6
};

template <>
AccessKind intToEnum(int value);

std::wstring accessKindToString(AccessKind t);

#endif	  // ACCESS_KIND_H
