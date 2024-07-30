#include "text_component.hh"

#include "util/nbt/tag/tag_compound.hh"
#include "util/nbt/tag/tag_string.hh"

acp::text::TextComponent::TextComponent(const std::string& text): text(text)
{
}

std::unique_ptr<acp::nbt::TagCompound> acp::text::TextComponent::serialize()
{
	auto tag = Component::serialize();

	tag->get()["text"] = std::make_unique<nbt::TagString>(text);

	return tag;
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

const acp::text::Type* acp::text::TextComponent::getType()
{
	return &Type::TEXT;
}
