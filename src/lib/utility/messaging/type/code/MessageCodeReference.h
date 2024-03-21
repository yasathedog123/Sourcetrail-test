#ifndef MESSAGE_CODE_REFERENCE_H
#define MESSAGE_CODE_REFERENCE_H

#include "Message.h"
#include "TabId.h"

class MessageCodeReference: public Message<MessageCodeReference>
{
public:
	enum ReferenceType
	{
		REFERENCE_PREVIOUS,
		REFERENCE_NEXT
	};

	MessageCodeReference(ReferenceType type, bool localReference)
		: type(type), localReference(localReference)
	{
		setSchedulerId(TabId::currentTab());
	}

	static const std::string getStaticType()
	{
		return "MessageCodeReference";
	}

	void print(std::wostream& os) const override
	{
		if (type == REFERENCE_PREVIOUS)
		{
			os << L"previous";
		}
		else
		{
			os << L"next";
		}

		if (localReference)
		{
			os << L" local";
		}
	}

	const ReferenceType type;
	bool localReference;
};

#endif	  // MESSAGE_CODE_REFERENCE_H
