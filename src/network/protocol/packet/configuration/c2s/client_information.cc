#include "client_information.hh"

#include "network/protocol/protocol_version.hh"
#include "network/handler/configuration_handler.hh"

#include <format>

void acp::packet::configuration::c2s::ClientInformation::read(const ProtocolVersion* version)
{
	locale = buf.readStr();
	viewDistance = buf.readByte();
	chatMode = buf.readVarint();
	chatColors = buf.readByte();
	skinParts = buf.readByte();
	mainHand = buf.readVarint();
	textFiltering = buf.readByte();
	allowServerListing = buf.readByte();
}

void acp::packet::configuration::c2s::ClientInformation::write(const ProtocolVersion* version)
{
	buf.writeStr(locale);
	buf.writeByte(viewDistance);
	buf.writeVarint(chatMode);
	buf.writeByte(chatColors);
	buf.writeByte(skinParts);
	buf.writeVarint(mainHand);
	buf.writeByte(textFiltering);
	buf.writeByte(allowServerListing);
}

bool acp::packet::configuration::c2s::ClientInformation::apply(std::unique_ptr<INetworkHandler>& handler)
{
	if (auto* configHandler = dynamic_cast<ConfigurationHandler*>(handler.get()))
		return configHandler->handle(this);

	return false;
}

int acp::packet::configuration::c2s::ClientInformation::getId(const ProtocolVersion* version) const
{
	if (*version >= ProtocolVersion::v1_20_2)
		return 0x00;

	return -1;
}

std::string& acp::packet::configuration::c2s::ClientInformation::getLocale()
{
	return locale;
}

void acp::packet::configuration::c2s::ClientInformation::setLocale(const std::string& locale)
{
	this->locale = locale;
}

byte_t& acp::packet::configuration::c2s::ClientInformation::getViewDistance()
{
	return viewDistance;
}

void acp::packet::configuration::c2s::ClientInformation::setViewDistance(byte_t view_distance)
{
	viewDistance = view_distance;
}

int& acp::packet::configuration::c2s::ClientInformation::getChatMode()
{
	return chatMode;
}

void acp::packet::configuration::c2s::ClientInformation::setChatMode(int chat_mode)
{
	chatMode = chat_mode;
}

bool& acp::packet::configuration::c2s::ClientInformation::isChatColors()
{
	return chatColors;
}

void acp::packet::configuration::c2s::ClientInformation::setChatColors(bool chat_colors)
{
	chatColors = chat_colors;
}

byte_t& acp::packet::configuration::c2s::ClientInformation::getSkinParts()
{
	return skinParts;
}

void acp::packet::configuration::c2s::ClientInformation::setSkinParts(byte_t skin_parts)
{
	skinParts = skin_parts;
}

int& acp::packet::configuration::c2s::ClientInformation::getMainHand()
{
	return mainHand;
}

void acp::packet::configuration::c2s::ClientInformation::setMainHand(int main_hand)
{
	mainHand = main_hand;
}

bool& acp::packet::configuration::c2s::ClientInformation::isTextFiltering()
{
	return textFiltering;
}

void acp::packet::configuration::c2s::ClientInformation::setTextFiltering(bool text_filtering)
{
	textFiltering = text_filtering;
}

bool& acp::packet::configuration::c2s::ClientInformation::isAllowServerListing()
{
	return allowServerListing;
}

void acp::packet::configuration::c2s::ClientInformation::setAllowServerListing(bool allow_server_listing)
{
	allowServerListing = allow_server_listing;
}

std::string acp::packet::configuration::c2s::ClientInformation::toString() const
{
	return std::format("ClientInformation[locale={}, viewDist={}, chat={}, colors={}, skin={}, hand={}, textFilter={}, listing={}]", locale, viewDistance, chatMode, chatColors, skinParts, mainHand, textFiltering, allowServerListing);
}
