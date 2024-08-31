#include "i_plugin_message.hh"

void acp::packet::IPluginMessage::read(const ProtocolVersion* version)
{
	channel = buf.readIdentifier();
	data = buf.readBuf(buf.size());
}

void acp::packet::IPluginMessage::write(const ProtocolVersion* version)
{
	buf.writeIdentifier(channel);
	buf.writeBuf(data);
}

acp::Identifier& acp::packet::IPluginMessage::getChannel()
{
	return channel;
}

const acp::Identifier& acp::packet::IPluginMessage::getChannel() const
{
	return channel;
}

void acp::packet::IPluginMessage::setChannel(const Identifier& channel)
{
	this->channel = channel;
}

acp::ByteBuf& acp::packet::IPluginMessage::getData()
{
	return data;
}

const acp::ByteBuf& acp::packet::IPluginMessage::getData() const
{
	return data;
}

void acp::packet::IPluginMessage::setData(const ByteBuf& data)
{
	this->data = data;
}

std::string acp::packet::IPluginMessage::toString() const
{
	return std::format("PluginMessage[ch={}, data={}]", channel.toString(), data.toStringShort());
}
