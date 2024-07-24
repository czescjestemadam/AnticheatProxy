#include "open_sign_editor.hh"

#include "network/handler/play_handler.hh"
#include "network/protocol/protocol_version.hh"

void acp::packet::play::s2c::OpenSignEditor::read(const ProtocolVersion* version)
{
	blockPosition = buf.readPosition();

	if (*version >= ProtocolVersion::v1_20)
		front = buf.readByte();
}

void acp::packet::play::s2c::OpenSignEditor::write(const ProtocolVersion* version)
{
	buf.writePosition(blockPosition);

	if (*version >= ProtocolVersion::v1_20)
		buf.writeByte(front.value());
}

bool acp::packet::play::s2c::OpenSignEditor::apply(std::unique_ptr<INetworkHandler>& handler)
{
	if (auto* playHandler = dynamic_cast<PlayHandler*>(handler.get()))
		return playHandler->handle(this);

	return false;
}

int acp::packet::play::s2c::OpenSignEditor::getId(const ProtocolVersion* version) const
{
	if (*version >= ProtocolVersion::v1_20_5)
		return 0x34;
	if (*version >= ProtocolVersion::v1_20_2)
		return 0x32;
	if (*version >= ProtocolVersion::v1_19_4)
		return 0x31;
	if (*version >= ProtocolVersion::v1_19_3)
		return 0x2D;
	if (*version >= ProtocolVersion::v1_19_1)
		return 0x2E;
	if (*version >= ProtocolVersion::v1_19)
		return 0x2C;
	if (*version >= ProtocolVersion::v1_17)
		return 0x2F;

	return 0x2E;
}

acp::Vec3i& acp::packet::play::s2c::OpenSignEditor::getBlockPosition()
{
	return blockPosition;
}

const acp::Vec3i& acp::packet::play::s2c::OpenSignEditor::getBlockPosition() const
{
	return blockPosition;
}

void acp::packet::play::s2c::OpenSignEditor::setBlockPosition(const Vec3i& block_position)
{
	blockPosition = block_position;
}

std::optional<bool> acp::packet::play::s2c::OpenSignEditor::getFront() const
{
	return front;
}

void acp::packet::play::s2c::OpenSignEditor::setFront(const std::optional<bool>& front)
{
	this->front = front;
}

std::string acp::packet::play::s2c::OpenSignEditor::toString() const
{
	return std::format("OpenSignEditor[pos={} {} {}, front={}]",
					   blockPosition.x, blockPosition.y, blockPosition.z,
					   front.value_or(true)
	);
}
