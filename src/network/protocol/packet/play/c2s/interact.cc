#include "interact.hh"

#include "network/handler/play_handler.hh"
#include "network/protocol/protocol_version.hh"

void acp::packet::play::c2s::Interact::read(const ProtocolVersion* version)
{
	entityId = buf.readVarint();
	type = buf.readVarint();

	if (type == 2)
	{
		targetX = buf.readFloat();
		targetY = buf.readFloat();
		targetZ = buf.readFloat();
	}

	if (type == 0 || type == 2)
		hand = buf.readVarint();

	sneaking = buf.readByte();
}

void acp::packet::play::c2s::Interact::write(const ProtocolVersion* version)
{
	buf.writeVarint(entityId);
	buf.writeVarint(type);

	if (type == 2)
	{
		buf.writeFloat(targetX.value_or(0));
		buf.writeFloat(targetY.value_or(0));
		buf.writeFloat(targetZ.value_or(0));
	}

	if (type == 0 || type == 2)
		buf.writeVarint(hand.value_or(0));

	buf.writeByte(sneaking);
}

acp::HandleResult acp::packet::play::c2s::Interact::apply(std::unique_ptr<INetworkHandler>& handler)
{
	if (auto* playHandler = dynamic_cast<PlayHandler*>(handler.get()))
		return playHandler->handle(this);

	return HandleResult::FORWARD;
}

int acp::packet::play::c2s::Interact::getId(const ProtocolVersion* version) const
{
	if (*version >= ProtocolVersion::v1_20_5)
		return 0x16;
	if (*version >= ProtocolVersion::v1_20_3)
		return 0x13;
	if (*version >= ProtocolVersion::v1_20_2)
		return 0x12;
	if (*version >= ProtocolVersion::v1_19_4)
		return 0x10;
	if (*version >= ProtocolVersion::v1_19_3)
		return 0x0F;
	if (*version >= ProtocolVersion::v1_19_1)
		return 0x10;
	if (*version >= ProtocolVersion::v1_19)
		return 0x0F;
	if (*version >= ProtocolVersion::v1_17)
		return 0x0D;

	return 0x0E;
}

int& acp::packet::play::c2s::Interact::getEntityId()
{
	return entityId;
}

void acp::packet::play::c2s::Interact::setEntityId(int entity_id)
{
	entityId = entity_id;
}

int& acp::packet::play::c2s::Interact::getType()
{
	return type;
}

void acp::packet::play::c2s::Interact::setType(int type)
{
	this->type = type;
}

std::optional<float>& acp::packet::play::c2s::Interact::getTargetX()
{
	return targetX;
}

void acp::packet::play::c2s::Interact::setTargetX(const std::optional<float>& target_x)
{
	targetX = target_x;
}

std::optional<float>& acp::packet::play::c2s::Interact::getTargetY()
{
	return targetY;
}

void acp::packet::play::c2s::Interact::setTargetY(const std::optional<float>& target_y)
{
	targetY = target_y;
}

std::optional<float>& acp::packet::play::c2s::Interact::getTargetZ()
{
	return targetZ;
}

void acp::packet::play::c2s::Interact::setTargetZ(const std::optional<float>& target_z)
{
	targetZ = target_z;
}

std::optional<int>& acp::packet::play::c2s::Interact::getHand()
{
	return hand;
}

void acp::packet::play::c2s::Interact::setHand(const std::optional<int>& hand)
{
	this->hand = hand;
}

bool& acp::packet::play::c2s::Interact::isSneaking()
{
	return sneaking;
}

void acp::packet::play::c2s::Interact::setSneaking(bool sneaking)
{
	this->sneaking = sneaking;
}

std::string acp::packet::play::c2s::Interact::toString() const
{
	return std::format("Interact[id={}, type={}, target={} {} {}, hand={}, sneak={}]",
					   entityId,
					   type,
					   targetX.value_or(0),
					   targetY.value_or(0),
					   targetZ.value_or(0),
					   hand.value_or(-1),
					   sneaking
	);
}
