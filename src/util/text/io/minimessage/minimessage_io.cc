#include "minimessage_io.hh"

#include "util/text/keybind_component.hh"
#include "util/text/text_component.hh"
#include "util/text/translatable_component.hh"
#include "util/text/io/io_tag.hh"

std::unique_ptr<acp::text::Component> acp::text::MinimessageIO::parse(const std::string& str) const
{
	std::unique_ptr<Component> component = std::make_unique<TextComponent>();

	std::vector<const IOTag*> tags;
	std::vector<IOTag> customTags;
	std::string text;

	const auto appendExtra = [&]
	{
		if (!text.empty())
		{
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

	bool insideTag = false;
	std::string tagCode;
	for (int i = 0; i < str.length(); ++i)
	{
		const char c = str[i];
		if (c == '<')
		{
			if (insideTag)
			{
				text += "<" + tagCode;
				tagCode.clear();
			}

			insideTag = true;
		}
		else if (c == '>' && insideTag)
		{
			if (const IOTag* tag = IOTag::byMinimessageCode(tagCode))
			{
				if (tag->isReset())
					appendExtra();

				tags.push_back(tag);
			}
			else if (tagCode.starts_with('#') && tagCode.length() == 7)
			{
				const IOTag hexTag(tagCode);

				if (hexTag.isReset())
					appendExtra();

				customTags.emplace_back(hexTag);
			}
			else
				text += "<" + tagCode + ">";

			insideTag = false;
			tagCode.clear();
		}
		else
			(insideTag ? tagCode : text) += c;
	}

	appendExtra();

	return component;
}

std::string acp::text::MinimessageIO::write(const std::unique_ptr<Component>& component) const
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
					str += "<" + IOTag::RESET.getMiniMessageCode() + ">";
				else
				{
					for (const auto& tag : customTags)
						str += "<" + tag.getMiniMessageCode() + ">";

					for (const auto& tag : tags)
						str += "<" + tag->getMiniMessageCode() + ">";
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
