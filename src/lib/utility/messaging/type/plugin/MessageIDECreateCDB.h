#ifndef MESSAGE_IDE_CREATE_CDB_H
#define MESSAGE_IDE_CREATE_CDB_H

#include "Message.h"

class MessageIDECreateCDB: public Message<MessageIDECreateCDB>
{
public:
	MessageIDECreateCDB() = default;

	static const std::string getStaticType()
	{
		return "MessageIDECreateCDB";
	}

	void print(std::wostream& os) const override
	{
		os << L"Create CDB from current solution";
	}
};

#endif	  // MESSAGE_IDE_CREATE_CDB_H