#include "string_properties.hh"

acp::command::StringProperties::StringProperties(Type type) : type(type)
{
}

acp::ByteBuf acp::command::StringProperties::serialize()
{
	ByteBuf buf;
	buf.writeVarint(static_cast<int>(type));
	return buf;
}

void acp::command::StringProperties::deserialize(ByteBuf& v)
{
	type = static_cast<Type>(v.readVarint());
}


std::string acp::EnumNames<acp::command::StringProperties::Type>::get(command::StringProperties::Type val)
{
	switch (val)
	{
		case command::StringProperties::Type::SINGLE_WORD: return "SINGLE_WORD";
		case command::StringProperties::Type::QUOTABLE_PHRASE: return "QUOTABLE_PHRASE";
		case command::StringProperties::Type::GREEDY_PHRASE: return "GREEDY_PHRASE";
		default: return "unknown";
	}
}
