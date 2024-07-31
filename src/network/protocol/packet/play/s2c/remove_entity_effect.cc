#include "remove_entity_effect.hh"

#include "network/handler/play_handler.hh"
#include "network/protocol/protocol_version.hh"

void acp::packet::play::s2c::RemoveEntityEffect::read(const ProtocolVersion* version)
{
	entityId = buf.readVarint();
	effectId = *version >= ProtocolVersion::v1_18_2 ? buf.readVarint() : buf.readByte();
}

void acp::packet::play::s2c::RemoveEntityEffect::write(const ProtocolVersion* version)
{
	buf.writeVarint(entityId);
	if (*version >= ProtocolVersion::v1_18_2)
		buf.writeVarint(effectId);
	else
		buf.writeByte(static_cast<byte_t>(effectId));
}

acp::HandleResult acp::packet::play::s2c::RemoveEntityEffect::apply(std::unique_ptr<INetworkHandler>& handler)
{
	if (auto* playHandler = dynamic_cast<PlayHandler*>(handler.get()))
		return playHandler->handle(this);

	return HandleResult::FORWARD;
}

int acp::packet::play::s2c::RemoveEntityEffect::getId(const ProtocolVersion* version) const
{
	if (*version >= ProtocolVersion::v1_20_5)
		return 0x43;
	if (*version >= ProtocolVersion::v1_20_2)
		return 0x41;
	if (*version >= ProtocolVersion::v1_19_4)
		return 0x3F;
	if (*version >= ProtocolVersion::v1_19_3)
		return 0x3B;
	if (*version >= ProtocolVersion::v1_19_1)
		return 0x3C;
	if (*version >= ProtocolVersion::v1_19)
		return 0x39;
	if (*version >= ProtocolVersion::v1_17)
		return 0x3B;

	return 0x37;
}

int acp::packet::play::s2c::RemoveEntityEffect::getEntityId() const
{
	return entityId;
}

void acp::packet::play::s2c::RemoveEntityEffect::setEntityId(const int entity_id)
{
	entityId = entity_id;
}

int acp::packet::play::s2c::RemoveEntityEffect::getEffectId() const
{
	return effectId;
}

void acp::packet::play::s2c::RemoveEntityEffect::setEffectId(const int effect_id)
{
	effectId = effect_id;
}

std::string acp::packet::play::s2c::RemoveEntityEffect::toString() const
{
	return std::format("RemoveEntityEffect[id={}, effect={}]", entityId, effectId);
}
