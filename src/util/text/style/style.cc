#include "style.hh"

#include "util/nbt/tag/tag_compound.hh"
#include "util/nbt/tag/tag_number.hh"
#include "util/nbt/tag/tag_string.hh"

std::unique_ptr<acp::nbt::TagCompound> acp::text::Style::serialize()
{
	auto tag = std::make_unique<nbt::TagCompound>();

	if (!color.empty())
		tag->get()["color"] = std::make_unique<nbt::TagString>(color);

	if (bold.has_value())
		tag->get()["bold"] = std::make_unique<nbt::TagByte>(bold.value());

	if (italic.has_value())
		tag->get()["italic"] = std::make_unique<nbt::TagByte>(italic.value());

	if (underlined.has_value())
		tag->get()["underlined"] = std::make_unique<nbt::TagByte>(underlined.value());

	if (strikethrough.has_value())
		tag->get()["strikethrough"] = std::make_unique<nbt::TagByte>(strikethrough.value());

	if (obfuscated.has_value())
		tag->get()["obfuscated"] = std::make_unique<nbt::TagByte>(obfuscated.value());

	if (!font.empty())
		tag->get()["font"] = std::make_unique<nbt::TagString>(font);

	if (!insertion.empty())
		tag->get()["insertion"] = std::make_unique<nbt::TagString>(insertion);

	if (clickEvent.has_value())
		tag->get()["clickEvent"] = clickEvent->serialize();

	if (hoverEvent.has_value())
		tag->get()["hoverEvent"] = hoverEvent->serialize();

	return tag;
}
