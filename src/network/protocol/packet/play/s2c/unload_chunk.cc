#include "unload_chunk.hh"

#include "network/handler/play_handler.hh"
#include "network/protocol/protocol_version.hh"

void acp::packet::play::s2c::UnloadChunk::read(const ProtocolVersion* version)
{
	z = buf.readInt();
	x = buf.readInt();
}

void acp::packet::play::s2c::UnloadChunk::write(const ProtocolVersion* version)
{
	buf.writeInt(z);
	buf.writeInt(x);
}

acp::HandleResult acp::packet::play::s2c::UnloadChunk::apply(std::unique_ptr<INetworkHandler>& handler)
{
	if (auto* playHandler = dynamic_cast<PlayHandler*>(handler.get()))
		return playHandler->handle(this);

	return HandleResult::FORWARD;
}

int acp::packet::play::s2c::UnloadChunk::getId(const ProtocolVersion* version) const
{
	if (*version >= ProtocolVersion::v1_20_5)
		return 0x21;
	if (*version >= ProtocolVersion::v1_20_2)
		return 0x1F;
	if (*version >= ProtocolVersion::v1_19_4)
		return 0x1E;
	if (*version >= ProtocolVersion::v1_19_3)
		return 0x1B;
	if (*version >= ProtocolVersion::v1_19_1)
		return 0x1C;
	if (*version >= ProtocolVersion::v1_19)
		return 0x1A;
	if (*version >= ProtocolVersion::v1_17)
		return 0x1D;

	return 0x1C;
}

int acp::packet::play::s2c::UnloadChunk::getZ() const
{
	return z;
}

void acp::packet::play::s2c::UnloadChunk::setZ(const int z)
{
	this->z = z;
}

int acp::packet::play::s2c::UnloadChunk::getX() const
{
	return x;
}

void acp::packet::play::s2c::UnloadChunk::setX(const int x)
{
	this->x = x;
}

std::string acp::packet::play::s2c::UnloadChunk::toString() const
{
	return std::format("UnloadChunk[z={}, x={}]", z, x);
}
