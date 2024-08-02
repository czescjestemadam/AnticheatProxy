#include "pick_item.hh"

#include "network/handler/play_handler.hh"
#include "network/protocol/protocol_version.hh"

void acp::packet::play::c2s::PickItem::read(const ProtocolVersion* version)
{
	slot = buf.readVarint();
}

void acp::packet::play::c2s::PickItem::write(const ProtocolVersion* version)
{
	buf.writeVarint(slot);
}

acp::HandleResult acp::packet::play::c2s::PickItem::apply(std::unique_ptr<INetworkHandler>& handler)
{
	if (auto* playHandler = dynamic_cast<PlayHandler*>(handler.get()))
		return playHandler->handle(this);

	return HandleResult::FORWARD;
}

int acp::packet::play::c2s::PickItem::getId(const ProtocolVersion* version) const
{
	if (*version >= ProtocolVersion::v1_20_5)
		return 0x20;
	if (*version >= ProtocolVersion::v1_20_3)
		return 0x1D;
	if (*version >= ProtocolVersion::v1_20_2)
		return 0x1C;
	if (*version >= ProtocolVersion::v1_19_4)
		return 0x1A;
	if (*version >= ProtocolVersion::v1_19_3)
		return 0x19;
	if (*version >= ProtocolVersion::v1_19_1)
		return 0x1A;
	if (*version >= ProtocolVersion::v1_19)
		return 0x19;
	if (*version >= ProtocolVersion::v1_17)
		return 0x17;

	return 0x18;
}

int acp::packet::play::c2s::PickItem::getSlot() const
{
	return slot;
}

void acp::packet::play::c2s::PickItem::setSlot(const int slot)
{
	this->slot = slot;
}

std::string acp::packet::play::c2s::PickItem::toString() const
{
	return std::format("PickItem[{}]", slot);
}
