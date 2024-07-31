#include "open_screen.hh"

#include "network/handler/play_handler.hh"
#include "network/protocol/protocol_version.hh"

void acp::packet::play::s2c::OpenScreen::read(const ProtocolVersion* version)
{
	windowId = buf.readVarint();
	type = buf.readVarint();

	title = text::Component::fromNbt(buf.readNbt(*version < ProtocolVersion::v1_20_2));
}

void acp::packet::play::s2c::OpenScreen::write(const ProtocolVersion* version)
{
	buf.writeVarint(windowId);
	buf.writeVarint(type);

	std::unique_ptr<nbt::Tag> titleTag = title->serialize();
	buf.writeNbt(titleTag, *version < ProtocolVersion::v1_20_2);
}

acp::HandleResult acp::packet::play::s2c::OpenScreen::apply(std::unique_ptr<INetworkHandler>& handler)
{
	if (auto* playHandler = dynamic_cast<PlayHandler*>(handler.get()))
		return playHandler->handle(this);

	return HandleResult::FORWARD;
}

int acp::packet::play::s2c::OpenScreen::getId(const ProtocolVersion* version) const
{
	if (*version >= ProtocolVersion::v1_20_5)
		return 0x33;
	if (*version >= ProtocolVersion::v1_20_2)
		return 0x31;
	if (*version >= ProtocolVersion::v1_19_4)
		return 0x30;
	if (*version >= ProtocolVersion::v1_19_3)
		return 0x2C;
	if (*version >= ProtocolVersion::v1_19_1)
		return 0x2D;
	if (*version >= ProtocolVersion::v1_19)
		return 0x2B;
	if (*version >= ProtocolVersion::v1_17)
		return 0x2E;

	return 0x2D;
}

int acp::packet::play::s2c::OpenScreen::getWindowId() const
{
	return windowId;
}

void acp::packet::play::s2c::OpenScreen::setWindowId(const int window_id)
{
	windowId = window_id;
}

int acp::packet::play::s2c::OpenScreen::getType() const
{
	return type;
}

void acp::packet::play::s2c::OpenScreen::setType(const int type)
{
	this->type = type;
}

std::unique_ptr<acp::text::Component>& acp::packet::play::s2c::OpenScreen::getTitle()
{
	return title;
}

const std::unique_ptr<acp::text::Component>& acp::packet::play::s2c::OpenScreen::getTitle() const
{
	return title;
}

void acp::packet::play::s2c::OpenScreen::setTitle(std::unique_ptr<text::Component>&& title)
{
	this->title = std::move(title);
}

std::string acp::packet::play::s2c::OpenScreen::toString() const
{
	return std::format("OpenScreen[id={}, type={}, title={}]", windowId, type, title->serialize()->toString());
}
