#include "click_event.hh"

#include "util/nbt/tag/tag_compound.hh"
#include "util/nbt/tag/tag_string.hh"

#include <unordered_map>

static std::unordered_map<std::string, acp::text::ClickEvent::Action*> actionsByName;

acp::text::ClickEvent::Action::Action(int id, const std::string& name): id(id), name(name)
{
	actionsByName[name] = this;
}

const std::string& acp::text::ClickEvent::Action::getName() const
{
	return name;
}

bool acp::text::ClickEvent::Action::operator==(const Action& rhs) const
{
	return id == rhs.id;
}

bool acp::text::ClickEvent::Action::operator!=(const Action& rhs) const
{
	return !(*this == rhs);
}


acp::text::ClickEvent::Action* acp::text::ClickEvent::Action::byName(const std::string& name)
{
	return actionsByName.contains(name) ? actionsByName[name] : nullptr;
}

const acp::text::ClickEvent::Action acp::text::ClickEvent::Action::OPEN_URL = { 0, "open_url" };
const acp::text::ClickEvent::Action acp::text::ClickEvent::Action::RUN_COMMAND = { 1, "run_command" };
const acp::text::ClickEvent::Action acp::text::ClickEvent::Action::SUGGEST_COMMAND = { 2, "suggest_command" };
const acp::text::ClickEvent::Action acp::text::ClickEvent::Action::CHANGE_PAGE = { 3, "change_page" };
const acp::text::ClickEvent::Action acp::text::ClickEvent::Action::COPY_TO_CLIPBOARD = { 4, "copy_to_clipboard" };


acp::text::ClickEvent::ClickEvent(const Action& action, const std::string& value): action(&action), value(value)
{
}

void acp::text::ClickEvent::serialize(std::unique_ptr<nbt::Tag>& v)
{
	if (auto* tag = dynamic_cast<nbt::TagCompound*>(v.get()))
	{
		tag->set<nbt::TagString>("action", action->getName());
		tag->set<nbt::TagString>("value", value);
	}
}

void acp::text::ClickEvent::deserialize(std::unique_ptr<nbt::Tag>& v)
{
	if (auto* tag = dynamic_cast<nbt::TagCompound*>(v.get()))
	{
		if (tag->contains("action"))
			action = Action::byName(tag->get<std::string, nbt::TagString>("action"));

		if (tag->contains("value"))
			value = tag->get<std::string, nbt::TagString>("value");
	}
}
