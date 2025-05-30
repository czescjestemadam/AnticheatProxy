#include "login_plugin_response.hh"

#include "network/handler/login_handler.hh"

#include <format>

void acp::packet::login::c2s::LoginPluginResponse::read(const ProtocolVersion* version)
{
	messageId = buf.readVarint();
	success = buf.readByte();
	data = buf.readBuf(buf.size());
}

void acp::packet::login::c2s::LoginPluginResponse::write(const ProtocolVersion* version)
{
	buf.writeVarint(messageId);
	buf.writeByte(success);
	buf.writeBuf(data);
}

acp::HandleResult acp::packet::login::c2s::LoginPluginResponse::apply(std::unique_ptr<INetworkHandler>& handler)
{
	if (auto* loginHandler = dynamic_cast<LoginHandler*>(handler.get()))
		return loginHandler->handle(this);

	return HandleResult::FORWARD;
}

int acp::packet::login::c2s::LoginPluginResponse::getId(const ProtocolVersion* version) const
{
	return 0x02;
}

int acp::packet::login::c2s::LoginPluginResponse::getMessageId() const
{
	return messageId;
}

void acp::packet::login::c2s::LoginPluginResponse::setMessageId(int message_id)
{
	messageId = message_id;
}

bool acp::packet::login::c2s::LoginPluginResponse::isSuccess() const
{
	return success;
}

void acp::packet::login::c2s::LoginPluginResponse::setSuccess(bool success)
{
	this->success = success;
}

acp::ByteBuf acp::packet::login::c2s::LoginPluginResponse::getData() const
{
	return data;
}

void acp::packet::login::c2s::LoginPluginResponse::setData(const ByteBuf& data)
{
	this->data = data;
}

std::string acp::packet::login::c2s::LoginPluginResponse::toString() const
{
	return std::format("LoginPluginResponse[id={}, success={}, data={}]", messageId, success, data.toStringShort());
}
