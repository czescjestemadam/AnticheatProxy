#include "plaintext_io.hh"

#include "util/text/keybind_component.hh"
#include "util/text/text_component.hh"
#include "util/text/translatable_component.hh"

std::unique_ptr<acp::text::Component> acp::text::PlaintextIO::parse(const std::string& str) const
{
	return std::make_unique<TextComponent>(str);
}

std::string acp::text::PlaintextIO::write(const std::unique_ptr<Component>& component) const
{
	std::string str;

	if (component->getType() == Type::TEXT)
	{
		if (const auto textComponent = dynamic_cast<TextComponent*>(component.get()))
		{
			str += textComponent->getText();

			for (const auto& extra : textComponent->getExtra())
				str += write(extra);
		}
	}
	else if (component->getType() == Type::TRANSLATABLE)
	{
		if (const auto translatableComponent = dynamic_cast<TranslatableComponent*>(component.get()))
		{
			str += translatableComponent->getKey();
		}
	}
	else if (component->getType() == Type::KEYBIND)
	{
		if (const auto keybindComponent = dynamic_cast<KeybindComponent*>(component.get()))
		{
			str += keybindComponent->getKeybind();
		}
	}

	return str;
}
