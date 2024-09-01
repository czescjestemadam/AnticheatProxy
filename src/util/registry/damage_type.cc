#include "damage_type.hh"

#include "util/nbt/tag/tag_compound.hh"
#include "util/nbt/tag/tag_number.hh"
#include "util/nbt/tag/tag_string.hh"

std::unique_ptr<acp::nbt::Tag> acp::registry::DamageType::serialize()
{
	auto tag = std::make_unique<nbt::TagCompound>();

	if (!deathMessageType.empty())
		tag->set<nbt::TagString>("death_message_type", deathMessageType);

	if (!effects.empty())
		tag->set<nbt::TagString>("effects", effects);

	tag->set<nbt::TagFloat>("exhaustion", exhaustion);
	tag->set<nbt::TagString>("message_id", messageId);
	tag->set<nbt::TagString>("scaling", scaling);

	return tag;
}

void acp::registry::DamageType::deserialize(std::unique_ptr<nbt::Tag>& v)
{
	auto* tag = dynamic_cast<nbt::TagCompound*>(v.get());
	if (!tag)
		return;

	if (tag->contains("death_message_type"))
		deathMessageType = tag->get<std::string, nbt::TagString>("death_message_type");

	if (tag->contains("effects"))
		deathMessageType = tag->get<std::string, nbt::TagString>("effects");

	exhaustion = tag->get<float, nbt::TagFloat>("exhaustion");
	messageId = tag->get<std::string, nbt::TagString>("message_id");
	scaling = tag->get<std::string, nbt::TagString>("scaling");
}


acp::registry::DamageTypeEntry::DamageTypeEntry(int id, const DamageType& type, const std::string& name)
	: id(id), type(type), name(name)
{
}

std::unique_ptr<acp::nbt::Tag> acp::registry::DamageTypeEntry::serialize()
{
	auto tag = std::make_unique<nbt::TagCompound>();

	tag->set<nbt::TagInt>("id", id);
	tag->set("element", type.serialize());
	tag->set<nbt::TagString>("name", name);

	return tag;
}

void acp::registry::DamageTypeEntry::deserialize(std::unique_ptr<nbt::Tag>& v)
{
	auto* tag = dynamic_cast<nbt::TagCompound*>(v.get());
	if (!tag)
		return;

	id = tag->get<int, nbt::TagInt>("id");
	type.deserialize(tag->get("element"));
	name = tag->get<std::string, nbt::TagString>("name");
}
