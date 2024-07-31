#include "forwarding_info.hh"

acp::velocity::ForwardingInfo::ForwardingInfo(ForwardingVersion version, const std::string& address, const GameProfile& profile)
	: version(version), address(address), profile(profile)
{
}

acp::ByteBuf acp::velocity::ForwardingInfo::serialize()
{
	ByteBuf buf;
	buf.writeBuf(signature);
	buf.writeVarint(static_cast<int>(version));
	buf.writeStr(address);
	buf.writeGameProfile(profile);

	return buf;
}

void acp::velocity::ForwardingInfo::deserialize(ByteBuf& v)
{
	signature = v.readBuf(32);
	version = static_cast<ForwardingVersion>(v.readVarint());
	address = v.readStr();
	profile = v.readGameProfile();
}
