#include "login_acknowledged.hh"

#include "network/handler/login_handler.hh"
#include "network/protocol/protocol_version.hh"

void acp::packet::login::c2s::LoginAcknowledged::read(const ProtocolVersion* version)
{
}

void acp::packet::login::c2s::LoginAcknowledged::write(const ProtocolVersion* version)
{
}

bool acp::packet::login::c2s::LoginAcknowledged::apply(std::unique_ptr<INetworkHandler>& handler)
{
	if (auto* loginHandler = dynamic_cast<LoginHandler*>(handler.get()))
		return loginHandler->handle(this);

	return false;
}

int acp::packet::login::c2s::LoginAcknowledged::getId(const ProtocolVersion* version) const
{
	if (*version >= ProtocolVersion::v1_20_2)
		return 0x03;

	return -1;
}

std::string acp::packet::login::c2s::LoginAcknowledged::toString() const
{
	return "LoginAcknowledged";
}
