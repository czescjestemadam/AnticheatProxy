#include "terminal_io.hh"

#include "util/terminal/format.hh"
#include "util/text/keybind_component.hh"
#include "util/text/text_component.hh"
#include "util/text/translatable_component.hh"
#include "util/text/io/io_tag.hh"

std::unique_ptr<acp::text::Component> acp::text::TerminalIO::parse(const std::string& str) const
{
	throw std::runtime_error("TerminalIO::parse is unsuported");
}

std::string acp::text::TerminalIO::write(const std::unique_ptr<Component>& component) const
{
	std::string str;

	if (component->getType() == Type::TEXT)
	{
		if (const auto textComponent = dynamic_cast<TextComponent*>(component.get()))
		{
			if (!textComponent->getText().empty())
			{
				const std::vector<const IOTag*> tags = textComponent->getStyle().getIOTags();
				const std::vector<IOTag> customTags = textComponent->getStyle().getCustomIOTags();
				if (tags.empty() && customTags.empty() && !str.empty())
					str += terminal::Format::RESET.toString();
				else
				{
					for (const auto& tag : customTags)
						str += tag.getTerminalFormat().toString();

					for (const auto& tag : tags)
						str += tag->getTerminalFormat().toString();
				}

				str += textComponent->getText();
			}

			for (const auto& extra : textComponent->getExtra())
				str += write(extra);
		}
	}
	else if (component->getType() == Type::TRANSLATABLE)
	{
		if (const auto translatableComponent = dynamic_cast<TranslatableComponent*>(component.get()))
		{
			str += translatableComponent->getKey() + ": ";

			const auto& with = translatableComponent->getWith();
			for (int i = 0; i < with.size(); ++i)
			{
				str += write(with[i]->copy());

				if (i + 1 < with.size())
					str += ", ";
			}

			str += "; extra: ";
			for (const auto& extra : translatableComponent->getExtra())
				str += write(extra);
		}
	}
	else if (component->getType() == Type::KEYBIND)
	{
		if (const auto keybindComponent = dynamic_cast<KeybindComponent*>(component.get()))
		{
			str += keybindComponent->getKeybind();

			str += "; extra: ";
			for (const auto& extra : keybindComponent->getExtra())
				str += write(extra);
		}
	}

	return str;
}
