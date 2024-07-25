#include "swing_arm.hh"

#include "network/handler/play_handler.hh"
#include "network/protocol/protocol_version.hh"

void acp::packet::play::c2s::SwingArm::read(const ProtocolVersion* version)
{
	hand = buf.readVarint();
}

void acp::packet::play::c2s::SwingArm::write(const ProtocolVersion* version)
{
	buf.writeVarint(hand);
}

acp::HandleResult acp::packet::play::c2s::SwingArm::apply(std::unique_ptr<INetworkHandler>& handler)
{
	if (auto* playHandler = dynamic_cast<PlayHandler*>(handler.get()))
		return playHandler->handle(this);

	return HandleResult::FORWARD;
}

int acp::packet::play::c2s::SwingArm::getId(const ProtocolVersion* version) const
{
	if (*version >= ProtocolVersion::v1_20_5)
		return 0x36;
	if (*version >= ProtocolVersion::v1_20_3)
		return 0x33;
	if (*version >= ProtocolVersion::v1_20_2)
		return 0x32;
	if (*version >= ProtocolVersion::v1_19_1)
		return 0x2F;
	if (*version >= ProtocolVersion::v1_19)
		return 0x2E;

	return 0x2C;
}

int& acp::packet::play::c2s::SwingArm::getHand()
{
	return hand;
}

void acp::packet::play::c2s::SwingArm::setHand(int hand)
{
	this->hand = hand;
}

std::string acp::packet::play::c2s::SwingArm::toString() const
{
	return std::format("SwingArm[{}]", hand);
}
