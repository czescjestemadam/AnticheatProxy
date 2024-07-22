#include "block_update.hh"

#include "network/handler/play_handler.hh"
#include "network/protocol/protocol_version.hh"

void acp::packet::play::s2c::BlockUpdate::read(const ProtocolVersion* version)
{
	blockPosition = buf.readPosition();
	blockId = buf.readVarint();
}

void acp::packet::play::s2c::BlockUpdate::write(const ProtocolVersion* version)
{
	buf.writePosition(blockPosition);
	buf.writeVarint(blockId);
}

bool acp::packet::play::s2c::BlockUpdate::apply(std::unique_ptr<INetworkHandler>& handler)
{
	if (auto* playHandler = dynamic_cast<PlayHandler*>(handler.get()))
		return playHandler->handle(this);

	return false;
}

int acp::packet::play::s2c::BlockUpdate::getId(const ProtocolVersion* version) const
{
	if (*version >= ProtocolVersion::v1_20_2)
		return 0x09;
	if (*version >= ProtocolVersion::v1_19_4)
		return 0x0A;
	if (*version >= ProtocolVersion::v1_19)
		return 0x09;
	if (*version >= ProtocolVersion::v1_17)
		return 0x0C;

	return 0x0B;
}

acp::Vec3i acp::packet::play::s2c::BlockUpdate::getBlockPosition() const
{
	return blockPosition;
}

void acp::packet::play::s2c::BlockUpdate::setBlockPosition(const Vec3i& block_position)
{
	blockPosition = block_position;
}

int acp::packet::play::s2c::BlockUpdate::getBlockId() const
{
	return blockId;
}

void acp::packet::play::s2c::BlockUpdate::setBlockId(const int block_id)
{
	blockId = block_id;
}

std::string acp::packet::play::s2c::BlockUpdate::toString() const
{
	return std::format("BlockUpdate[pos={} {} {}, id={}]", blockPosition.x, blockPosition.y, blockPosition.z, blockId);
}
