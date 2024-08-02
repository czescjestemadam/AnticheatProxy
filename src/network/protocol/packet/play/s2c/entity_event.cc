#include "entity_event.hh"

#include "network/handler/play_handler.hh"
#include "network/protocol/protocol_version.hh"

void acp::packet::play::s2c::EntityEvent::read(const ProtocolVersion* version)
{
	entityId = buf.readInt();
	status = buf.readByte();
}

void acp::packet::play::s2c::EntityEvent::write(const ProtocolVersion* version)
{
	buf.writeInt(entityId);
	buf.writeByte(status);
}

acp::HandleResult acp::packet::play::s2c::EntityEvent::apply(std::unique_ptr<INetworkHandler>& handler)
{
	if (auto* playHandler = dynamic_cast<PlayHandler*>(handler.get()))
		return playHandler->handle(this);

	return HandleResult::FORWARD;
}

int acp::packet::play::s2c::EntityEvent::getId(const ProtocolVersion* version) const
{
	if (*version >= ProtocolVersion::v1_20_5)
		return 0x1F;
	if (*version >= ProtocolVersion::v1_20_2)
		return 0x1D;
	if (*version >= ProtocolVersion::v1_19_4)
		return 0x1C;
	if (*version >= ProtocolVersion::v1_19_3)
		return 0x19;
	if (*version >= ProtocolVersion::v1_19_1)
		return 0x1A;
	if (*version >= ProtocolVersion::v1_19)
		return 0x18;
	if (*version >= ProtocolVersion::v1_17)
		return 0x1B;

	return 0x1A;
}

int acp::packet::play::s2c::EntityEvent::getEntityId() const
{
	return entityId;
}

void acp::packet::play::s2c::EntityEvent::setEntityId(const int entity_id)
{
	entityId = entity_id;
}

byte_t acp::packet::play::s2c::EntityEvent::getStatus() const
{
	return status;
}

void acp::packet::play::s2c::EntityEvent::setStatus(const byte_t status)
{
	this->status = status;
}

std::string acp::packet::play::s2c::EntityEvent::toString() const
{
	return std::format("EntityEvent[id={}, status={}]", entityId, status);
}
