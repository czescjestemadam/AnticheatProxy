#include "player_abilities.hh"

#include "network/handler/play_handler.hh"
#include "network/protocol/protocol_version.hh"

void acp::packet::play::s2c::PlayerAbilities::read(const ProtocolVersion* version)
{
	flags = buf.readByte();
	flyingSpeed = buf.readFloat();
	fovModifier = buf.readFloat();
}

void acp::packet::play::s2c::PlayerAbilities::write(const ProtocolVersion* version)
{
	buf.writeByte(flags);
	buf.writeFloat(flyingSpeed);
	buf.writeFloat(fovModifier);
}

acp::HandleResult acp::packet::play::s2c::PlayerAbilities::apply(std::unique_ptr<INetworkHandler>& handler)
{
	if (auto* playHandler = dynamic_cast<PlayHandler*>(handler.get()))
		return playHandler->handle(this);

	return HandleResult::FORWARD;
}

int acp::packet::play::s2c::PlayerAbilities::getId(const ProtocolVersion* version) const
{
	if (*version >= ProtocolVersion::v1_20_5)
		return 0x38;
	if (*version >= ProtocolVersion::v1_20_2)
		return 0x36;
	if (*version >= ProtocolVersion::v1_19_4)
		return 0x34;
	if (*version >= ProtocolVersion::v1_19_3)
		return 0x30;
	if (*version >= ProtocolVersion::v1_19_1)
		return 0x31;
	if (*version >= ProtocolVersion::v1_19)
		return 0x2F;
	if (*version >= ProtocolVersion::v1_17)
		return 0x32;

	return 0x30;
}

byte_t acp::packet::play::s2c::PlayerAbilities::getFlags() const
{
	return flags;
}

void acp::packet::play::s2c::PlayerAbilities::setFlags(const byte_t flags)
{
	this->flags = flags;
}

float acp::packet::play::s2c::PlayerAbilities::getFlyingSpeed() const
{
	return flyingSpeed;
}

void acp::packet::play::s2c::PlayerAbilities::setFlyingSpeed(const float flying_speed)
{
	flyingSpeed = flying_speed;
}

float acp::packet::play::s2c::PlayerAbilities::getFovModifier() const
{
	return fovModifier;
}

void acp::packet::play::s2c::PlayerAbilities::setFovModifier(const float fov_modifier)
{
	fovModifier = fov_modifier;
}

std::string acp::packet::play::s2c::PlayerAbilities::toString() const
{
	return std::format("PlayerAbilities[fl={:08b}, flySpeed={}, fovMod={}]", flags, flyingSpeed, fovModifier);
}
