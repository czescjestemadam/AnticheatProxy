#include "update_entity_position.hh"

#include "network/handler/play_handler.hh"
#include "network/protocol/protocol_version.hh"

void acp::packet::play::s2c::UpdateEntityPosition::read(const ProtocolVersion* version)
{
	entityId = buf.readVarint();
	delta = {
		buf.readShort(),
		buf.readShort(),
		buf.readShort()
	};
	onGround = buf.readByte();
}

void acp::packet::play::s2c::UpdateEntityPosition::write(const ProtocolVersion* version)
{
	buf.writeVarint(entityId);
	buf.writeShort(delta.x);
	buf.writeShort(delta.y);
	buf.writeShort(delta.z);
	buf.writeByte(onGround);
}

acp::HandleResult acp::packet::play::s2c::UpdateEntityPosition::apply(std::unique_ptr<INetworkHandler>& handler)
{
	if (auto* playHandler = dynamic_cast<PlayHandler*>(handler.get()))
		return playHandler->handle(this);

	return HandleResult::FORWARD;
}

int acp::packet::play::s2c::UpdateEntityPosition::getId(const ProtocolVersion* version) const
{
	if (*version >= ProtocolVersion::v1_20_5)
		return 0x2E;
	if (*version >= ProtocolVersion::v1_20_2)
		return 0x2C;
	if (*version >= ProtocolVersion::v1_19_4)
		return 0x2B;
	if (*version >= ProtocolVersion::v1_19_3)
		return 0x27;
	if (*version >= ProtocolVersion::v1_19_1)
		return 0x28;
	if (*version >= ProtocolVersion::v1_19)
		return 0x26;
	if (*version >= ProtocolVersion::v1_17)
		return 0x29;

	return 0x27;
}

int acp::packet::play::s2c::UpdateEntityPosition::getEntityId() const
{
	return entityId;
}

void acp::packet::play::s2c::UpdateEntityPosition::setEntityId(const int entity_id)
{
	entityId = entity_id;
}

acp::Vec3s acp::packet::play::s2c::UpdateEntityPosition::getDelta() const
{
	return delta;
}

void acp::packet::play::s2c::UpdateEntityPosition::setDelta(const Vec3s& delta)
{
	this->delta = delta;
}

bool acp::packet::play::s2c::UpdateEntityPosition::isOnGround() const
{
	return onGround;
}

void acp::packet::play::s2c::UpdateEntityPosition::setOnGround(const bool on_ground)
{
	onGround = on_ground;
}

std::string acp::packet::play::s2c::UpdateEntityPosition::toString() const
{
	return std::format("UpdateEntityPosition[id={}, delta={} {} {}, ground={}]", entityId, delta.x, delta.y, delta.z, onGround);
}
