#include "component.hh"

#include "text_component.hh"
#include "util/nbt/tag/tag_list.hh"
#include "util/nbt/tag/tag_string.hh"

std::unique_ptr<acp::nbt::TagCompound> acp::text::Component::serialize()
{
	auto tag = style.serialize();

	auto extraTag = std::make_unique<nbt::TagList>();
	for (const std::unique_ptr<Component>& component : extra)
		extraTag->get().push_back(component->serialize());

	return tag;
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


std::unique_ptr<acp::text::Component> acp::text::Component::fromNbt(std::unique_ptr<nbt::Tag> tag)
{
	if (tag->getType() == nbt::TagType::STRING)
	{
		const auto strTag = dynamic_cast<nbt::TagString*>(tag.get());
		return std::make_unique<TextComponent>(strTag->get());
	}

	// TODO get by checking if contains field for components
	// TODO deserializer in ISerializable
	return std::make_unique<TextComponent>("nullptr");
}
