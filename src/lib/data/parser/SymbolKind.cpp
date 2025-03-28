#include "SymbolKind.h"

#include <iterator>

using namespace std;

namespace
{

const SymbolKind SYMBOL_KINDS[] = {
	SymbolKind::UNDEFINED,
	SymbolKind::ANNOTATION,
	SymbolKind::BUILTIN_TYPE,
	SymbolKind::CLASS,
	SymbolKind::ENUM,
	SymbolKind::ENUM_CONSTANT,
	SymbolKind::FIELD,
	SymbolKind::FUNCTION,
	SymbolKind::GLOBAL_VARIABLE,
	SymbolKind::INTERFACE,
	SymbolKind::MACRO,
	SymbolKind::METHOD,
	SymbolKind::MODULE,
	SymbolKind::NAMESPACE,
	SymbolKind::PACKAGE,
	SymbolKind::STRUCT,
	SymbolKind::TYPEDEF,
	SymbolKind::TYPE_PARAMETER,
	SymbolKind::UNION,
	SymbolKind::RECORD
};

}

template <>
SymbolKind intToEnum(int value)
{
	return findEnum(value, begin(SYMBOL_KINDS), end(SYMBOL_KINDS), SymbolKind::UNDEFINED);
}
