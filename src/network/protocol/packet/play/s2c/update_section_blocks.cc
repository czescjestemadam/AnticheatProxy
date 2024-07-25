#include "update_section_blocks.hh"

#include "network/handler/play_handler.hh"
#include "network/protocol/protocol_version.hh"

void acp::packet::play::s2c::UpdateSectionBlocks::read(const ProtocolVersion* version)
{
	chunkSectionPosition = buf.readPosition(42, 44, 22);

	if (*version <= ProtocolVersion::v1_19_4)
		supressLightUpdates = buf.readByte();

	const int len = buf.readVarint();
	for (int i = 0; i < len; ++i)
	{
		const long l = buf.readVarlong();
		blocks.emplace_back(
			Vec3i{ static_cast<int>(l >> 8 & 0xf), static_cast<int>(l & 0xf), static_cast<int>(l >> 4 & 0xf) },
			l >> 12
		);
	}
}

void acp::packet::play::s2c::UpdateSectionBlocks::write(const ProtocolVersion* version)
{
	buf.writePosition(chunkSectionPosition, 0x3fffff, 0xfffff, 42, 20);

	if (*version <= ProtocolVersion::v1_19_4)
		buf.writeByte(supressLightUpdates.value());

	buf.writeVarint(static_cast<int>(blocks.size()));
	for (auto& [pos, id] : blocks)
		buf.writeVarlong(id << 12 | (pos.x << 8 | pos.z << 4 | pos.y));
}

acp::HandleResult acp::packet::play::s2c::UpdateSectionBlocks::apply(std::unique_ptr<INetworkHandler>& handler)
{
	if (auto* playHandler = dynamic_cast<PlayHandler*>(handler.get()))
		return playHandler->handle(this);

	return HandleResult::FORWARD;
}

int acp::packet::play::s2c::UpdateSectionBlocks::getId(const ProtocolVersion* version) const
{
	if (*version >= ProtocolVersion::v1_20_5)
		return 0x49;
	if (*version >= ProtocolVersion::v1_20_3)
		return 0x47;
	if (*version >= ProtocolVersion::v1_20_2)
		return 0x45;
	if (*version >= ProtocolVersion::v1_19_4)
		return 0x43;
	if (*version >= ProtocolVersion::v1_19_3)
		return 0x3F;
	if (*version >= ProtocolVersion::v1_19_1)
		return 0x40;
	if (*version >= ProtocolVersion::v1_19)
		return 0x3D;
	if (*version >= ProtocolVersion::v1_17)
		return 0x3F;

	return 0x3B;
}

acp::Vec3i& acp::packet::play::s2c::UpdateSectionBlocks::getChunkSectionPosition()
{
	return chunkSectionPosition;
}

const acp::Vec3i& acp::packet::play::s2c::UpdateSectionBlocks::getChunkSectionPosition() const
{
	return chunkSectionPosition;
}

void acp::packet::play::s2c::UpdateSectionBlocks::setChunkSectionPosition(const Vec3i& chunk_section_position)
{
	chunkSectionPosition = chunk_section_position;
}

const std::optional<bool>& acp::packet::play::s2c::UpdateSectionBlocks::getSupressLightUpdates() const
{
	return supressLightUpdates;
}

void acp::packet::play::s2c::UpdateSectionBlocks::setSupressLightUpdates(const std::optional<bool>& supress_light_updates)
{
	supressLightUpdates = supress_light_updates;
}

std::vector<std::pair<acp::Vec3i, int>>& acp::packet::play::s2c::UpdateSectionBlocks::getBlocks()
{
	return blocks;
}

const std::vector<std::pair<acp::Vec3i, int>>& acp::packet::play::s2c::UpdateSectionBlocks::getBlocks() const
{
	return blocks;
}

void acp::packet::play::s2c::UpdateSectionBlocks::setBlocks(const std::vector<std::pair<Vec3i, int>>& blocks)
{
	this->blocks = blocks;
}

std::string acp::packet::play::s2c::UpdateSectionBlocks::toString() const
{
	return std::format("UpdateSectionBlocks[pos={} {} {}, noLight={}, blocks={}]",
					   chunkSectionPosition.x, chunkSectionPosition.y, chunkSectionPosition.z,
					   supressLightUpdates.value_or(false),
					   blocks.size()
	);
}
