#include "AccessKind.h"

namespace
{

const AccessKind ACCESS_KINDS[] = {
	AccessKind::NONE,
	AccessKind::PUBLIC,
	AccessKind::PROTECTED,
	AccessKind::PRIVATE,
	AccessKind::DEFAULT,
	AccessKind::TEMPLATE_PARAMETER,
	AccessKind::TYPE_PARAMETER
};

}

template <>
AccessKind intToEnum(int value)
{
	return lookupEnum(value, ACCESS_KINDS, AccessKind::NONE);
}

std::wstring accessKindToString(AccessKind t)
{
	switch (t)
	{
	case AccessKind::NONE:
		return L"";
	case AccessKind::PUBLIC:
		return L"public";
	case AccessKind::PROTECTED:
		return L"protected";
	case AccessKind::PRIVATE:
		return L"private";
	case AccessKind::DEFAULT:
		return L"default";
	case AccessKind::TEMPLATE_PARAMETER:
		return L"template parameter";
	case AccessKind::TYPE_PARAMETER:
		return L"type parameter";
	}
	return L"";
}
