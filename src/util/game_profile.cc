#include "game_profile.hh"

#include "network/protocol/protocol_version.hh"

acp::GameProfile::Property::Property(const std::string& name, const std::string& value, const std::string& signature)
	: name(name), value(value), signature(signature)
{
}

acp::GameProfile::GameProfile(const UUID& uuid, const std::string& username, const std::vector<Property>& properties)
	: uuid(uuid), username(username), properties(properties)
{
}
