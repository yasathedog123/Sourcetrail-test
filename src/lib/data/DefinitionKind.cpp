#include "DefinitionKind.h"

template<>
DefinitionKind intToEnum(int definitionKind)
{
	switch (definitionKind)
	{
	case DEFINITION_NONE:
		return DEFINITION_NONE;
	case DEFINITION_IMPLICIT:
		return DEFINITION_IMPLICIT;
	case DEFINITION_EXPLICIT:
		return DEFINITION_EXPLICIT;
	}
	return DEFINITION_NONE;
}
