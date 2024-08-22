#include "style.hh"

#include "util/nbt/tag/tag_compound.hh"
#include "util/nbt/tag/tag_number.hh"
#include "util/nbt/tag/tag_string.hh"

std::unique_ptr<acp::nbt::TagCompound> acp::text::Style::serialize()
{
	auto tag = std::make_unique<nbt::TagCompound>();

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
		tag->set("clickEvent", clickEvent->serialize());

	if (hoverEvent.has_value())
		tag->set("hoverEvent", hoverEvent->serialize());

	return tag;
}

void acp::text::Style::deserialize(std::unique_ptr<nbt::TagCompound>& v)
{
	if (v->contains("color"))
		color = v->get<std::string, nbt::TagString>("color");

	if (v->contains("bold"))
		bold = v->get<bool, nbt::TagByte>("bold");

	if (v->contains("italic"))
		italic = v->get<bool, nbt::TagByte>("italic");

	if (v->contains("underlined"))
		underlined = v->get<bool, nbt::TagByte>("underlined");

	if (v->contains("strikethrough"))
		strikethrough = v->get<bool, nbt::TagByte>("strikethrough");

	if (v->contains("obfuscated"))
		obfuscated = v->get<bool, nbt::TagByte>("obfuscated");

	if (v->contains("font"))
		font = v->get<std::string, nbt::TagString>("font");

	if (v->contains("insertion"))
		insertion = v->get<std::string, nbt::TagString>("insertion");

	// TODO fuckin unique_ptr wont cast
	// if (v->get().contains("clickEvent"))
	// {
	// 	ClickEvent event;
	// 	const auto& tag = v->get()["clickEvent"];
	// 	event.deserialize();
	// }
}
