#include "player_input.hh"

#include "network/handler/play_handler.hh"
#include "network/protocol/protocol_version.hh"

void acp::packet::play::c2s::PlayerInput::read(const ProtocolVersion* version)
{
	sideways = buf.readFloat();
	forward = buf.readFloat();
	flags = buf.readByte();
}

void acp::packet::play::c2s::PlayerInput::write(const ProtocolVersion* version)
{
	buf.writeFloat(sideways);
	buf.writeFloat(forward);
	buf.writeByte(flags);
}

acp::HandleResult acp::packet::play::c2s::PlayerInput::apply(std::unique_ptr<INetworkHandler>& handler)
{
	if (auto* playHandler = dynamic_cast<PlayHandler*>(handler.get()))
		return playHandler->handle(this);

	return HandleResult::FORWARD;
}

int acp::packet::play::c2s::PlayerInput::getId(const ProtocolVersion* version) const
{
	if (*version >= ProtocolVersion::v1_20_5)
		return 0x26;
	if (*version >= ProtocolVersion::v1_20_3)
		return 0x23;
	if (*version >= ProtocolVersion::v1_20_2)
		return 0x22;
	if (*version >= ProtocolVersion::v1_19_4)
		return 0x1F;
	if (*version >= ProtocolVersion::v1_19_3)
		return 0x1E;
	if (*version >= ProtocolVersion::v1_19_1)
		return 0x1F;
	if (*version >= ProtocolVersion::v1_19)
		return 0x1E;
	if (*version >= ProtocolVersion::v1_17)
		return 0x1C;

	return 0x1D;
}

float acp::packet::play::c2s::PlayerInput::getSideways() const
{
	return sideways;
}

void acp::packet::play::c2s::PlayerInput::setSideways(const float sideways)
{
	this->sideways = sideways;
}

float acp::packet::play::c2s::PlayerInput::getForward() const
{
	return forward;
}

void acp::packet::play::c2s::PlayerInput::setForward(const float forward)
{
	this->forward = forward;
}

byte_t acp::packet::play::c2s::PlayerInput::getFlags() const
{
	return flags;
}

void acp::packet::play::c2s::PlayerInput::setFlags(const byte_t flags)
{
	this->flags = flags;
}

std::string acp::packet::play::c2s::PlayerInput::toString() const
{
	return std::format("PlayerInput[sideways={}, forward={}, fl={:02x}]", sideways, forward, flags);
}
