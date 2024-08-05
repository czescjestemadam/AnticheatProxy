#include "dimension_type.hh"

#include <algorithm>

#include "util/nbt/tag/tag_compound.hh"
#include "util/nbt/tag/tag_number.hh"
#include "util/nbt/tag/tag_string.hh"

std::unique_ptr<acp::nbt::Tag> acp::registry::DimensionType::serialize()
{
	auto tag = std::make_unique<nbt::TagCompound>();

	tag->get("monster_spawn_block_light_limit") = std::make_unique<nbt::TagInt>(monsterSpawnBlockLightLimit);
	tag->get("ambient_light") = std::make_unique<nbt::TagFloat>(ambientLight);

	auto msTag = std::make_unique<nbt::TagCompound>();
	{
		auto msValTag = std::make_unique<nbt::TagCompound>();
		{
			msValTag->get("max_inclusive") = std::make_unique<nbt::TagInt>(std::get<0>(monsterSpawnLightLevel));
			msValTag->get("min_inclusive") = std::make_unique<nbt::TagInt>(std::get<1>(monsterSpawnLightLevel));
			msTag->get("value") = std::move(msValTag);
		}

		msTag->get("max_inclusive") = std::make_unique<nbt::TagInt>(std::get<0>(monsterSpawnLightLevel));
		msTag->get("min_inclusive") = std::make_unique<nbt::TagInt>(std::get<1>(monsterSpawnLightLevel));
		msTag->get("type") = std::make_unique<nbt::TagString>(std::get<2>(monsterSpawnLightLevel));

		tag->get("monster_spawn_light_level") = std::move(msTag);
	}

	tag->set<nbt::TagString>("infiniburn", infiniburn);
	tag->set<nbt::TagByte>("has_raids", hasRaids);
	tag->set<nbt::TagByte>("ultrawarm", ultrawarm);
	tag->set<nbt::TagByte>("respawn_anchor_works", respawnAnchorWorks);
	tag->set<nbt::TagString>("effects", effects);
	tag->set<nbt::TagInt>("min_y", minY);
	tag->set<nbt::TagInt>("height", height);
	tag->set<nbt::TagByte>("piglin_safe", piglinSafe);
	tag->set<nbt::TagByte>("natural", natural);
	tag->set<nbt::TagInt>("logical_height", logicalHeight);
	tag->set<nbt::TagDouble>("coordinate_scale", coordinateScale);
	tag->set<nbt::TagByte>("has_skylight", hasSkylight);
	tag->set<nbt::TagByte>("bed_works", bedWorks);
	tag->set<nbt::TagByte>("has_ceiling", hasCeiling);

	return tag;
}

void acp::registry::DimensionType::deserialize(std::unique_ptr<nbt::Tag>& v)
{
	auto* tag = dynamic_cast<nbt::TagCompound*>(v.get());
	if (!tag)
		return;

	monsterSpawnBlockLightLimit = tag->get<int, nbt::TagInt>("monster_spawn_block_light_limit");
	ambientLight = tag->get<float, nbt::TagFloat>("ambient_light");

	if (auto* msTag = dynamic_cast<nbt::TagCompound*>(tag->get("monster_spawn_light_level").get()))
	{
		monsterSpawnLightLevel = std::make_tuple(
			msTag->get<int, nbt::TagInt>("min_inclusive"),
			msTag->get<int, nbt::TagInt>("max_inclusive"),
			msTag->get<std::string, nbt::TagString>("type")
		);
	}
	else if (const auto* msInt = dynamic_cast<nbt::TagInt*>(tag->get("monster_spawn_light_level").get()))
		monsterSpawnLightLevel = std::make_tuple(msInt->get(), msInt->get(), "");

	infiniburn = tag->get<std::string, nbt::TagString>("infiniburn");
	hasRaids = tag->get<bool, nbt::TagByte>("has_raids");
	ultrawarm = tag->get<bool, nbt::TagByte>("ultrawarm");
	respawnAnchorWorks = tag->get<bool, nbt::TagByte>("respawn_anchor_works");
	effects = tag->get<std::string, nbt::TagString>("effects");
	minY = tag->get<int, nbt::TagInt>("min_y");
	height = tag->get<int, nbt::TagInt>("height");
	piglinSafe = tag->get<bool, nbt::TagByte>("piglin_safe");
	natural = tag->get<bool, nbt::TagByte>("natural");
	logicalHeight = tag->get<int, nbt::TagInt>("logical_height");
	coordinateScale = tag->get<double, nbt::TagDouble>("coordinate_scale");
	hasSkylight = tag->get<bool, nbt::TagByte>("has_skylight");
	bedWorks = tag->get<bool, nbt::TagByte>("bed_works");
	hasCeiling = tag->get<bool, nbt::TagByte>("has_ceiling");
}


std::unique_ptr<acp::nbt::Tag> acp::registry::DimensionTypeEntry::serialize()
{
	auto tag = std::make_unique<nbt::TagCompound>();

	tag->set<nbt::TagInt>("id", id);
	tag->set("element", type.serialize());
	tag->set<nbt::TagString>("name", name);

	return tag;
}

void acp::registry::DimensionTypeEntry::deserialize(std::unique_ptr<nbt::Tag>& v)
{
	auto* tag = dynamic_cast<nbt::TagCompound*>(v.get());
	if (!tag)
		return;

	id = tag->get<int, nbt::TagInt>("id");
	type.deserialize(tag->get("element"));
	name = tag->get<std::string, nbt::TagString>("name");
}
