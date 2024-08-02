#include "empty_properties.hh"

acp::ByteBuf acp::command::EmptyProperties::serialize()
{
	return {};
}

void acp::command::EmptyProperties::deserialize(ByteBuf& v)
{
}
