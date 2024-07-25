#include "disconnect.hh"

#include "network/handler/login_handler.hh"

#include <format>

void acp::packet::login::s2c::Disconnect::read(const ProtocolVersion* version)
{
	reason = buf.readStr();
}

void acp::packet::login::s2c::Disconnect::write(const ProtocolVersion* version)
{
	buf.writeStr(reason);
}

acp::HandleResult acp::packet::login::s2c::Disconnect::apply(std::unique_ptr<INetworkHandler>& handler)
{
	if (auto* loginHandler = dynamic_cast<LoginHandler*>(handler.get()))
		return loginHandler->handle(this);

	return HandleResult::FORWARD;
}

int acp::packet::login::s2c::Disconnect::getId(const ProtocolVersion* version) const
{
	return 0x00;
}

std::string acp::packet::login::s2c::Disconnect::getReason() const
{
	return reason;
}

void acp::packet::login::s2c::Disconnect::setReason(const std::string& reason)
{
	this->reason = reason;
}

std::string acp::packet::login::s2c::Disconnect::toString() const
{
	return std::format("Disconnect[{}]", reason);
}
