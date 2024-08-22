#include "text_component.hh"

#include "util/nbt/tag/tag_compound.hh"
#include "util/nbt/tag/tag_string.hh"

acp::text::TextComponent::TextComponent(const std::string& text): text(text)
{
}

acp::text::TextComponent::TextComponent(TextComponent& component) : text(component.text)
{
	style = component.style;
	for (const std::unique_ptr<Component>& e : component.extra)
		extra.push_back(e->copy());
}

std::unique_ptr<acp::nbt::TagCompound> acp::text::TextComponent::serialize()
{
	auto tag = Component::serialize();

	tag->get()["text"] = std::make_unique<nbt::TagString>(text);

	return tag;
}

std::unique_ptr<acp::text::Component> acp::text::TextComponent::copy()
{
	return std::make_unique<TextComponent>(*this);
}

std::string& acp::text::TextComponent::getText()
{
	return text;
}

const std::string& acp::text::TextComponent::getText() const
{
	return text;
}

void acp::text::TextComponent::setText(const std::string& text)
{
	this->text = text;
}

const acp::text::Type& acp::text::TextComponent::getType() const
{
	return Type::TEXT;
}
