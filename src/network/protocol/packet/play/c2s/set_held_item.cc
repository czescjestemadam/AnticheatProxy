#include "set_held_item.hh"

#include "network/handler/play_handler.hh"
#include "network/protocol/protocol_version.hh"

void acp::packet::play::c2s::SetHeldItem::read(const ProtocolVersion* version)
{
	slot = buf.readShort();
}

void acp::packet::play::c2s::SetHeldItem::write(const ProtocolVersion* version)
{
	buf.writeShort(slot);
}

bool acp::packet::play::c2s::SetHeldItem::apply(std::unique_ptr<INetworkHandler>& handler)
{
	if (auto* playHandler = dynamic_cast<PlayHandler*>(handler.get()))
		return playHandler->handle(this);

	return false;
}

int acp::packet::play::c2s::SetHeldItem::getId(const ProtocolVersion* version) const
{
	if (*version >= ProtocolVersion::v1_20_5)
		return 0x2F;
	if (*version >= ProtocolVersion::v1_20_3)
		return 0x2C;
	if (*version >= ProtocolVersion::v1_20_2)
		return 0x2B;
	if (*version >= ProtocolVersion::v1_19_1)
		return 0x28;
	if (*version >= ProtocolVersion::v1_19)
		return 0x27;

	return 0x25;
}

short acp::packet::play::c2s::SetHeldItem::getSlot() const
{
	return slot;
}

void acp::packet::play::c2s::SetHeldItem::setSlot(const short slot)
{
	this->slot = slot;
}

std::string acp::packet::play::c2s::SetHeldItem::toString() const
{
	return std::format("SetHeldItem[{}]", slot);
}
