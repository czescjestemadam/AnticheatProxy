#include "cookie_response.hh"

#include "network/handler/configuration_handler.hh"
#include "network/protocol/protocol_version.hh"

void acp::packet::configuration::c2s::CookieResponse::read(const ProtocolVersion* version)
{
	key = buf.readIdentifier();

	if (buf.readByte())
	{
		const int len = buf.readVarint();
		payload = buf.readBuf(len);
	}
}

void acp::packet::configuration::c2s::CookieResponse::write(const ProtocolVersion* version)
{
	buf.writeIdentifier(key);

	buf.writeByte(payload.has_value());
	if (payload.has_value())
	{
		buf.writeVarint(static_cast<int>(payload.value().size()));
		buf.writeBuf(payload.value());
	}
}

acp::HandleResult acp::packet::configuration::c2s::CookieResponse::apply(std::unique_ptr<INetworkHandler>& handler)
{
	if (auto* configHandler = dynamic_cast<ConfigurationHandler*>(handler.get()))
		return configHandler->handle(this);

	return HandleResult::FORWARD;
}

int acp::packet::configuration::c2s::CookieResponse::getId(const ProtocolVersion* version) const
{
	if (*version >= ProtocolVersion::v1_20_5)
		return 0x01;

	return -1;
}

acp::Identifier acp::packet::configuration::c2s::CookieResponse::getKey() const
{
	return key;
}

void acp::packet::configuration::c2s::CookieResponse::setKey(const Identifier& key)
{
	this->key = key;
}

std::optional<acp::ByteBuf>& acp::packet::configuration::c2s::CookieResponse::getPayload()
{
	return payload;
}

void acp::packet::configuration::c2s::CookieResponse::setPayload(const std::optional<ByteBuf>& payload)
{
	this->payload = payload;
}

std::string acp::packet::configuration::c2s::CookieResponse::toString() const
{
	return std::format("CookieResponse[key={}, payload={}]", key.toString(), payload.value_or(ByteBuf{}).toString());
}
