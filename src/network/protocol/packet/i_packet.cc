#include "i_packet.hh"

acp::packet::IPacket::IPacket(const ByteBuf& buf) : buf(buf)
{
}

acp::ByteBuf& acp::packet::IPacket::getBuf()
{
	return buf;
}
