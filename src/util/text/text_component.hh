#pragma once
#include "component.hh"

namespace acp::text
{
	class TextComponent : public Component
	{
		std::string text;

	public:
		TextComponent() = default;
		explicit TextComponent(const std::string& text);

		std::unique_ptr<nbt::TagCompound> serialize() override;

		std::string& getText();
		const std::string& getText() const;
		void setText(const std::string& text);

		const Type* getType() override;
	};
}
