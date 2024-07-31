#pragma once
#include "uuid.hh"

#include <vector>

namespace acp
{
	struct GameProfile
	{
		struct Property
		{
			std::string name;
			std::string value;
			std::string signature;

			Property() = default;
			Property(const std::string& name, const std::string& value, const std::string& signature);
		};

		UUID uuid;
		std::string username;
		std::vector<Property> properties;

		GameProfile() = default;
		GameProfile(const UUID& uuid, const std::string& username, const std::vector<Property>& properties);
	};
}
