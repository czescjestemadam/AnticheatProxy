#include "component.hh"

#include "keybind_component.hh"
#include "text_component.hh"
#include "translatable_component.hh"
#include "util/nbt/tag/tag_list.hh"
#include "util/nbt/tag/tag_string.hh"

void acp::text::Component::serialize(std::unique_ptr<nbt::Tag>& v)
{
	style.serialize(v);

	if (!extra.empty())
	{
		if (auto* compound = dynamic_cast<nbt::TagCompound*>(v.get()))
		{
			auto extraTag = std::make_unique<nbt::TagList>();
			for (const std::unique_ptr<Component>& component : extra)
			{
				std::unique_ptr<nbt::Tag> extraTagEntry = std::make_unique<nbt::TagCompound>();
				component->serialize(extraTagEntry);
				extraTag->get().push_back(std::move(extraTagEntry));
			}
			compound->set("extra", std::move(extraTag));
		}
	}
}

void acp::text::Component::deserialize(std::unique_ptr<nbt::Tag>& v)
{
	style.deserialize(v);

	if (auto* compound = dynamic_cast<nbt::TagCompound*>(v.get()))
	{
		if (compound->contains("extra"))
		{
			if (auto* extraTag = dynamic_cast<nbt::TagList*>(compound->get("extra").get()))
			{
				for (std::unique_ptr<nbt::Tag>& extraTagEntry : extraTag->get())
					extra.push_back(fromNbt(extraTagEntry));
			}
		}
	}
}

acp::text::Style& acp::text::Component::getStyle()
{
	return style;
}

const acp::text::Style& acp::text::Component::getStyle() const
{
	return style;
}

void acp::text::Component::setStyle(const Style& style)
{
	this->style = style;
}

std::vector<std::unique_ptr<acp::text::Component>>& acp::text::Component::getExtra()
{
	return extra;
}

const std::vector<std::unique_ptr<acp::text::Component>>& acp::text::Component::getExtra() const
{
	return extra;
}

void acp::text::Component::setExtra(std::vector<std::unique_ptr<Component>>&& extra)
{
	this->extra = std::move(extra);
}


std::unique_ptr<acp::nbt::Tag> acp::text::Component::toNbt(std::unique_ptr<Component>&& component)
{
	return toNbt(component);
}

std::unique_ptr<acp::nbt::Tag> acp::text::Component::toNbt(std::unique_ptr<Component>& component)
{
	std::unique_ptr<nbt::Tag> tag = std::make_unique<nbt::TagCompound>();
	component->serialize(tag);
	return tag;
}

std::unique_ptr<acp::text::Component> acp::text::Component::fromNbt(std::unique_ptr<nbt::Tag>&& tag)
{
	return fromNbt(tag);
}

std::unique_ptr<acp::text::Component> acp::text::Component::fromNbt(std::unique_ptr<nbt::Tag>& tag)
{
	if (tag->getType() == nbt::TagType::STRING)
	{
		const auto strTag = dynamic_cast<nbt::TagString*>(tag.get());
		return std::make_unique<TextComponent>(strTag->get());
	}

	if (tag->getType() == nbt::TagType::COMPOUND)
	{
		if (const nbt::TagCompound* compound = dynamic_cast<nbt::TagCompound*>(tag.get()))
		{
			std::unique_ptr<Component> component;
			if (compound->contains("text") || compound->contains(""))
				component = std::make_unique<TextComponent>();
			else if (compound->contains("translate"))
				component = std::make_unique<TranslatableComponent>();
			else if (compound->contains("keybind"))
				component = std::make_unique<KeybindComponent>();
			else
				throw std::invalid_argument("component type of " + tag->toString() + " is not supported");

			component->deserialize(tag);
			return component;
		}
	}

	throw std::invalid_argument("tag type must be STRING or COMPOUND");
}
