#include "block_entity_data.hh"

#include "network/handler/play_handler.hh"
#include "network/protocol/protocol_version.hh"

void acp::packet::play::s2c::BlockEntityData::read(const ProtocolVersion* version)
{
	position = buf.readPosition();
	type = *version < ProtocolVersion::v1_18 ? buf.readByte() : buf.readVarint();
	data = buf.readNbt(*version < ProtocolVersion::v1_20_2);
}

void acp::packet::play::s2c::BlockEntityData::write(const ProtocolVersion* version)
{
	buf.writePosition(position);
	if (*version < ProtocolVersion::v1_18)
		buf.writeByte(type);
	else
		buf.writeVarint(type);
	buf.writeNbt(data, *version < ProtocolVersion::v1_20_2);
}

acp::HandleResult acp::packet::play::s2c::BlockEntityData::apply(std::unique_ptr<INetworkHandler>& handler)
{
	if (auto* playHandler = dynamic_cast<PlayHandler*>(handler.get()))
		return playHandler->handle(this);

	return HandleResult::FORWARD;
}

int acp::packet::play::s2c::BlockEntityData::getId(const ProtocolVersion* version) const
{
	if (*version >= ProtocolVersion::v1_20_2)
		return 0x07;
	if (*version >= ProtocolVersion::v1_19_4)
		return 0x08;
	if (*version >= ProtocolVersion::v1_19)
		return 0x07;
	if (*version >= ProtocolVersion::v1_17)
		return 0x0A;

	return 0x09;
}

const acp::Vec3i& acp::packet::play::s2c::BlockEntityData::getPosition() const
{
	return position;
}

void acp::packet::play::s2c::BlockEntityData::setPosition(const Vec3i& position)
{
	this->position = position;
}

int acp::packet::play::s2c::BlockEntityData::getType() const
{
	return type;
}

void acp::packet::play::s2c::BlockEntityData::setType(const int type)
{
	this->type = type;
}

std::unique_ptr<acp::nbt::Tag>& acp::packet::play::s2c::BlockEntityData::getData()
{
	return data;
}

const std::unique_ptr<acp::nbt::Tag>& acp::packet::play::s2c::BlockEntityData::getData() const
{
	return data;
}

void acp::packet::play::s2c::BlockEntityData::setData(std::unique_ptr<nbt::Tag>&& data)
{
	this->data = std::move(data);
}

std::string acp::packet::play::s2c::BlockEntityData::toString() const
{
	return std::format("BlockEntityData[pos={} {} {}, type={}, data={}]",
					   position.x, position.y, position.z,
					   type,
					   data->toString()
	);
}
