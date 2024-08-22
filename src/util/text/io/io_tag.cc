#include "io_tag.hh"

#include <unordered_map>

static std::unordered_map<char, const acp::text::IOTag*> tagByLegacyCode;
static std::unordered_map<std::string, const acp::text::IOTag*> tagByMinimessageCode;

acp::text::IOTag::IOTag(int id, char legacy_code, std::string&& mini_message_code, bool reset_before)
	: id(id), legacyCode(legacy_code), minimessageCode(mini_message_code), resetBefore(reset_before)
{
	tagByLegacyCode[legacy_code] = this;
	tagByMinimessageCode[mini_message_code] = this;
}

char acp::text::IOTag::getLegacyCode() const
{
	return legacyCode;
}

const std::string& acp::text::IOTag::getMiniMessageCode() const
{
	return minimessageCode;
}

bool acp::text::IOTag::isResetBefore() const
{
	return resetBefore;
}

bool acp::text::IOTag::operator==(const IOTag& rhs) const
{
	return id == rhs.id;
}

bool acp::text::IOTag::operator!=(const IOTag& rhs) const
{
	return !(*this == rhs);
}


const acp::text::IOTag* acp::text::IOTag::byLegacyCode(char code)
{
	return tagByLegacyCode.contains(code) ? tagByLegacyCode[code] : nullptr;
}

const acp::text::IOTag* acp::text::IOTag::byMinimessageCode(const std::string& code)
{
	return tagByMinimessageCode.contains(code) ? tagByMinimessageCode[code] : nullptr;
}

const acp::text::IOTag acp::text::IOTag::RESET = { 0, 'r', "reset", false };

const acp::text::IOTag acp::text::IOTag::BLACK = { 1, '0', "black", true };
const acp::text::IOTag acp::text::IOTag::DARK_BLUE = { 2, '1', "dark_blue", true };
const acp::text::IOTag acp::text::IOTag::DARK_GREEN = { 3, '2', "dark_green", true };
const acp::text::IOTag acp::text::IOTag::DARK_AQUA = { 4, '3', "dark_aqua", true };
const acp::text::IOTag acp::text::IOTag::DARK_RED = { 5, '4', "dark_red", true };
const acp::text::IOTag acp::text::IOTag::DARK_PURPLE = { 6, '5', "dark_purple", true };
const acp::text::IOTag acp::text::IOTag::GOLD = { 7, '6', "gold", true };
const acp::text::IOTag acp::text::IOTag::GRAY = { 8, '7', "gray", true };
const acp::text::IOTag acp::text::IOTag::DARK_GRAY = { 9, '8', "dark_gray", true };
const acp::text::IOTag acp::text::IOTag::BLUE = { 10, '9', "blue", true };
const acp::text::IOTag acp::text::IOTag::GREEN = { 11, 'a', "green", true };
const acp::text::IOTag acp::text::IOTag::AQUA = { 12, 'b', "aqua", true };
const acp::text::IOTag acp::text::IOTag::RED = { 13, 'c', "red", true };
const acp::text::IOTag acp::text::IOTag::LIGHT_PURPLE = { 14, 'd', "light_purple", true };
const acp::text::IOTag acp::text::IOTag::YELLOW = { 15, 'e', "yellow", true };
const acp::text::IOTag acp::text::IOTag::WHITE = { 16, 'f', "white", true };

const acp::text::IOTag acp::text::IOTag::BOLD = { 17, 'l', "bold", false };
const acp::text::IOTag acp::text::IOTag::ITALIC = { 18, 'o', "italic", false };
const acp::text::IOTag acp::text::IOTag::UNDERLINED = { 19, 'n', "underlined", false };
const acp::text::IOTag acp::text::IOTag::STRIKETHROUGH = { 20, 'm', "strikethrough", false };
const acp::text::IOTag acp::text::IOTag::OBFUSCATED = { 21, 'k', "obfuscated", false };
