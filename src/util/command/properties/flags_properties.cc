#include "flags_properties.hh"

acp::command::FlagsProperties::FlagsProperties(byte_t flags) : flags(flags)
{
}

acp::ByteBuf acp::command::FlagsProperties::serialize()
{
	ByteBuf buf;
	buf.writeByte(flags);
	return buf;
}

void acp::command::FlagsProperties::deserialize(ByteBuf& v)
{
	flags = v.readByte();
}
