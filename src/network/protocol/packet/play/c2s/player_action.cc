#include "player_action.hh"

#include "network/handler/play_handler.hh"
#include "network/protocol/protocol_version.hh"

void acp::packet::play::c2s::PlayerAction::read(const ProtocolVersion* version)
{
	status = buf.readVarint();
	blockPosition = buf.readPosition();
	face = static_cast<BoxFace>(buf.readByte());

	if (*version >= ProtocolVersion::v1_19)
		sequence = buf.readVarint();
}

void acp::packet::play::c2s::PlayerAction::write(const ProtocolVersion* version)
{
	buf.writeVarint(status);
	buf.writePosition(blockPosition);
	buf.writeByte(static_cast<byte_t>(face));

	if (*version >= ProtocolVersion::v1_19)
		buf.writeVarint(sequence.value());
}

acp::HandleResult acp::packet::play::c2s::PlayerAction::apply(std::unique_ptr<INetworkHandler>& handler)
{
	if (auto* playHandler = dynamic_cast<PlayHandler*>(handler.get()))
		return playHandler->handle(this);

	return HandleResult::FORWARD;
}

int acp::packet::play::c2s::PlayerAction::getId(const ProtocolVersion* version) const
{
	if (*version >= ProtocolVersion::v1_20_5)
		return 0x24;
	if (*version >= ProtocolVersion::v1_20_3)
		return 0x21;
	if (*version >= ProtocolVersion::v1_20_2)
		return 0x20;
	if (*version >= ProtocolVersion::v1_19_1)
		return 0x1D;
	if (*version >= ProtocolVersion::v1_19)
		return 0x1C;
	if (*version >= ProtocolVersion::v1_17)
		return 0x1A;

	return 0x1B;
}

int acp::packet::play::c2s::PlayerAction::getStatus() const
{
	return status;
}

void acp::packet::play::c2s::PlayerAction::setStatus(const int status)
{
	this->status = status;
}

acp::Vec3i acp::packet::play::c2s::PlayerAction::getBlockPosition() const
{
	return blockPosition;
}

void acp::packet::play::c2s::PlayerAction::setBlockPosition(const Vec3i& block_position)
{
	blockPosition = block_position;
}

acp::BoxFace acp::packet::play::c2s::PlayerAction::getFace() const
{
	return face;
}

void acp::packet::play::c2s::PlayerAction::setFace(const BoxFace face)
{
	this->face = face;
}

const std::optional<int>& acp::packet::play::c2s::PlayerAction::getSequence() const
{
	return sequence;
}

void acp::packet::play::c2s::PlayerAction::setSequence(const std::optional<int>& sequence)
{
	this->sequence = sequence;
}

std::string acp::packet::play::c2s::PlayerAction::toString() const
{
	return std::format("PlayerAction[status={}, pos={} {} {}, face={}, seq={}]",
					   status,
					   blockPosition.x, blockPosition.y, blockPosition.z,
					   EnumNames<BoxFace>::get(face),
					   sequence.value_or(-1)
	);
}
