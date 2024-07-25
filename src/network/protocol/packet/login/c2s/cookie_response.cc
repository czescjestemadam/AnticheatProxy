#include "cookie_response.hh"

#include "network/protocol/protocol_version.hh"
#include "network/handler/login_handler.hh"

#include <format>

void acp::packet::login::c2s::CookieResponse::read(const ProtocolVersion* version)
{
	key = buf.readIdentifier();

	if (buf.readByte())
	{
		const int payloadLen = buf.readVarint();
		payload = buf.readBuf(payloadLen);
	}
}

void acp::packet::login::c2s::CookieResponse::write(const ProtocolVersion* version)
{
	buf.writeIdentifier(key);

	if (payload.has_value())
	{
		buf.writeVarint(payload.value().size());
		buf.writeBuf(payload.value());
	}
}

acp::HandleResult acp::packet::login::c2s::CookieResponse::apply(std::unique_ptr<INetworkHandler>& handler)
{
	if (auto* loginHandler = dynamic_cast<LoginHandler*>(handler.get()))
		return loginHandler->handle(this);

	return HandleResult::FORWARD;
}

int acp::packet::login::c2s::CookieResponse::getId(const ProtocolVersion* version) const
{
	if (*version >= ProtocolVersion::v1_20_5)
		return 0x04;

	return -1;
}

acp::Identifier& acp::packet::login::c2s::CookieResponse::getKey()
{
	return key;
}

void acp::packet::login::c2s::CookieResponse::setKey(const Identifier& key)
{
	this->key = key;
}

std::optional<acp::ByteBuf>& acp::packet::login::c2s::CookieResponse::getPayload()
{
	return payload;
}

void acp::packet::login::c2s::CookieResponse::setPayload(const std::optional<ByteBuf>& payload)
{
	this->payload = payload;
}

std::string acp::packet::login::c2s::CookieResponse::toString() const
{
	return std::format("CookieResponse[key={}, payload={}]", key.toString(), payload.value_or(ByteBuf{}).toString());
}
