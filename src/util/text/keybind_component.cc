#include "keybind_component.hh"

#include "util/nbt/tag/tag_compound.hh"
#include "util/nbt/tag/tag_string.hh"

acp::text::KeybindComponent::KeybindComponent(const std::string& keybind): keybind(keybind)
{
}

std::unique_ptr<acp::nbt::TagCompound> acp::text::KeybindComponent::serialize()
{
	auto tag = Component::serialize();

	tag->get()["keybind"] = std::make_unique<nbt::TagString>(keybind);

	return tag;
}

const std::string& acp::text::KeybindComponent::getKeybind() const
{
	return keybind;
}

void acp::text::KeybindComponent::setKeybind(const std::string& keybind)
{
	this->keybind = keybind;
}

const acp::text::Type* acp::text::KeybindComponent::getType()
{
	return &Type::KEYBIND;
}
