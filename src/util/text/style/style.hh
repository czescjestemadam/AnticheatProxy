#pragma once
#include "click_event.hh"
#include "hover_event.hh"

#include <optional>
#include <string>

namespace acp::text
{
	struct Style : ISerializable<std::unique_ptr<nbt::TagCompound>>
	{
		std::string color;
		std::optional<bool> bold, italic, underlined, strikethrough, obfuscated;
		std::string font;
		std::string insertion;
		std::optional<ClickEvent> clickEvent;
		std::optional<HoverEvent> hoverEvent;

		std::unique_ptr<nbt::TagCompound> serialize() override;
		void deserialize(std::unique_ptr<nbt::TagCompound>& v) override;
	};
}
