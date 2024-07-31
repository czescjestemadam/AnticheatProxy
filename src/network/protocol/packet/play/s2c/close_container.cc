#include "close_container.hh"

#include "network/handler/play_handler.hh"
#include "network/protocol/protocol_version.hh"

void acp::packet::play::s2c::CloseContainer::read(const ProtocolVersion* version)
{
	windowId = buf.readByte();
}

void acp::packet::play::s2c::CloseContainer::write(const ProtocolVersion* version)
{
	buf.writeByte(windowId);
}

acp::HandleResult acp::packet::play::s2c::CloseContainer::apply(std::unique_ptr<INetworkHandler>& handler)
{
	if (auto* playHandler = dynamic_cast<PlayHandler*>(handler.get()))
		return playHandler->handle(this);

	return HandleResult::FORWARD;
}

int acp::packet::play::s2c::CloseContainer::getId(const ProtocolVersion* version) const
{
	if (*version >= ProtocolVersion::v1_20_2)
		return 0x12;
	if (*version >= ProtocolVersion::v1_19_4)
		return 0x11;
	if (*version >= ProtocolVersion::v1_19_3)
		return 0x0F;
	if (*version >= ProtocolVersion::v1_19)
		return 0x10;
	if (*version >= ProtocolVersion::v1_17)
		return 0x13;

	return 0x12;
}

byte_t acp::packet::play::s2c::CloseContainer::getWindowId() const
{
	return windowId;
}

void acp::packet::play::s2c::CloseContainer::setWindowId(const byte_t window_id)
{
	windowId = window_id;
}

std::string acp::packet::play::s2c::CloseContainer::toString() const
{
	return std::format("CloseContainer[{}]", windowId);
}
