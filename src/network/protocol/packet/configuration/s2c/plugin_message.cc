#include "plugin_message.hh"

#include "network/handler/configuration_handler.hh"
#include "network/protocol/protocol_version.hh"

void acp::packet::configuration::s2c::PluginMessage::read(const ProtocolVersion* version)
{
	channel = buf.readIdentifier();
	data = buf.readBuf(buf.size());
}

void acp::packet::configuration::s2c::PluginMessage::write(const ProtocolVersion* version)
{
	buf.writeIdentifier(channel);
	buf.writeBuf(data);
}

acp::HandleResult acp::packet::configuration::s2c::PluginMessage::apply(std::unique_ptr<INetworkHandler>& handler)
{
	if (auto* configHandler = dynamic_cast<ConfigurationHandler*>(handler.get()))
		return configHandler->handle(this);

	return HandleResult::FORWARD;
}

int acp::packet::configuration::s2c::PluginMessage::getId(const ProtocolVersion* version) const
{
	if (*version >= ProtocolVersion::v1_20_5)
		return 0x01;
	if (*version >= ProtocolVersion::v1_20_2)
		return 0x00;

	return -1;
}

acp::Identifier& acp::packet::configuration::s2c::PluginMessage::getChannel()
{
	return channel;
}

void acp::packet::configuration::s2c::PluginMessage::setChannel(const Identifier& channel)
{
	this->channel = channel;
}

acp::ByteBuf& acp::packet::configuration::s2c::PluginMessage::getData()
{
	return data;
}

void acp::packet::configuration::s2c::PluginMessage::setData(const ByteBuf& data)
{
	this->data = data;
}

std::string acp::packet::configuration::s2c::PluginMessage::toString() const
{
	return std::format("PluginMessage[ch={}, data={}]", channel.toString(), data.toStringShort());
}
