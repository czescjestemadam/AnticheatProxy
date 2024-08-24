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


acp::text::HoverEvent::HoverEvent(const HoverEvent& event) : action(event.action), contents(event.contents->copy())
{
}

acp::text::HoverEvent::HoverEvent(HoverEvent&& event) noexcept : action(event.action), contents(std::move(event.contents))
{
}

acp::text::HoverEvent::HoverEvent(const Action& action, std::unique_ptr<nbt::Tag>&& contents) : action(&action), contents(std::move(contents))
{
}

void acp::text::HoverEvent::serialize(std::unique_ptr<nbt::Tag>& v)
{
	if (auto* tag = dynamic_cast<nbt::TagCompound*>(v.get()))
	{
		tag->set<nbt::TagString>("action", action->getName());
		tag->set("contents", contents->copy());
	}
}

void acp::text::HoverEvent::deserialize(std::unique_ptr<nbt::Tag>& v)
{
	if (auto* tag = dynamic_cast<nbt::TagCompound*>(v.get()))
	{
		if (tag->contains("action"))
			action = Action::byName(tag->get<std::string, nbt::TagString>("action"));

		if (tag->contains("contents"))
			contents = tag->get("contents")->copy();
	}
}

acp::text::HoverEvent& acp::text::HoverEvent::operator=(const HoverEvent& other)
{
	if (this == &other)
		return *this;
	action = other.action;
	contents = other.contents->copy();
	return *this;
}

acp::text::HoverEvent& acp::text::HoverEvent::operator=(HoverEvent&& other) noexcept
{
	if (this == &other)
		return *this;
	action = other.action;
	contents = std::move(other.contents);
	return *this;
}
