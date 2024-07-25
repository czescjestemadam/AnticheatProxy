#include "cookie_request.hh"

#include "network/protocol/protocol_version.hh"
#include "network/handler/login_handler.hh"

#include <format>

void acp::packet::login::s2c::CookieRequest::read(const ProtocolVersion* version)
{
	key = buf.readIdentifier();
}

void acp::packet::login::s2c::CookieRequest::write(const ProtocolVersion* version)
{
	buf.writeIdentifier(key);
}

acp::HandleResult acp::packet::login::s2c::CookieRequest::apply(std::unique_ptr<INetworkHandler>& handler)
{
	if (auto* loginHandler = dynamic_cast<LoginHandler*>(handler.get()))
		return loginHandler->handle(this);

	return HandleResult::FORWARD;
}

int acp::packet::login::s2c::CookieRequest::getId(const ProtocolVersion* version) const
{
	if (*version >= ProtocolVersion::v1_20_5)
		return 0x05;

	return -1;
}

acp::Identifier& acp::packet::login::s2c::CookieRequest::getKey()
{
	return key;
}

void acp::packet::login::s2c::CookieRequest::setKey(const Identifier& key)
{
	this->key = key;
}

std::string acp::packet::login::s2c::CookieRequest::toString() const
{
	return std::format("CookieRequest[{}]", key.toString());
}
