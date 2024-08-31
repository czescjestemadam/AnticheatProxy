#include "plugin_messenger.hh"

#include "util/str_utils.hh"

#include <ranges>

#include "connection.hh"

static const auto REGISTER_CHANNEL = acp::Identifier("minecraft", "register");
static const auto UNREGISTER_CHANNEL = acp::Identifier("minecraft", "unregister");
static const auto BRAND_CHANNEL = acp::Identifier("minecraft", "brand");

std::vector<std::string> getStrings(const acp::ByteBuf& data);


acp::PluginMessenger::PluginMessenger(Connection* connection) : connection(connection)
{
}

acp::HandleResult acp::PluginMessenger::onPluginMessage(NetworkSide to, packet::IPluginMessage* packet)
{
	if (packet->getChannel() == REGISTER_CHANNEL)
	{
		for (const std::string& channel : getStrings(packet->getData()))
			registerChannel(Identifier::parse(channel));
	}
	else if (packet->getChannel() == UNREGISTER_CHANNEL)
	{
		for (const std::string& channel : getStrings(packet->getData()))
			unregisterChannel(Identifier::parse(channel));
	}
	else if (packet->getChannel() == BRAND_CHANNEL)
	{
		if (to == NetworkSide::DEST)
			connection->setClientbrand(packet->getData().readStr());
	}

	return HandleResult::FORWARD;
}

void acp::PluginMessenger::registerChannel(const Identifier& channel)
{
	registeredChannels.push_back(channel);
}

void acp::PluginMessenger::unregisterChannel(const Identifier& channel)
{
	const auto& it = std::ranges::find(registeredChannels, channel);
	if (it != registeredChannels.end())
		registeredChannels.erase(it);
}

const std::vector<acp::Identifier>& acp::PluginMessenger::getRegisteredChannels() const
{
	return registeredChannels;
}


std::vector<std::string> getStrings(const acp::ByteBuf& data)
{
	std::vector<std::string> arr;

	std::string str;
	for (int i = 0; i < data.size(); ++i)
	{
		const byte_t byte = data.data()[i];
		if (byte == 0)
		{
			arr.push_back(str);
			str.clear();
		}
		else
			str += static_cast<char>(byte);
	}

	return arr;
}
