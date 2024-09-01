#include "legacy_io.hh"

#include "util/str_utils.hh"
#include "util/text/keybind_component.hh"
#include "util/text/text_component.hh"
#include "util/text/translatable_component.hh"
#include "util/text/io/io_tag.hh"

std::unique_ptr<acp::text::Component> acp::text::LegacyIO::parse(const std::string& str, char prefix) const
{
	std::string from;
	from += prefix;
	from += IOTag::NEWLINE.getLegacyCode();
	std::string newlinedStr = StrUtils::replaced(str, from, "\n");

	std::unique_ptr<Component> component = std::make_unique<TextComponent>();

	std::vector<const IOTag*> tags;
	std::vector<IOTag> customTags; // rgb hex only
	std::string text;

	const auto appendExtra = [&]
	{
		if (!text.empty())
		{

			StrUtils::replace(text, from, "\n");

			std::unique_ptr<Component> extra = std::make_unique<TextComponent>(text);
			for (const IOTag* t : tags)
				t->apply(extra->getStyle());

			for (const IOTag& t : customTags)
				t.apply(extra->getStyle());

			component->getExtra().push_back(std::move(extra));
		}

		tags.clear();
		customTags.clear();
		text.clear();
	};

	for (int i = 0; i < newlinedStr.length(); ++i)
	{
		const char c = newlinedStr[i];
		if (c == prefix && i + 1 < newlinedStr.length())
		{
			const char code = newlinedStr[++i];
			if (code == prefix) // parse && as &
				text += prefix;
			else if (code == '#' && i + 6 < newlinedStr.length())
			{
				const std::string hexCode = newlinedStr.substr(i, 7);
				i += 6;
				const IOTag tag(hexCode);

				if (tag.isReset())
					appendExtra();

				customTags.push_back(tag);
			}
			else if (const IOTag* tag = IOTag::byLegacyCode(code))
			{
				if (tag->isReset())
					appendExtra();

				tags.push_back(tag);
			}
			else
			{
				text += c;
				text += code;
			}
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
				const std::vector<const IOTag*> tags = textComponent->getStyle().getIOTags();
				const std::vector<IOTag> customTags = textComponent->getStyle().getCustomIOTags(); // rgb hex only
				if (tags.empty() && customTags.empty() && !str.empty())
				{
					str += prefix;
					str += IOTag::RESET.getLegacyCode();
				}
				else
				{
					for (const auto& tag : customTags)
					{
						str += prefix;
						str += tag.getMiniMessageCode();
					}

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

	std::string to;
	to += prefix;
	to += IOTag::NEWLINE.getLegacyCode();
	return StrUtils::replaced(str, "\n", to);
}

std::string acp::text::LegacyIO::write(const std::unique_ptr<Component>& component) const
{
	return write(component, '&');
}
