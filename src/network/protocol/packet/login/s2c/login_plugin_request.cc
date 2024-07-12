#include "login_plugin_request.hh"

#include <format>

void acp::packet::login::s2c::LoginPluginRequest::read(const ProtocolVersion* version)
{
	messageId = buf.readVarint();
	channel = buf.readStr();
	data = buf;
}

void acp::packet::login::s2c::LoginPluginRequest::write(const ProtocolVersion* version)
{
	buf.writeVarint(messageId);
	buf.writeStr(channel);
	buf.writeBuf(data);
}

int acp::packet::login::s2c::LoginPluginRequest::getId(const ProtocolVersion* version) const
{
	return 4;
}

int acp::packet::login::s2c::LoginPluginRequest::getMessageId() const
{
	return messageId;
}

void acp::packet::login::s2c::LoginPluginRequest::setMessageId(int message_id)
{
	messageId = message_id;
}

std::string acp::packet::login::s2c::LoginPluginRequest::getChannel() const
{
	return channel;
}

void acp::packet::login::s2c::LoginPluginRequest::setChannel(const std::string& channel)
{
	this->channel = channel;
}

acp::ByteBuf acp::packet::login::s2c::LoginPluginRequest::getData() const
{
	return data;
}

void acp::packet::login::s2c::LoginPluginRequest::setData(const ByteBuf& data)
{
	this->data = data;
}

std::string acp::packet::login::s2c::LoginPluginRequest::toString() const
{
	return std::format("LoginPluginRequest[id={}, ch={}, data={}]", messageId, channel, data.toStringShort());
}
