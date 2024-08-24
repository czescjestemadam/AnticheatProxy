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

void acp::text::TextComponent::serialize(std::unique_ptr<nbt::Tag>& v)
{
	Component::serialize(v);
	if (auto* compound = dynamic_cast<nbt::TagCompound*>(v.get()))
		compound->set<nbt::TagString>("text", text);
}

void acp::text::TextComponent::deserialize(std::unique_ptr<nbt::Tag>& v)
{
	Component::deserialize(v);
	if (auto* compound = dynamic_cast<nbt::TagCompound*>(v.get()))
		text = compound->get<std::string, nbt::TagString>(compound->contains("text") ? "text" : "");
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
