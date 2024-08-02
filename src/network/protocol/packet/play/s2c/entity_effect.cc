#include "entity_effect.hh"

#include "network/handler/play_handler.hh"
#include "network/protocol/protocol_version.hh"

void acp::packet::play::s2c::EntityEffect::read(const ProtocolVersion* version)
{
	entityId = buf.readVarint();
	effectId = *version >= ProtocolVersion::v1_18_2 ? buf.readVarint() : buf.readByte();
	amplifier = *version >= ProtocolVersion::v1_20_5 ? buf.readVarint() : buf.readByte();
	duration = buf.readVarint();
	flags = buf.readByte();

	if (*version >= ProtocolVersion::v1_19 && *version < ProtocolVersion::v1_20_5)
	{
		if (buf.readByte())
			factorCodec = buf.readNbt(*version < ProtocolVersion::v1_20_2);
	}
}

void acp::packet::play::s2c::EntityEffect::write(const ProtocolVersion* version)
{
	buf.writeVarint(entityId);

	if (*version >= ProtocolVersion::v1_18_2)
		buf.writeVarint(effectId);
	else
		buf.writeByte(effectId);

	if (*version >= ProtocolVersion::v1_20_5)
		buf.writeVarint(amplifier);
	else
		buf.writeByte(amplifier);

	buf.writeVarint(duration);
	buf.writeByte(flags);

	if (*version >= ProtocolVersion::v1_19 && *version < ProtocolVersion::v1_20_5)
	{
		buf.writeByte(factorCodec.has_value());
		if (factorCodec.has_value())
			buf.writeNbt(factorCodec.value(), *version < ProtocolVersion::v1_20_2);
	}
}

acp::HandleResult acp::packet::play::s2c::EntityEffect::apply(std::unique_ptr<INetworkHandler>& handler)
{
	if (auto* playHandler = dynamic_cast<PlayHandler*>(handler.get()))
		return playHandler->handle(this);

	return HandleResult::FORWARD;
}

int acp::packet::play::s2c::EntityEffect::getId(const ProtocolVersion* version) const
{
	if (*version >= ProtocolVersion::v1_20_5)
		return 0x76;
	if (*version >= ProtocolVersion::v1_20_3)
		return 0x72;
	if (*version >= ProtocolVersion::v1_20_2)
		return 0x6E;
	if (*version >= ProtocolVersion::v1_19_4)
		return 0x6C;
	if (*version >= ProtocolVersion::v1_19_3)
		return 0x68;
	if (*version >= ProtocolVersion::v1_19_1)
		return 0x69;
	if (*version >= ProtocolVersion::v1_19)
		return 0x66;
	if (*version >= ProtocolVersion::v1_18)
		return 0x65;
	if (*version >= ProtocolVersion::v1_17)
		return 0x64;

	return 0x59;
}

int acp::packet::play::s2c::EntityEffect::getEntityId() const
{
	return entityId;
}

void acp::packet::play::s2c::EntityEffect::setEntityId(const int entity_id)
{
	entityId = entity_id;
}

int acp::packet::play::s2c::EntityEffect::getEffectId() const
{
	return effectId;
}

void acp::packet::play::s2c::EntityEffect::setEffectId(const int effect_id)
{
	effectId = effect_id;
}

int acp::packet::play::s2c::EntityEffect::getAmplifier() const
{
	return amplifier;
}

void acp::packet::play::s2c::EntityEffect::setAmplifier(const int amplifier)
{
	this->amplifier = amplifier;
}

int acp::packet::play::s2c::EntityEffect::getDuration() const
{
	return duration;
}

void acp::packet::play::s2c::EntityEffect::setDuration(const int duration)
{
	this->duration = duration;
}

byte_t acp::packet::play::s2c::EntityEffect::getFlags() const
{
	return flags;
}

void acp::packet::play::s2c::EntityEffect::setFlags(const byte_t flags)
{
	this->flags = flags;
}

const std::optional<std::unique_ptr<acp::nbt::Tag>>& acp::packet::play::s2c::EntityEffect::getFactorCodec() const
{
	return factorCodec;
}

void acp::packet::play::s2c::EntityEffect::setFactorCodec(std::optional<std::unique_ptr<nbt::Tag>>&& factor_codec)
{
	factorCodec = std::move(factor_codec);
}

std::string acp::packet::play::s2c::EntityEffect::toString() const
{
	return std::format("EntityEffect[id={}, effect={}, amp={}, dur={}, fl=0x{:x}, factor={}]",
					   entityId,
					   effectId,
					   amplifier,
					   duration,
					   flags,
					   factorCodec.has_value() ? factorCodec.value()->toString() : "nullptr"
	);
}
