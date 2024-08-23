#include "io_tag.hh"

#include "util/text/style/style.hh"

#include <unordered_map>

static std::unordered_map<char, const acp::text::IOTag*> tagByLegacyCode;
static std::unordered_map<std::string, const acp::text::IOTag*> tagByMinimessageCode;

acp::text::IOTag::IOTag(int id, char legacy_code, const std::string& minimessage_code, bool reset, std::function<void(Style&)>&& applier)
	: id(id), legacyCode(legacy_code), minimessageCode(minimessage_code), reset(reset), applier(std::move(applier))
{
	tagByLegacyCode[legacy_code] = this;
	tagByMinimessageCode[minimessage_code] = this;
}

acp::text::IOTag::IOTag(const std::string& hexColor)
	: id(-1), legacyCode('-'), minimessageCode(hexColor), reset(true), applier([hexColor](Style& style) { style.color = hexColor; })
{
}

char acp::text::IOTag::getLegacyCode() const
{
	return legacyCode;
}

const std::string& acp::text::IOTag::getMiniMessageCode() const
{
	return minimessageCode;
}

bool acp::text::IOTag::isReset() const
{
	return reset;
}

void acp::text::IOTag::apply(Style& style) const
{
	applier(style);
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

const acp::text::IOTag acp::text::IOTag::RESET = { 0, 'r', "reset", true, [](Style& style) { style = {}; } };

static acp::text::IOTag createColorTag(int id, char legacyCode, const std::string& minimessageCode)
{
	return { id, legacyCode, minimessageCode, true, [minimessageCode](acp::text::Style& style) { style.color = minimessageCode; } };
}

const acp::text::IOTag acp::text::IOTag::BLACK = createColorTag(1, '0', "black");
const acp::text::IOTag acp::text::IOTag::DARK_BLUE = createColorTag(2, '1', "dark_blue");
const acp::text::IOTag acp::text::IOTag::DARK_GREEN = createColorTag(3, '2', "dark_green");
const acp::text::IOTag acp::text::IOTag::DARK_AQUA = createColorTag(4, '3', "dark_aqua");
const acp::text::IOTag acp::text::IOTag::DARK_RED = createColorTag(5, '4', "dark_red");
const acp::text::IOTag acp::text::IOTag::DARK_PURPLE = createColorTag(6, '5', "dark_purple");
const acp::text::IOTag acp::text::IOTag::GOLD = createColorTag(7, '6', "gold");
const acp::text::IOTag acp::text::IOTag::GRAY = createColorTag(8, '7', "gray");
const acp::text::IOTag acp::text::IOTag::DARK_GRAY = createColorTag(9, '8', "dark_gray");
const acp::text::IOTag acp::text::IOTag::BLUE = createColorTag(10, '9', "blue");
const acp::text::IOTag acp::text::IOTag::GREEN = createColorTag(11, 'a', "green");
const acp::text::IOTag acp::text::IOTag::AQUA = createColorTag(12, 'b', "aqua");
const acp::text::IOTag acp::text::IOTag::RED = createColorTag(13, 'c', "red");
const acp::text::IOTag acp::text::IOTag::LIGHT_PURPLE = createColorTag(14, 'd', "light_purple");
const acp::text::IOTag acp::text::IOTag::YELLOW = createColorTag(15, 'e', "yellow");
const acp::text::IOTag acp::text::IOTag::WHITE = createColorTag(16, 'f', "white");

const acp::text::IOTag acp::text::IOTag::BOLD = { 17, 'l', "bold", false, [](Style& style) { style.bold = true; } };
const acp::text::IOTag acp::text::IOTag::ITALIC = { 18, 'o', "italic", false, [](Style& style) { style.italic = true; } };
const acp::text::IOTag acp::text::IOTag::UNDERLINED = { 19, 'n', "underlined", false, [](Style& style) { style.underlined = true; } };
const acp::text::IOTag acp::text::IOTag::STRIKETHROUGH = { 20, 'm', "strikethrough", false, [](Style& style) { style.strikethrough = true; } };
const acp::text::IOTag acp::text::IOTag::OBFUSCATED = { 21, 'k', "obfuscated", false, [](Style& style) { style.obfuscated = true; } };
