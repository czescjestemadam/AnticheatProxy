#include "feature_flags.hh"

#include "network/handler/configuration_handler.hh"
#include "network/protocol/protocol_version.hh"

void acp::packet::configuration::s2c::FeatureFlags::read(const ProtocolVersion* version)
{
	const int length = buf.readVarint();
	for (int i = 0; i < length; ++i)
		flags.push_back(buf.readIdentifier());
}

void acp::packet::configuration::s2c::FeatureFlags::write(const ProtocolVersion* version)
{
	buf.writeVarint(static_cast<int>(flags.size()));
	for (Identifier& flag : flags)
		buf.writeIdentifier(flag);
}

bool acp::packet::configuration::s2c::FeatureFlags::apply(std::unique_ptr<INetworkHandler>& handler)
{
	if (auto* configHandler = dynamic_cast<ConfigurationHandler*>(handler.get()))
		return configHandler->handle(this);

	return false;
}

int acp::packet::configuration::s2c::FeatureFlags::getId(const ProtocolVersion* version) const
{
	if (*version >= ProtocolVersion::v1_21)
		return 0x0C;
	if (*version >= ProtocolVersion::v1_20_3)
		return 0x08;
	if (*version >= ProtocolVersion::v1_20_2)
		return 0x07;

	return -1;
}

std::vector<acp::Identifier>& acp::packet::configuration::s2c::FeatureFlags::getFlags()
{
	return flags;
}

void acp::packet::configuration::s2c::FeatureFlags::setFlags(const std::vector<Identifier>& flags)
{
	this->flags = flags;
}

std::string acp::packet::configuration::s2c::FeatureFlags::toString() const
{
	return std::format("FeatureFlags[size={}]", flags.size());
}
