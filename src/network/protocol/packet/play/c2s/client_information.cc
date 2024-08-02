#include "client_information.hh"

#include "network/handler/play_handler.hh"
#include "network/protocol/protocol_version.hh"

void acp::packet::play::c2s::ClientInformation::read(const ProtocolVersion* version)
{
	locale = buf.readStr();
	viewDistance = buf.readByte();
	chatMode = buf.readVarint();
	chatColors = buf.readByte();
	skinParts = buf.readByte();
	mainHand = buf.readVarint();

	if (*version >= ProtocolVersion::v1_18)
		textFiltering = buf.readByte();
	else if (*version >= ProtocolVersion::v1_17)
		textFiltering = !buf.readByte();

	if (*version >= ProtocolVersion::v1_18)
		allowServerListing = buf.readByte();
}

void acp::packet::play::c2s::ClientInformation::write(const ProtocolVersion* version)
{
	buf.writeStr(locale);
	buf.writeByte(viewDistance);
	buf.writeVarint(chatMode);
	buf.writeByte(chatColors);
	buf.writeByte(skinParts);
	buf.writeVarint(mainHand);

	if (*version >= ProtocolVersion::v1_18)
		buf.writeByte(textFiltering.value());
	else if (*version >= ProtocolVersion::v1_17)
		buf.writeByte(!textFiltering.value());

	if (*version >= ProtocolVersion::v1_18)
		buf.writeByte(allowServerListing.value());
}

acp::HandleResult acp::packet::play::c2s::ClientInformation::apply(std::unique_ptr<INetworkHandler>& handler)
{
	if (auto* playHandler = dynamic_cast<PlayHandler*>(handler.get()))
		return playHandler->handle(this);

	return HandleResult::FORWARD;
}

int acp::packet::play::c2s::ClientInformation::getId(const ProtocolVersion* version) const
{
	if (*version >= ProtocolVersion::v1_20_5)
		return 0x0A;
	if (*version >= ProtocolVersion::v1_20_2)
		return 0x09;
	if (*version >= ProtocolVersion::v1_19_4)
		return 0x08;
	if (*version >= ProtocolVersion::v1_19_3)
		return 0x07;
	if (*version >= ProtocolVersion::v1_19_1)
		return 0x08;
	if (*version >= ProtocolVersion::v1_19)
		return 0x07;

	return 0x05;
}

const std::string& acp::packet::play::c2s::ClientInformation::getLocale() const
{
	return locale;
}

void acp::packet::play::c2s::ClientInformation::setLocale(const std::string& locale)
{
	this->locale = locale;
}

byte_t acp::packet::play::c2s::ClientInformation::getViewDistance() const
{
	return viewDistance;
}

void acp::packet::play::c2s::ClientInformation::setViewDistance(const byte_t view_distance)
{
	viewDistance = view_distance;
}

int acp::packet::play::c2s::ClientInformation::getChatMode() const
{
	return chatMode;
}

void acp::packet::play::c2s::ClientInformation::setChatMode(const int chat_mode)
{
	chatMode = chat_mode;
}

bool acp::packet::play::c2s::ClientInformation::isChatColors() const
{
	return chatColors;
}

void acp::packet::play::c2s::ClientInformation::setChatColors(const bool chat_colors)
{
	chatColors = chat_colors;
}

byte_t acp::packet::play::c2s::ClientInformation::getSkinParts() const
{
	return skinParts;
}

void acp::packet::play::c2s::ClientInformation::setSkinParts(const byte_t skin_parts)
{
	skinParts = skin_parts;
}

int acp::packet::play::c2s::ClientInformation::getMainHand() const
{
	return mainHand;
}

void acp::packet::play::c2s::ClientInformation::setMainHand(const int main_hand)
{
	mainHand = main_hand;
}

const std::optional<bool>& acp::packet::play::c2s::ClientInformation::getTextFiltering() const
{
	return textFiltering;
}

void acp::packet::play::c2s::ClientInformation::setTextFiltering(const std::optional<bool>& text_filtering)
{
	textFiltering = text_filtering;
}

const std::optional<bool>& acp::packet::play::c2s::ClientInformation::getAllowServerListing() const
{
	return allowServerListing;
}

void acp::packet::play::c2s::ClientInformation::setAllowServerListing(const std::optional<bool>& allow_server_listing)
{
	allowServerListing = allow_server_listing;
}

std::string acp::packet::play::c2s::ClientInformation::toString() const
{
	return std::format("ClientInformation[locale={}, viewDist={}, chat={}, colors={}, skin={}, hand={}, textFilter={}, listing={}]",
					   locale,
					   viewDistance,
					   chatMode,
					   chatColors,
					   skinParts,
					   mainHand,
					   textFiltering.value_or(false),
					   allowServerListing.value_or(false)
	);
}
