#include "legacy_io.hh"

#include "util/text/keybind_component.hh"
#include "util/text/text_component.hh"
#include "util/text/translatable_component.hh"
#include "util/text/io/io_tag.hh"

std::unique_ptr<acp::text::Component> acp::text::LegacyIO::parse(const std::string& str, char prefix) const
{
	std::unique_ptr<Component> component = std::make_unique<TextComponent>();

	std::vector<const IOTag*> tags;
	std::string text;

	const auto appendExtra = [&]
	{
		if (!text.empty())
		{
			std::unique_ptr<Component> extra = std::make_unique<TextComponent>(text);
			for (const IOTag* t : tags)
				t->apply(extra->getStyle());

			component->getExtra().push_back(std::move(extra));
		}

		tags.clear();
		text.clear();
	};

	for (int i = 0; i < str.length(); ++i)
	{
		const char c = str[i];
		if (c == prefix && i + 1 < str.length())
		{
			const char code = str[++i];
			if (code == prefix) // parse && as &
				text += prefix;
			else if (const IOTag* tag = IOTag::byLegacyCode(code))
			{
				if (tag->isReset())
					appendExtra();

				tags.push_back(tag);
			}
			else
				text += code;
		}
		else
			text += c;
	}

	appendExtra();

	return component;
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
			if (!textComponent->getText().empty())
			{
				const auto& tags = textComponent->getStyle().getIOTags();
				if (tags.empty() && !str.empty())
				{
					str += prefix;
					str += IOTag::RESET.getLegacyCode();
				}
				else
				{
					for (const auto& tag : tags)
					{
						str += prefix;
						str += tag->getLegacyCode();
					}
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
