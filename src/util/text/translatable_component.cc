#include "translatable_component.hh"

#include "util/nbt/tag/tag_compound.hh"
#include "util/nbt/tag/tag_list.hh"
#include "util/nbt/tag/tag_string.hh"

acp::text::TranslatableComponent::TranslatableComponent(const std::string& key) : key(key)
{
}

std::unique_ptr<acp::nbt::TagCompound> acp::text::TranslatableComponent::serialize()
{
	auto tag = Component::serialize();

	tag->get()["translate"] = std::make_unique<nbt::TagString>(key);

	auto withTag = std::make_unique<nbt::TagList>();
	for (const std::unique_ptr<TextComponent>& component : with)
		withTag->get().push_back(component->serialize());

	tag->get()["with"] = std::move(withTag);

	return tag;
}

const std::string& acp::text::TranslatableComponent::getKey() const
{
	return key;
}

void acp::text::TranslatableComponent::setKey(const std::string& key)
{
	this->key = key;
}

std::vector<std::unique_ptr<acp::text::TextComponent>>& acp::text::TranslatableComponent::getWith()
{
	return with;
}

const std::vector<std::unique_ptr<acp::text::TextComponent>>& acp::text::TranslatableComponent::getWith() const
{
	return with;
}

void acp::text::TranslatableComponent::setWith(std::vector<std::unique_ptr<TextComponent>>&& with)
{
	this->with = std::move(with);
}

const acp::text::Type* acp::text::TranslatableComponent::getType()
{
	return &Type::TRANSLATABLE;
}
