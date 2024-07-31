#include "hover_event.hh"

#include "util/nbt/tag/tag_compound.hh"
#include "util/nbt/tag/tag_string.hh"

#include <unordered_map>

static std::unordered_map<std::string, acp::text::HoverEvent::Action*> actionsByName;

acp::text::HoverEvent::Action::Action(int id, const std::string& name): id(id), name(name)
{
	actionsByName[name] = this;
}

const std::string& acp::text::HoverEvent::Action::getName() const
{
	return name;
}

bool acp::text::HoverEvent::Action::operator==(const Action& rhs) const
{
	return id == rhs.id;
}

bool acp::text::HoverEvent::Action::operator!=(const Action& rhs) const
{
	return !(*this == rhs);
}


acp::text::HoverEvent::Action* acp::text::HoverEvent::Action::byName(const std::string& name)
{
	return actionsByName.contains(name) ? actionsByName[name] : nullptr;
}

const acp::text::HoverEvent::Action acp::text::HoverEvent::Action::SHOW_TEXT = { 0, "show_text" };
const acp::text::HoverEvent::Action acp::text::HoverEvent::Action::SHOW_ITEM = { 1, "show_item" };
const acp::text::HoverEvent::Action acp::text::HoverEvent::Action::SHOW_ENTITY = { 2, "show_entity" };


acp::text::HoverEvent::HoverEvent(const Action& action, const std::string& contents): action(&action), contents(contents)
{
}

std::unique_ptr<acp::nbt::TagCompound> acp::text::HoverEvent::serialize()
{
	auto tag = std::make_unique<nbt::TagCompound>();
	tag->get()["action"] = std::make_unique<nbt::TagString>(action->getName());
	tag->get()["contents"] = std::make_unique<nbt::TagString>(contents);

	return tag;
}

void acp::text::HoverEvent::deserialize(std::unique_ptr<nbt::TagCompound>& v)
{
	if (v->get().contains("action"))
	{
		nbt::Tag* tag = v->get()["action"].get();
		if (const auto* actionTag = dynamic_cast<nbt::TagString*>(tag))
			action = Action::byName(actionTag->get());
	}

	if (v->get().contains("contents"))
	{
		nbt::Tag* tag = v->get()["contents"].get();
		if (const auto* contentsTag = dynamic_cast<nbt::TagString*>(tag))
			contents = contentsTag->get();
	}
}
