#include "keybind_component.hh"

#include "util/nbt/tag/tag_compound.hh"
#include "util/nbt/tag/tag_string.hh"

acp::text::KeybindComponent::KeybindComponent(const std::string& keybind) : keybind(keybind)
{
}

acp::text::KeybindComponent::KeybindComponent(KeybindComponent& component) : keybind(component.keybind)
{
	style = component.style;
	for (const std::unique_ptr<Component>& e : component.extra)
		extra.push_back(e->copy());
}

void acp::text::KeybindComponent::serialize(std::unique_ptr<nbt::Tag>& v)
{
	Component::serialize(v);
	if (auto* compound = dynamic_cast<nbt::TagCompound*>(v.get()))
		compound->set<nbt::TagString>("keybind", keybind);
}

void acp::text::KeybindComponent::deserialize(std::unique_ptr<nbt::Tag>& v)
{
	Component::deserialize(v);
	if (auto* compound = dynamic_cast<nbt::TagCompound*>(v.get()))
		keybind = compound->get<std::string, nbt::TagString>("keybind");
}

std::unique_ptr<acp::text::Component> acp::text::KeybindComponent::copy()
{
	return std::make_unique<KeybindComponent>(*this);
}

const std::string& acp::text::KeybindComponent::getKeybind() const
{
	return keybind;
}

void acp::text::KeybindComponent::setKeybind(const std::string& keybind)
{
	this->keybind = keybind;
}

const acp::text::Type& acp::text::KeybindComponent::getType() const
{
	return Type::KEYBIND;
}
