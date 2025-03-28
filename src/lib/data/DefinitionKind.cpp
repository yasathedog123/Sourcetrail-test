#include "DefinitionKind.h"

#include <iterator>

using namespace std;

namespace
{

const DefinitionKind DEFINITION_KINDS[] = {
	DefinitionKind::NONE,
	DefinitionKind::IMPLICIT,
	DefinitionKind::EXPLICIT
};

}
template<>
DefinitionKind intToEnum(int value)
{
	return findEnum(value, begin(DEFINITION_KINDS), end(DEFINITION_KINDS), DefinitionKind::NONE);
}
