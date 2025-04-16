#ifndef MESSAGE_GRAPH_NODE_EXPAND_H
#define MESSAGE_GRAPH_NODE_EXPAND_H

#include "Message.h"
#include "TabIds.h"
#include "types.h"

class MessageGraphNodeExpand: public Message<MessageGraphNodeExpand>
{
public:
	MessageGraphNodeExpand(Id tokenId, bool expand, bool ignoreIfNotReplayed = false)
		: tokenId(tokenId), expand(expand), ignoreIfNotReplayed(ignoreIfNotReplayed)
	{
		setSchedulerId(TabIds::currentTab());
	}

	static const std::string getStaticType()
	{
		return "MessageGraphNodeExpand";
	}

	void print(std::wostream& os) const override
	{
		os << tokenId << L" ";
		if (expand)
		{
			os << L"expand";
		}
		else
		{
			os << L"collapse";
		}
	}

	const Id tokenId;
	const bool expand;
	const bool ignoreIfNotReplayed;
};

#endif	  // MESSAGE_GRAPH_NODE_EXPAND_H
