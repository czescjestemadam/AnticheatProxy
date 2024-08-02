#include "time_properties.hh"

acp::command::TimeProperties::TimeProperties(int min) : min(min)
{
}

acp::ByteBuf acp::command::TimeProperties::serialize()
{
	ByteBuf buf;
	buf.writeInt(min);
	return buf;
}

void acp::command::TimeProperties::deserialize(ByteBuf& v)
{
	min = v.readInt();
}
