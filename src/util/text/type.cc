#include "type.hh"

#include <unordered_map>

static std::unordered_map<std::string, acp::text::Type*> typesByName;

acp::text::Type::Type(int id, const std::string& name) : id(id), name(name)
{
	typesByName[name] = this;
}

const std::string& acp::text::Type::getName() const
{
	return name;
}

bool acp::text::Type::operator==(const Type& rhs) const
{
	return id == rhs.id;
}

bool acp::text::Type::operator!=(const Type& rhs) const
{
	return !(*this == rhs);
}


acp::text::Type* acp::text::Type::byName(const std::string& name)
{
	return typesByName.contains(name) ? typesByName[name] : nullptr;
}

const acp::text::Type acp::text::Type::TEXT = { 0, "text" };
const acp::text::Type acp::text::Type::TRANSLATABLE = { 1, "translatable" };
const acp::text::Type acp::text::Type::KEYBIND = { 2, "keybind" };
const acp::text::Type acp::text::Type::SCORE = { 3, "score" };
const acp::text::Type acp::text::Type::SELECTOR = { 4, "selector" };
const acp::text::Type acp::text::Type::NBT = { 5, "nbt" };
