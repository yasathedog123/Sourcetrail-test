#include "Edge.h"

#include <sstream>

#include "Node.h"
#include "TokenComponentBundledEdges.h"
#include "logging.h"
#include "utilityString.h"

template <>
Edge::EdgeType intToEnum(int value)
{
	switch (value)
	{
		case Edge::EDGE_MEMBER:
			return Edge::EDGE_MEMBER;
		case Edge::EDGE_TYPE_USAGE:
			return Edge::EDGE_TYPE_USAGE;
		case Edge::EDGE_USAGE:
			return Edge::EDGE_USAGE;
		case Edge::EDGE_CALL:
			return Edge::EDGE_CALL;
		case Edge::EDGE_INHERITANCE:
			return Edge::EDGE_INHERITANCE;
		case Edge::EDGE_OVERRIDE:
			return Edge::EDGE_OVERRIDE;
		case Edge::EDGE_TYPE_ARGUMENT:
			return Edge::EDGE_TYPE_ARGUMENT;
		case Edge::EDGE_TEMPLATE_SPECIALIZATION:
			return Edge::EDGE_TEMPLATE_SPECIALIZATION;
		case Edge::EDGE_INCLUDE:
			return Edge::EDGE_INCLUDE;
		case Edge::EDGE_IMPORT:
			return Edge::EDGE_IMPORT;
		case Edge::EDGE_BUNDLED_EDGES:
			return Edge::EDGE_BUNDLED_EDGES;
		case Edge::EDGE_MACRO_USAGE:
			return Edge::EDGE_MACRO_USAGE;
		case Edge::EDGE_ANNOTATION_USAGE:
			return Edge::EDGE_ANNOTATION_USAGE;
	}
	return Edge::EDGE_UNDEFINED;
}

Edge::Edge(Id id, EdgeType type, Node* from, Node* to)
	: Token(id), m_type(type), m_from(from), m_to(to)
{
	m_from->addEdge(this);
	m_to->addEdge(this);
}

Edge::Edge(const Edge& other, Node* from, Node* to)
	: Token(other), m_type(other.m_type), m_from(from), m_to(to)
{
	m_from->addEdge(this);
	m_to->addEdge(this);

	if (m_from == other.m_from || m_to == other.m_to || m_from->getId() != other.m_from->getId() ||
		m_to->getId() != other.m_to->getId())
	{
		LOG_ERROR("Nodes are not plain copies.");
	}
}

Edge::~Edge()
{
	m_from->removeEdge(this);
	m_to->removeEdge(this);
}

Edge::EdgeType Edge::getType() const
{
	return m_type;
}

bool Edge::isType(TypeMask mask) const
{
	return (m_type & mask) > 0;
}

Node* Edge::getFrom() const
{
	return m_from;
}

Node* Edge::getTo() const
{
	return m_to;
}

std::wstring Edge::getName() const
{
	return getReadableTypeString() + L":" + getFrom()->getFullName() + L"->" + getTo()->getFullName();
}

bool Edge::isNode() const
{
	return false;
}

bool Edge::isEdge() const
{
	return true;
}

std::wstring Edge::getUnderscoredTypeString(EdgeType type)
{
	return utility::replace(utility::replace(getReadableTypeString(type), L"-", L"_"), L" ", L"_");
}

std::wstring Edge::getReadableTypeString(EdgeType type)
{
	switch (type)
	{
	case EDGE_UNDEFINED:
		return L"undefined";
	case EDGE_MEMBER:
		return L"child";
	case EDGE_TYPE_USAGE:
		return L"type use";
	case EDGE_USAGE:
		return L"use";
	case EDGE_CALL:
		return L"call";
	case EDGE_INHERITANCE:
		return L"inheritance";
	case EDGE_OVERRIDE:
		return L"override";
	case EDGE_TYPE_ARGUMENT:
		return L"type argument";
	case EDGE_TEMPLATE_SPECIALIZATION:
		return L"template specialization";
	case EDGE_INCLUDE:
		return L"include";
	case EDGE_IMPORT:
		return L"import";
	case EDGE_BUNDLED_EDGES:
		return L"bundled edges";
	case EDGE_MACRO_USAGE:
		return L"macro use";
	case EDGE_ANNOTATION_USAGE:
		return L"annotation use";
	}

	return L"";
}

Edge::EdgeType Edge::getTypeForReadableTypeString(const std::wstring& str)
{
	for (TypeMask mask = 1; mask <= EDGE_TYPE_MAX_VALUE; mask *= 2)
	{
		EdgeType type = intToEnum<EdgeType>(mask);
		if (getReadableTypeString(type) == str)
		{
			return type;
		}
	}

	return EDGE_UNDEFINED;
}

std::wstring Edge::getReadableTypeString() const
{
	return getReadableTypeString(m_type);
}

std::wstring Edge::getAsString() const
{
	std::wstringstream str;
	str << L"[" << getId() << L"] " << getReadableTypeString();
	str << L": \"" << m_from->getName() << L"\" -> \"" + m_to->getName() << L"\"";

	TokenComponentBundledEdges* bundledEdges = getComponent<TokenComponentBundledEdges>();
	if (bundledEdges)
	{
		str << L" " << bundledEdges->getBundledEdgesCount();
	}

	return str.str();
}

std::wostream& operator<<(std::wostream& ostream, const Edge& edge)
{
	ostream << edge.getAsString();
	return ostream;
}
