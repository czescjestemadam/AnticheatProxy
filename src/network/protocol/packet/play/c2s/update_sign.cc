#include "update_sign.hh"

#include "network/handler/play_handler.hh"
#include "network/protocol/protocol_version.hh"

void acp::packet::play::c2s::UpdateSign::read(const ProtocolVersion* version)
{
	blockPosition = buf.readPosition();

	if (*version >= ProtocolVersion::v1_20)
		front = buf.readByte();

	for (std::string& line : lines)
		line = buf.readStr();
}

void acp::packet::play::c2s::UpdateSign::write(const ProtocolVersion* version)
{
	buf.writePosition(blockPosition);

	if (*version >= ProtocolVersion::v1_20)
		buf.writeByte(front.value());

	for (std::string& line : lines)
		buf.writeStr(line);
}

acp::HandleResult acp::packet::play::c2s::UpdateSign::apply(std::unique_ptr<INetworkHandler>& handler)
{
	if (auto* playHandler = dynamic_cast<PlayHandler*>(handler.get()))
		return playHandler->handle(this);
	return HandleResult::FORWARD;
}

int acp::packet::play::c2s::UpdateSign::getId(const ProtocolVersion* version) const
{
	if (*version >= ProtocolVersion::v1_20_5)
		return 0x35;
	if (*version >= ProtocolVersion::v1_20_3)
		return 0x32;
	if (*version >= ProtocolVersion::v1_20_2)
		return 0x31;
	if (*version >= ProtocolVersion::v1_19_1)
		return 0x2E;
	if (*version >= ProtocolVersion::v1_19)
		return 0x2D;

	return 0x2B;
}

acp::Vec3i& acp::packet::play::c2s::UpdateSign::getBlockPosition()
{
	return blockPosition;
}

const acp::Vec3i& acp::packet::play::c2s::UpdateSign::getBlockPosition() const
{
	return blockPosition;
}

void acp::packet::play::c2s::UpdateSign::setBlockPosition(const Vec3i& block_position)
{
	blockPosition = block_position;
}

std::optional<bool>& acp::packet::play::c2s::UpdateSign::getFront()
{
	return front;
}

const std::optional<bool>& acp::packet::play::c2s::UpdateSign::getFront() const
{
	return front;
}

void acp::packet::play::c2s::UpdateSign::setFront(const std::optional<bool>& front)
{
	this->front = front;
}

std::array<std::string, 4>& acp::packet::play::c2s::UpdateSign::getLines()
{
	return lines;
}

const std::array<std::string, 4>& acp::packet::play::c2s::UpdateSign::getLines() const
{
	return lines;
}

void acp::packet::play::c2s::UpdateSign::setLines(const std::array<std::string, 4>& lines)
{
	this->lines = lines;
}

std::string acp::packet::play::c2s::UpdateSign::toString() const
{
	return std::format(R"(UpdateSign[pos={} {} {}, front={}, lines="{}" "{}" "{}" "{}"])",
					   blockPosition.x, blockPosition.y, blockPosition.z,
					   front.value_or(true),
					   lines[0], lines[1], lines[2], lines[3]
	);
}
