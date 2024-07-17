#include "login_plugin_request.hh"

#include "network/handler/login_handler.hh"

#include <format>

void acp::packet::login::s2c::LoginPluginRequest::read(const ProtocolVersion* version)
{
	messageId = buf.readVarint();
	channel = buf.readIdentifier();
	data = buf;
}

void acp::packet::login::s2c::LoginPluginRequest::write(const ProtocolVersion* version)
{
	buf.writeVarint(messageId);
	buf.writeIdentifier(channel);
	buf.writeBuf(data);
}

bool acp::packet::login::s2c::LoginPluginRequest::apply(std::unique_ptr<INetworkHandler>& handler)
{
	if (auto* loginHandler = dynamic_cast<LoginHandler*>(handler.get()))
		return loginHandler->handle(this);

	return false;
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

acp::Identifier& acp::packet::login::s2c::LoginPluginRequest::getChannel()
{
	return channel;
}

void acp::packet::login::s2c::LoginPluginRequest::setChannel(const Identifier& channel)
{
	this->channel = channel;
}

acp::ByteBuf& acp::packet::login::s2c::LoginPluginRequest::getData()
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
