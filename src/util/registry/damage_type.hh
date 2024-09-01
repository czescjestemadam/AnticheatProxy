#pragma once
#include "util/io/i_serializable.hh"
#include "util/nbt/tag.hh"

#include <memory>

namespace acp::registry
{
	struct DamageType : ISerializable<std::unique_ptr<nbt::Tag>>
	{
		std::string deathMessageType;
		std::string effects;
		float exhaustion;
		std::string messageId;
		std::string scaling;

		std::unique_ptr<nbt::Tag> serialize() override;
		void deserialize(std::unique_ptr<nbt::Tag>& v) override;
	};

	struct DamageTypeEntry : ISerializable<std::unique_ptr<nbt::Tag>>
	{
		int id;
		DamageType type;
		std::string name;

		DamageTypeEntry() = default;
		DamageTypeEntry(int id, const DamageType& type, const std::string& name);

		std::unique_ptr<nbt::Tag> serialize() override;
		void deserialize(std::unique_ptr<nbt::Tag>& v) override;
	};
}
