#include "login_start.hh"

#include "network/handler/login_handler.hh"

#include <format>

void acp::packet::login::c2s::LoginStart::read(const ProtocolVersion* version)
{
	username = buf.readStr();
}

void acp::packet::login::c2s::LoginStart::write(const ProtocolVersion* version)
{
	buf.writeStr(username);
}

bool acp::packet::login::c2s::LoginStart::apply(std::unique_ptr<INetworkHandler>& handler)
{
	if (auto* loginHandler = dynamic_cast<LoginHandler*>(handler.get()))
		return loginHandler->handle(this);

	return false;
}

int acp::packet::login::c2s::LoginStart::getId(const ProtocolVersion* version) const
{
	return 0;
}

std::string acp::packet::login::c2s::LoginStart::getUsername() const
{
	return username;
}

void acp::packet::login::c2s::LoginStart::setUsername(const std::string& username)
{
	this->username = username;
}

std::string acp::packet::login::c2s::LoginStart::toString() const
{
	return std::format("LoginStart[{}]", username);
}
