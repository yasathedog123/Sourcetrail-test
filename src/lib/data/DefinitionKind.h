#ifndef DEFINITION_KIND_H
#define DEFINITION_KIND_H

#include "utilityEnum.h"

// these values need to be the same as DefinitionKind in Java code
enum DefinitionKind
{	 
	DEFINITION_NONE = 0,
	DEFINITION_IMPLICIT = 1,
	DEFINITION_EXPLICIT = 2
};

template<>
DefinitionKind intToEnum(int definitionKind);

#endif	  // DEFINITION_TYPE_H
