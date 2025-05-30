#include "format.hh"

acp::terminal::Format::Format(const std::string& code): code(code)
{
}

const std::string& acp::terminal::Format::getCode() const
{
	return code;
}

std::string acp::terminal::Format::toString() const
{
	return "\033[" + code + 'm';
}


std::string acp::terminal::Format::stripped(std::string str)
{
	while (true)
	{
		const size_t startPos = str.find("\033[");
		if (startPos == std::string::npos)
			break;

		const size_t endPos = str.find('m', startPos);
		if (endPos == std::string::npos)
			break;

		str = str.erase(startPos, endPos - startPos + 1);
	}

	return str;
}

acp::terminal::Format acp::terminal::Format::color(const Format& type, const ColorB& color)
{
	return {
		type.getCode() + ";2;" +
		std::to_string(color.r) + ';' +
		std::to_string(color.g) + ';' +
		std::to_string(color.b)
	};
}

acp::terminal::Format acp::terminal::Format::color(const Format& type, const std::string& hex)
{
	ColorB c;

	if (hex.length() == 7 && hex.starts_with('#'))
	{
		c.r = std::strtoul(hex.substr(1, 2).c_str(), nullptr, 16);
		c.g = std::strtoul(hex.substr(3, 2).c_str(), nullptr, 16);
		c.b = std::strtoul(hex.substr(5, 2).c_str(), nullptr, 16);
	}

	return color(type, c);
}

const acp::terminal::Format acp::terminal::Format::RESET = { "0" };
const acp::terminal::Format acp::terminal::Format::BOLD = { "1" };
const acp::terminal::Format acp::terminal::Format::DIM = { "2" };
const acp::terminal::Format acp::terminal::Format::ITALIC = { "3" };
const acp::terminal::Format acp::terminal::Format::UNDERLINE = { "4" };
const acp::terminal::Format acp::terminal::Format::BLINK = { "6" };
const acp::terminal::Format acp::terminal::Format::STRIKETHROUGH = { "9" };

const acp::terminal::Format acp::terminal::Format::FG_DARK_BLACK = { "30" };
const acp::terminal::Format acp::terminal::Format::FG_DARK_RED = { "31" };
const acp::terminal::Format acp::terminal::Format::FG_DARK_GREEN = { "32" };
const acp::terminal::Format acp::terminal::Format::FG_DARK_YELLOW = { "33" };
const acp::terminal::Format acp::terminal::Format::FG_DARK_BLUE = { "34" };
const acp::terminal::Format acp::terminal::Format::FG_DARK_MAGENTA = { "35" };
const acp::terminal::Format acp::terminal::Format::FG_DARK_CYAN = { "36" };
const acp::terminal::Format acp::terminal::Format::FG_DARK_WHITE = { "37" };
const acp::terminal::Format acp::terminal::Format::FG_BLACK = { "90" };
const acp::terminal::Format acp::terminal::Format::FG_RED = { "91" };
const acp::terminal::Format acp::terminal::Format::FG_GREEN = { "92" };
const acp::terminal::Format acp::terminal::Format::FG_YELLOW = { "93" };
const acp::terminal::Format acp::terminal::Format::FG_BLUE = { "94" };
const acp::terminal::Format acp::terminal::Format::FG_MAGENTA = { "95" };
const acp::terminal::Format acp::terminal::Format::FG_CYAN = { "96" };
const acp::terminal::Format acp::terminal::Format::FG_WHITE = { "97" };
const acp::terminal::Format acp::terminal::Format::FG_COLOR = { "38" };
const acp::terminal::Format acp::terminal::Format::DEFAULT_FG_COLOR = { "39" };

const acp::terminal::Format acp::terminal::Format::BG_DARK_BLACK = { "40" };
const acp::terminal::Format acp::terminal::Format::BG_DARK_RED = { "41" };
const acp::terminal::Format acp::terminal::Format::BG_DARK_GREEN = { "42" };
const acp::terminal::Format acp::terminal::Format::BG_DARK_YELLOW = { "43" };
const acp::terminal::Format acp::terminal::Format::BG_DARK_BLUE = { "44" };
const acp::terminal::Format acp::terminal::Format::BG_DARK_MAGENTA = { "45" };
const acp::terminal::Format acp::terminal::Format::BG_DARK_CYAN = { "46" };
const acp::terminal::Format acp::terminal::Format::BG_DARK_WHITE = { "47" };
const acp::terminal::Format acp::terminal::Format::BG_BLACK = { "100" };
const acp::terminal::Format acp::terminal::Format::BG_RED = { "101" };
const acp::terminal::Format acp::terminal::Format::BG_GREEN = { "102" };
const acp::terminal::Format acp::terminal::Format::BG_YELLOW = { "103" };
const acp::terminal::Format acp::terminal::Format::BG_BLUE = { "104" };
const acp::terminal::Format acp::terminal::Format::BG_MAGENTA = { "105" };
const acp::terminal::Format acp::terminal::Format::BG_CYAN = { "106" };
const acp::terminal::Format acp::terminal::Format::BG_WHITE = { "107" };
const acp::terminal::Format acp::terminal::Format::BG_COLOR = { "48" };
const acp::terminal::Format acp::terminal::Format::DEFAULT_BG_COLOR = { "49" };
