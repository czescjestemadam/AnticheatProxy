#include "use_item.hh"

#include "network/handler/play_handler.hh"
#include "network/protocol/protocol_version.hh"

void acp::packet::play::c2s::UseItem::read(const ProtocolVersion* version)
{
	hand = buf.readVarint();

	if (*version >= ProtocolVersion::v1_19)
		sequence = buf.readVarint();

	if (*version >= ProtocolVersion::v1_21)
	{
		yaw = buf.readFloat();
		pitch = buf.readFloat();
	}
}

void acp::packet::play::c2s::UseItem::write(const ProtocolVersion* version)
{
	buf.writeVarint(hand);

	if (*version >= ProtocolVersion::v1_19)
		buf.writeVarint(sequence.value());

	if (*version >= ProtocolVersion::v1_21)
	{
		buf.writeFloat(yaw.value());
		buf.writeFloat(pitch.value());
	}
}

acp::HandleResult acp::packet::play::c2s::UseItem::apply(std::unique_ptr<INetworkHandler>& handler)
{
	if (auto* playHandler = dynamic_cast<PlayHandler*>(handler.get()))
		return playHandler->handle(this);

	return HandleResult::FORWARD;
}

int acp::packet::play::c2s::UseItem::getId(const ProtocolVersion* version) const
{
	if (*version >= ProtocolVersion::v1_20_5)
		return 0x39;
	if (*version >= ProtocolVersion::v1_20_3)
		return 0x36;
	if (*version >= ProtocolVersion::v1_20_2)
		return 0x35;
	if (*version >= ProtocolVersion::v1_19_1)
		return 0x32;
	if (*version >= ProtocolVersion::v1_19)
		return 0x31;

	return 0x2F;
}

int acp::packet::play::c2s::UseItem::getHand() const
{
	return hand;
}

void acp::packet::play::c2s::UseItem::setHand(const int hand)
{
	this->hand = hand;
}

std::optional<int> acp::packet::play::c2s::UseItem::getSequence() const
{
	return sequence;
}

void acp::packet::play::c2s::UseItem::setSequence(const std::optional<int>& sequence)
{
	this->sequence = sequence;
}

std::optional<float> acp::packet::play::c2s::UseItem::getYaw() const
{
	return yaw;
}

void acp::packet::play::c2s::UseItem::setYaw(const std::optional<float>& yaw)
{
	this->yaw = yaw;
}

std::optional<float> acp::packet::play::c2s::UseItem::getPitch() const
{
	return pitch;
}

void acp::packet::play::c2s::UseItem::setPitch(const std::optional<float>& pitch)
{
	this->pitch = pitch;
}

std::string acp::packet::play::c2s::UseItem::toString() const
{
	return std::format("UseItem[hand={}, seq={}, rot={} {}]", hand, sequence.value_or(-1), yaw.value_or(-1), pitch.value_or(-1));
}
