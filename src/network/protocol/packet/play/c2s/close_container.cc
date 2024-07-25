#include "close_container.hh"

#include "network/handler/play_handler.hh"
#include "network/protocol/protocol_version.hh"

void acp::packet::play::c2s::CloseContainer::read(const ProtocolVersion* version)
{
	windowId = buf.readByte();
}

void acp::packet::play::c2s::CloseContainer::write(const ProtocolVersion* version)
{
	buf.writeByte(windowId);
}

acp::HandleResult acp::packet::play::c2s::CloseContainer::apply(std::unique_ptr<INetworkHandler>& handler)
{
	if (auto* playHandler = dynamic_cast<PlayHandler*>(handler.get()))
		return playHandler->handle(this);

	return HandleResult::FORWARD;
}

int acp::packet::play::c2s::CloseContainer::getId(const ProtocolVersion* version) const
{
	if (*version >= ProtocolVersion::v1_20_5)
		return 0x0F;
	if (*version >= ProtocolVersion::v1_20_2)
		return 0x0E;
	if (*version >= ProtocolVersion::v1_19_4)
		return 0x0C;
	if (*version >= ProtocolVersion::v1_19_3)
		return 0x0B;
	if (*version >= ProtocolVersion::v1_19_1)
		return 0x0C;
	if (*version >= ProtocolVersion::v1_19)
		return 0x0B;
	if (*version >= ProtocolVersion::v1_17)
		return 0x09;

	return 0x0A;
}

byte_t acp::packet::play::c2s::CloseContainer::getWindowId() const
{
	return windowId;
}

void acp::packet::play::c2s::CloseContainer::setWindowId(const byte_t window_id)
{
	windowId = window_id;
}

std::string acp::packet::play::c2s::CloseContainer::toString() const
{
	return std::format("CloseContainer[{}]", windowId);
}
