#include "identifier_properties.hh"

acp::command::IdentifierProperties::IdentifierProperties(const Identifier& id) : id(id)
{
}

acp::ByteBuf acp::command::IdentifierProperties::serialize()
{
	ByteBuf buf;
	buf.writeIdentifier(id);
	return buf;
}

void acp::command::IdentifierProperties::deserialize(ByteBuf& v)
{
	id = v.readIdentifier();
}
