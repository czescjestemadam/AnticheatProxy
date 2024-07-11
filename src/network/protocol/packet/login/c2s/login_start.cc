#include "login_start.hh"

#include <format>

void acp::packet::login::c2s::LoginStart::read(const ProtocolVersion* version)
{
	username = buf.readStr();
}

void acp::packet::login::c2s::LoginStart::write(const ProtocolVersion* version)
{
	buf.writeStr(username);
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
