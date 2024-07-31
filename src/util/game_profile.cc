#include "game_profile.hh"

#include "network/protocol/protocol_version.hh"

acp::ByteBuf acp::GameProfile::Property::serialize()
{
	ByteBuf buf;
	buf.writeStr(name);
	buf.writeStr(value);

	const bool signaturePresent = !signature.empty();
	buf.writeByte(signaturePresent);
	if (signaturePresent)
		buf.writeStr(signature);

	return buf;
}

void acp::GameProfile::Property::deserialize(ByteBuf& v)
{
	name = v.readStr();
	value = v.readStr();

	if (v.readByte())
		signature = v.readStr();
}


acp::ByteBuf acp::GameProfile::serialize()
{
	ByteBuf buf;
	buf.writeUuid(uuid);
	buf.writeStr(username);

	buf.writeVarint(static_cast<int>(properties.size()));
	for (Property& property : properties)
		buf.writeBuf(property.serialize());

	return buf;
}

void acp::GameProfile::deserialize(ByteBuf& v)
{
	uuid = v.readUuid();
	username = v.readStr();

	const int len = v.readVarint();
	for (int i = 0; i < len; ++i)
	{
		Property prop;
		prop.deserialize(v);
		properties.push_back(std::move(prop));
	}
}
