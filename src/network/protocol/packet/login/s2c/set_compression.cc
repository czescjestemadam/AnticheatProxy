#include "set_compression.hh"

#include <format>

void acp::packet::login::s2c::SetCompression::read(const ProtocolVersion* version)
{
	threshold = buf.readVarint();
}

void acp::packet::login::s2c::SetCompression::write(const ProtocolVersion* version)
{
	buf.writeVarint(threshold);
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
