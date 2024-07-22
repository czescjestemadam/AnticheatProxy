#include "use_item_on.hh"

#include "network/handler/play_handler.hh"
#include "network/protocol/protocol_version.hh"

void acp::packet::play::c2s::UseItemOn::read(const ProtocolVersion* version)
{
	hand = buf.readVarint();
	blockPosition = buf.readPosition();
	face = buf.readVarint();
	cursorPosition = buf.readVec3f();
	insideBlock = buf.readByte();

	if (*version >= ProtocolVersion::v1_19)
		sequence = buf.readVarint();
}

void acp::packet::play::c2s::UseItemOn::write(const ProtocolVersion* version)
{
	buf.writeVarint(hand);
	buf.writePosition(blockPosition);
	buf.writeVarint(face);
	buf.writeVec3f(cursorPosition);
	buf.writeByte(insideBlock);

	if (*version >= ProtocolVersion::v1_19)
		sequence = buf.readVarint();
}

bool acp::packet::play::c2s::UseItemOn::apply(std::unique_ptr<INetworkHandler>& handler)
{
	if (auto* playHandler = dynamic_cast<PlayHandler*>(handler.get()))
		return playHandler->handle(this);

	return false;
}

int acp::packet::play::c2s::UseItemOn::getId(const ProtocolVersion* version) const
{
	if (*version >= ProtocolVersion::v1_20_5)
		return 0x38;
	if (*version >= ProtocolVersion::v1_20_3)
		return 0x35;
	if (*version >= ProtocolVersion::v1_20_2)
		return 0x34;
	if (*version >= ProtocolVersion::v1_19_1)
		return 0x31;
	if (*version >= ProtocolVersion::v1_19)
		return 0x30;

	return 0x2E;
}

int acp::packet::play::c2s::UseItemOn::getHand() const
{
	return hand;
}

void acp::packet::play::c2s::UseItemOn::setHand(const int hand)
{
	this->hand = hand;
}

acp::Vec3i acp::packet::play::c2s::UseItemOn::getBlockPosition() const
{
	return blockPosition;
}

void acp::packet::play::c2s::UseItemOn::setBlockPosition(const Vec3i& block_position)
{
	blockPosition = block_position;
}

int acp::packet::play::c2s::UseItemOn::getFace() const
{
	return face;
}

void acp::packet::play::c2s::UseItemOn::setFace(const int face)
{
	this->face = face;
}

acp::Vec3f acp::packet::play::c2s::UseItemOn::getCursorPosition() const
{
	return cursorPosition;
}

void acp::packet::play::c2s::UseItemOn::setCursorPosition(const Vec3f& cursor_position)
{
	cursorPosition = cursor_position;
}

bool acp::packet::play::c2s::UseItemOn::isInsideBlock() const
{
	return insideBlock;
}

void acp::packet::play::c2s::UseItemOn::setInsideBlock(const bool inside_block)
{
	insideBlock = inside_block;
}

std::optional<int> acp::packet::play::c2s::UseItemOn::getSequence() const
{
	return sequence;
}

void acp::packet::play::c2s::UseItemOn::setSequence(const std::optional<int>& sequence)
{
	this->sequence = sequence;
}

std::string acp::packet::play::c2s::UseItemOn::toString() const
{
	return std::format("UseItemOn[hand={}, pos={} {} {}, face={}, cursorPos={} {} {}, insideBlock={}, seq={}]",
					   hand,
					   blockPosition.x, blockPosition.y, blockPosition.z,
					   face,
					   cursorPosition.x, cursorPosition.y, cursorPosition.z,
					   insideBlock,
					   sequence.value_or(-1)
	);
}
