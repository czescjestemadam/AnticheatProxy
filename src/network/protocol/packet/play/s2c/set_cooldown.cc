#include "set_cooldown.hh"

#include "network/handler/play_handler.hh"
#include "network/protocol/protocol_version.hh"

void acp::packet::play::s2c::SetCooldown::read(const ProtocolVersion* version)
{
	itemId = buf.readVarint();
	ticks = buf.readVarint();
}

void acp::packet::play::s2c::SetCooldown::write(const ProtocolVersion* version)
{
	buf.writeVarint(itemId);
	buf.writeVarint(ticks);
}

bool acp::packet::play::s2c::SetCooldown::apply(std::unique_ptr<INetworkHandler>& handler)
{
	if (auto* playHandler = dynamic_cast<PlayHandler*>(handler.get()))
		return playHandler->handle(this);

	return false;
}

int acp::packet::play::s2c::SetCooldown::getId(const ProtocolVersion* version) const
{
	if (*version >= ProtocolVersion::v1_20_5)
		return 0x17;
	if (*version >= ProtocolVersion::v1_20_2)
		return 0x16;
	if (*version >= ProtocolVersion::v1_19_4)
		return 0x15;
	if (*version >= ProtocolVersion::v1_19_3)
		return 0x13;
	if (*version >= ProtocolVersion::v1_19)
		return 0x14;
	if (*version >= ProtocolVersion::v1_17)
		return 0x17;

	return 0x16;
}

int acp::packet::play::s2c::SetCooldown::getItemId() const
{
	return itemId;
}

void acp::packet::play::s2c::SetCooldown::setItemId(const int item_id)
{
	itemId = item_id;
}

int acp::packet::play::s2c::SetCooldown::getTicks() const
{
	return ticks;
}

void acp::packet::play::s2c::SetCooldown::setTicks(const int ticks)
{
	this->ticks = ticks;
}

std::string acp::packet::play::s2c::SetCooldown::toString() const
{
	return std::format("SetCooldown[item={}, ticks={}]", itemId, ticks);
}
