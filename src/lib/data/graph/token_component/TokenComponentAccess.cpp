#include "TokenComponentAccess.h"

std::wstring TokenComponentAccess::getAccessString(AccessKind access)
{
	switch (access)
	{
	case AccessKind::NONE:
		break;
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


TokenComponentAccess::TokenComponentAccess(AccessKind access): m_access(access) {}

TokenComponentAccess::~TokenComponentAccess() = default;

std::shared_ptr<TokenComponent> TokenComponentAccess::copy() const
{
	return std::make_shared<TokenComponentAccess>(*this);
}

AccessKind TokenComponentAccess::getAccess() const
{
	return m_access;
}

std::wstring TokenComponentAccess::getAccessString() const
{
	return getAccessString(m_access);
}
