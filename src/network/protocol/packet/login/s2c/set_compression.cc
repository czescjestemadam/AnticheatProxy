#include "set_compression.hh"

#include "network/handler/login_handler.hh"

#include <format>

void acp::packet::login::s2c::SetCompression::read(const ProtocolVersion* version)
{
	threshold = buf.readVarint();
}

void acp::packet::login::s2c::SetCompression::write(const ProtocolVersion* version)
{
	buf.writeVarint(threshold);
}

bool acp::packet::login::s2c::SetCompression::apply(std::unique_ptr<INetworkHandler>& handler)
{
	if (auto* loginHandler = dynamic_cast<LoginHandler*>(handler.get()))
		return loginHandler->handle(this);

	return false;
}

int acp::packet::login::s2c::SetCompression::getId(const ProtocolVersion* version) const
{
	return 0x03;
}

int acp::packet::login::s2c::SetCompression::getThreshold() const
{
	return threshold;
}

void acp::packet::login::s2c::SetCompression::setThreshold(int threshold)
{
	this->threshold = threshold;
}

std::string acp::packet::login::s2c::SetCompression::toString() const
{
	return std::format("SetCompression[{}]", threshold);
}
