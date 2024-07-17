#include "login_success.hh"

#include "network/handler/login_handler.hh"

#include <format>

void acp::packet::login::s2c::LoginSuccess::read(const ProtocolVersion* version)
{
	uuid = buf.readUuid();
	username = buf.readStr();
}

void acp::packet::login::s2c::LoginSuccess::write(const ProtocolVersion* version)
{
	buf.writeUuid(uuid);
	buf.writeStr(username);
}

bool acp::packet::login::s2c::LoginSuccess::apply(std::unique_ptr<INetworkHandler>& handler)
{
	if (auto* loginHandler = dynamic_cast<LoginHandler*>(handler.get()))
		return loginHandler->handle(this);

	return false;
}

int acp::packet::login::s2c::LoginSuccess::getId(const ProtocolVersion* version) const
{
	return 2;
}

acp::UUID acp::packet::login::s2c::LoginSuccess::getUuid() const
{
	return uuid;
}

void acp::packet::login::s2c::LoginSuccess::setUuid(const UUID& uuid)
{
	this->uuid = uuid;
}

std::string acp::packet::login::s2c::LoginSuccess::getUsername() const
{
	return username;
}

void acp::packet::login::s2c::LoginSuccess::setUsername(const std::string& username)
{
	this->username = username;
}

std::string acp::packet::login::s2c::LoginSuccess::toString() const
{
	return std::format("LoginSuccess[id={}, name={}]", uuid.toString(), username);
}
