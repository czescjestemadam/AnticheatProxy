#include "legacy_io.hh"

#include "util/text/keybind_component.hh"
#include "util/text/text_component.hh"
#include "util/text/translatable_component.hh"
#include "util/text/io/io_tag.hh"

std::unique_ptr<acp::text::Component> acp::text::LegacyIO::parse(const std::string& str, char prefix) const
{
	return nullptr;
}

std::unique_ptr<acp::text::Component> acp::text::LegacyIO::parse(const std::string& str) const
{
	return parse(str, '&');
}

std::string acp::text::LegacyIO::write(const std::unique_ptr<Component>& component, char prefix) const
{
	std::string str;

	if (component->getType() == Type::TEXT)
	{
		if (const auto textComponent = dynamic_cast<TextComponent*>(component.get()))
		{
			for (const auto& tag : textComponent->getStyle().getIOTags())
			{
				str += prefix;
				str += tag->getLegacyCode();
			}
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

std::string acp::text::LegacyIO::write(const std::unique_ptr<Component>& component) const
{
	return write(component, '&');
}
