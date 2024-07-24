#include "set_held_item.hh"

#include "network/handler/play_handler.hh"
#include "network/protocol/protocol_version.hh"

void acp::packet::play::s2c::SetHeldItem::read(const ProtocolVersion* version)
{
	slot = buf.readByte();
}

void acp::packet::play::s2c::SetHeldItem::write(const ProtocolVersion* version)
{
	buf.writeByte(slot);
}

bool acp::packet::play::s2c::SetHeldItem::apply(std::unique_ptr<INetworkHandler>& handler)
{
	if (auto* playHandler = dynamic_cast<PlayHandler*>(handler.get()))
		return playHandler->handle(this);

	return false;
}

int acp::packet::play::s2c::SetHeldItem::getId(const ProtocolVersion* version) const
{
	if (*version >= ProtocolVersion::v1_20_5)
		return 0x53;
	if (*version >= ProtocolVersion::v1_20_3)
		return 0x51;
	if (*version >= ProtocolVersion::v1_20_2)
		return 0x4F;
	if (*version >= ProtocolVersion::v1_19_4)
		return 0x4D;
	if (*version >= ProtocolVersion::v1_19_3)
		return 0x49;
	if (*version >= ProtocolVersion::v1_19_1)
		return 0x4A;
	if (*version >= ProtocolVersion::v1_19)
		return 0x47;
	if (*version >= ProtocolVersion::v1_17)
		return 0x48;

	return 0x3F;
}

byte_t acp::packet::play::s2c::SetHeldItem::getSlot() const
{
	return slot;
}

void acp::packet::play::s2c::SetHeldItem::setSlot(byte_t slot)
{
	this->slot = slot;
}

std::string acp::packet::play::s2c::SetHeldItem::toString() const
{
	return std::format("SetHeldItem[{}]", slot);
}
