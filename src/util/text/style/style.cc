#include "style.hh"

#include "util/nbt/tag/tag_compound.hh"
#include "util/nbt/tag/tag_number.hh"
#include "util/nbt/tag/tag_string.hh"
#include "util/text/io/io_tag.hh"

std::vector<const acp::text::IOTag*> acp::text::Style::getIOTags() const
{
	std::vector<const IOTag*> tags;

	if (!color.empty())
	{
		if (const IOTag* tag = IOTag::byMinimessageCode(color))
			tags.push_back(tag);
	}

	if (bold.has_value())
		tags.push_back(&IOTag::BOLD);

	if (italic.has_value())
		tags.push_back(&IOTag::ITALIC);

	if (underlined.has_value())
		tags.push_back(&IOTag::UNDERLINED);

	if (strikethrough.has_value())
		tags.push_back(&IOTag::STRIKETHROUGH);

	if (obfuscated.has_value())
		tags.push_back(&IOTag::OBFUSCATED);

	return tags;
}

std::vector<acp::text::IOTag> acp::text::Style::getCustomIOTags() const
{
	std::vector<IOTag> tags;

	if (!color.empty() && !IOTag::byMinimessageCode(color))
		tags.emplace_back(color);

	return tags;
}

void acp::text::Style::serialize(std::unique_ptr<nbt::Tag>& v)
{
	if (auto* tag = dynamic_cast<nbt::TagCompound*>(v.get()))
	{
		if (!color.empty())
			tag->set<nbt::TagString>("color", color);

		if (bold.has_value())
			tag->set<nbt::TagByte>("bold", bold.value());

		if (italic.has_value())
			tag->set<nbt::TagByte>("italic", italic.value());

		if (underlined.has_value())
			tag->set<nbt::TagByte>("underlined", underlined.value());

		if (strikethrough.has_value())
			tag->set<nbt::TagByte>("strikethrough", strikethrough.value());

		if (obfuscated.has_value())
			tag->set<nbt::TagByte>("obfuscated", obfuscated.value());

		if (!font.empty())
			tag->set<nbt::TagString>("font", font);

		if (!insertion.empty())
			tag->set<nbt::TagString>("insertion", insertion);

		if (clickEvent.has_value())
		{
			std::unique_ptr<nbt::Tag> eventTag = std::make_unique<nbt::TagCompound>();
			clickEvent->serialize(eventTag);
			tag->set("clickEvent", std::move(eventTag));
		}

		if (hoverEvent.has_value())
		{
			std::unique_ptr<nbt::Tag> eventTag = std::make_unique<nbt::TagCompound>();
			hoverEvent->serialize(eventTag);
			tag->set("hoverEvent", std::move(eventTag));
		}
	}
}

void acp::text::Style::deserialize(std::unique_ptr<nbt::Tag>& v)
{
	if (auto* tag = dynamic_cast<nbt::TagCompound*>(v.get()))
	{
		if (tag->contains("color"))
			color = tag->get<std::string, nbt::TagString>("color");

		if (tag->contains("bold"))
			bold = tag->get<bool, nbt::TagByte>("bold");

		if (tag->contains("italic"))
			italic = tag->get<bool, nbt::TagByte>("italic");

		if (tag->contains("underlined"))
			underlined = tag->get<bool, nbt::TagByte>("underlined");

		if (tag->contains("strikethrough"))
			strikethrough = tag->get<bool, nbt::TagByte>("strikethrough");

		if (tag->contains("obfuscated"))
			obfuscated = tag->get<bool, nbt::TagByte>("obfuscated");

		if (tag->contains("font"))
			font = tag->get<std::string, nbt::TagString>("font");

		if (tag->contains("insertion"))
			insertion = tag->get<std::string, nbt::TagString>("insertion");

		if (tag->contains("clickEvent"))
		{
			clickEvent = ClickEvent{};
			clickEvent->deserialize(tag->get("clickEvent"));
		}

		if (tag->contains("hoverEvent"))
		{
			hoverEvent = HoverEvent{};
			hoverEvent->deserialize(tag->get("hoverEvent"));
		}
	}
}
