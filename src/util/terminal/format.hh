#pragma once
#include "util/color.hh"

#include <string>

namespace acp::terminal
{
	class Format
	{
		std::string code;

	public:
		Format(const std::string& code);

		const std::string& getCode() const;

		std::string toString() const;


		static std::string stripped(std::string str);

		/**
		 * creates color formatting
		 * @param type @c SET_FOREGROUND_COLOR or @c SET_BACKGROUND_COLOR
		 * @param color rgb color
		 * @return color formatting
		 */
		static Format color(const Format& type, const ColorB& color);
		static Format color(const Format& type, const std::string& hex);

		static const Format RESET;
		static const Format BOLD;
		static const Format DIM;
		static const Format ITALIC;
		static const Format UNDERLINE;
		static const Format BLINK;
		static const Format STRIKETHROUGH;

		static const Format FG_DARK_BLACK;
		static const Format FG_DARK_RED;
		static const Format FG_DARK_GREEN;
		static const Format FG_DARK_YELLOW;
		static const Format FG_DARK_BLUE;
		static const Format FG_DARK_MAGENTA;
		static const Format FG_DARK_CYAN;
		static const Format FG_DARK_WHITE;
		static const Format FG_BLACK;
		static const Format FG_RED;
		static const Format FG_GREEN;
		static const Format FG_YELLOW;
		static const Format FG_BLUE;
		static const Format FG_MAGENTA;
		static const Format FG_CYAN;
		static const Format FG_WHITE;
		static const Format FG_COLOR;
		static const Format DEFAULT_FG_COLOR;

		static const Format BG_DARK_BLACK;
		static const Format BG_DARK_RED;
		static const Format BG_DARK_GREEN;
		static const Format BG_DARK_YELLOW;
		static const Format BG_DARK_BLUE;
		static const Format BG_DARK_MAGENTA;
		static const Format BG_DARK_CYAN;
		static const Format BG_DARK_WHITE;
		static const Format BG_BLACK;
		static const Format BG_RED;
		static const Format BG_GREEN;
		static const Format BG_YELLOW;
		static const Format BG_BLUE;
		static const Format BG_MAGENTA;
		static const Format BG_CYAN;
		static const Format BG_WHITE;
		static const Format BG_COLOR;
		static const Format DEFAULT_BG_COLOR;
	};
}

inline std::ostream& operator<<(std::ostream& os, const acp::terminal::Format& format)
{
	os << format.toString();
	return os;
}

inline std::string operator+(const std::string& str, const acp::terminal::Format& format)
{
	return str + format.toString();
}

inline std::string operator+(const acp::terminal::Format& format, const std::string& str)
{
	return format.toString() + str;
}
