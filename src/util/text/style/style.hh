#pragma once
#include "click_event.hh"
#include "hover_event.hh"

#include <optional>
#include <string>

namespace acp::text
{
	class IOTag;

	struct Style
	{
		std::string color;
		std::optional<bool> bold, italic, underlined, strikethrough, obfuscated;
		std::string font;
		std::string insertion;
		std::optional<ClickEvent> clickEvent;
		std::optional<HoverEvent> hoverEvent;

		std::vector<const IOTag*> getIOTags() const;
		std::vector<IOTag> getCustomIOTags() const;

		void serialize(std::unique_ptr<nbt::Tag>& v);
		void deserialize(std::unique_ptr<nbt::Tag>& v);
	};
}
