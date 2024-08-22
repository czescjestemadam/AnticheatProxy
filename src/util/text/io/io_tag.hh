#pragma once
#include <memory>
#include <string>

namespace acp::text
{
	class IOTag
	{
		int id;
		char legacyCode;
		std::string minimessageCode;
		bool resetBefore;

	public:
		IOTag(int id, char legacy_code, std::string&& mini_message_code, bool reset_before);

		char getLegacyCode() const;
		const std::string& getMiniMessageCode() const;
		bool isResetBefore() const;

		bool operator==(const IOTag& rhs) const;
		bool operator!=(const IOTag& rhs) const;


		static const IOTag* byLegacyCode(char code);
		static const IOTag* byMinimessageCode(const std::string& code);

		static const IOTag RESET;

		static const IOTag BLACK;
		static const IOTag DARK_BLUE;
		static const IOTag DARK_GREEN;
		static const IOTag DARK_AQUA;
		static const IOTag DARK_RED;
		static const IOTag DARK_PURPLE;
		static const IOTag GOLD;
		static const IOTag GRAY;
		static const IOTag DARK_GRAY;
		static const IOTag BLUE;
		static const IOTag GREEN;
		static const IOTag AQUA;
		static const IOTag RED;
		static const IOTag LIGHT_PURPLE;
		static const IOTag YELLOW;
		static const IOTag WHITE;

		static const IOTag BOLD;
		static const IOTag ITALIC;
		static const IOTag UNDERLINED;
		static const IOTag STRIKETHROUGH;
		static const IOTag OBFUSCATED;
	};
}
