#include "player_abilities.hh"

#include "network/handler/play_handler.hh"
#include "network/protocol/protocol_version.hh"

void acp::packet::play::c2s::PlayerAbilities::read(const ProtocolVersion* version)
{
	flags = buf.readByte();
}

void acp::packet::play::c2s::PlayerAbilities::write(const ProtocolVersion* version)
{
	buf.writeByte(flags);
}

bool acp::packet::play::c2s::PlayerAbilities::apply(std::unique_ptr<INetworkHandler>& handler)
{
	if (auto* playHandler = dynamic_cast<PlayHandler*>(handler.get()))
		return playHandler->handle(this);

	return false;
}

int acp::packet::play::c2s::PlayerAbilities::getId(const ProtocolVersion* version) const
{
	if (*version >= ProtocolVersion::v1_20_5)
		return 0x23;
	if (*version >= ProtocolVersion::v1_20_3)
		return 0x20;
	if (*version >= ProtocolVersion::v1_20_2)
		return 0x1F;
	if (*version >= ProtocolVersion::v1_19_4)
		return 0x1C;
	if (*version >= ProtocolVersion::v1_19_3)
		return 0x1B;
	if (*version >= ProtocolVersion::v1_19_1)
		return 0x1C;
	if (*version >= ProtocolVersion::v1_19)
		return 0x1B;
	if (*version >= ProtocolVersion::v1_17)
		return 0x19;

	return 0x1A;
}

byte_t acp::packet::play::c2s::PlayerAbilities::getFlags() const
{
	return flags;
}

void acp::packet::play::c2s::PlayerAbilities::setFlags(const byte_t flags)
{
	this->flags = flags;
}

std::string acp::packet::play::c2s::PlayerAbilities::toString() const
{
	return std::format("PlayerAbilities[{:x}]", flags);
}
