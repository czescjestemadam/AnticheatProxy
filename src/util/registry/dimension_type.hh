#pragma once
#include "util/io/i_serializable.hh"
#include "util/nbt/tag.hh"

#include <memory>
#include <string>

namespace acp::registry
{
	struct DimensionType : ISerializable<std::unique_ptr<nbt::Tag>>
	{
		int monsterSpawnBlockLightLimit;
		float ambientLight;
		/// min max inclusive, type
		std::tuple<int, int, std::string> monsterSpawnLightLevel;
		std::string infiniburn;
		bool hasRaids;
		bool ultrawarm;
		bool respawnAnchorWorks;
		std::string effects;
		int minY;
		int height;
		bool piglinSafe;
		bool natural;
		int logicalHeight;
		double coordinateScale;
		bool hasSkylight;
		bool bedWorks;
		bool hasCeiling;

		std::unique_ptr<nbt::Tag> serialize() override;
		void deserialize(std::unique_ptr<nbt::Tag>& v) override;
	};

	struct DimensionTypeEntry : ISerializable<std::unique_ptr<nbt::Tag>>
	{
		int id;
		DimensionType type;
		std::string name;

		std::unique_ptr<nbt::Tag> serialize() override;
		void deserialize(std::unique_ptr<nbt::Tag>& v) override;
	};
}
