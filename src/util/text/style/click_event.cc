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

std::unique_ptr<acp::nbt::TagCompound> acp::text::ClickEvent::serialize()
{
	auto tag = std::make_unique<nbt::TagCompound>();
	tag->get()["action"] = std::make_unique<nbt::TagString>(action->getName());
	tag->get()["value"] = std::make_unique<nbt::TagString>(value);

	return tag;
}

void acp::text::ClickEvent::deserialize(std::unique_ptr<nbt::TagCompound>& v)
{
	if (v->get().contains("action"))
	{
		nbt::Tag* tag = v->get()["action"].get();
		if (const auto* actionTag = dynamic_cast<nbt::TagString*>(tag))
			action = Action::byName(actionTag->get());
	}

	if (v->get().contains("value"))
	{
		nbt::Tag* tag = v->get()["value"].get();
		if (const auto* valueTag = dynamic_cast<nbt::TagString*>(tag))
			value = valueTag->get();
	}
}
