#include "translatable_component.hh"

#include "util/nbt/tag/tag_compound.hh"
#include "util/nbt/tag/tag_list.hh"
#include "util/nbt/tag/tag_string.hh"

acp::text::TranslatableComponent::TranslatableComponent(const std::string& key) : key(key)
{
}

acp::text::TranslatableComponent::TranslatableComponent(TranslatableComponent& component) : key(component.key)
{
	style = component.style;
	for (const std::unique_ptr<Component>& e : component.extra)
		extra.push_back(e->copy());

	for (const std::unique_ptr<Component>& e : component.with)
		with.push_back(e->copy());
}

void acp::text::TranslatableComponent::serialize(std::unique_ptr<nbt::Tag>& v)
{
	Component::serialize(v);

	if (auto* compound = dynamic_cast<nbt::TagCompound*>(v.get()))
	{
		compound->set<nbt::TagString>("translate", key);

		auto withTag = std::make_unique<nbt::TagList>();
		for (const std::unique_ptr<Component>& component : with)
		{
			std::unique_ptr<nbt::Tag> withTagEntry = std::make_unique<nbt::TagCompound>();
			component->serialize(withTagEntry);
			withTag->get().push_back(std::move(withTagEntry));
		}
		compound->set("with", std::move(withTag));
	}
}

void acp::text::TranslatableComponent::deserialize(std::unique_ptr<nbt::Tag>& v)
{
	Component::deserialize(v);

	if (auto* compound = dynamic_cast<nbt::TagCompound*>(v.get()))
	{
		key = compound->get<std::string, nbt::TagString>("translate");

		if (compound->contains("with"))
		{
			if (auto* withTag = dynamic_cast<nbt::TagList*>(compound->get("with").get()))
			{
				for (std::unique_ptr<nbt::Tag>& withTagEntry : withTag->get())
					with.push_back(fromNbt(withTagEntry));
			}
		}
	}
}

std::unique_ptr<acp::text::Component> acp::text::TranslatableComponent::copy()
{
	return std::make_unique<TranslatableComponent>(*this);
}

const std::string& acp::text::TranslatableComponent::getKey() const
{
	return key;
}

void acp::text::TranslatableComponent::setKey(const std::string& key)
{
	this->key = key;
}

std::vector<std::unique_ptr<acp::text::Component>>& acp::text::TranslatableComponent::getWith()
{
	return with;
}

const std::vector<std::unique_ptr<acp::text::Component>>& acp::text::TranslatableComponent::getWith() const
{
	return with;
}

void acp::text::TranslatableComponent::setWith(std::vector<std::unique_ptr<Component>>&& with)
{
	this->with = std::move(with);
}

const acp::text::Type& acp::text::TranslatableComponent::getType() const
{
	return Type::TRANSLATABLE;
}
