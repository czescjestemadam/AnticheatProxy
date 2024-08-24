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
		TextComponent(TextComponent& component);

		void serialize(std::unique_ptr<nbt::Tag>& v) override;
		void deserialize(std::unique_ptr<nbt::Tag>& v) override;

		std::unique_ptr<Component> copy() override;

		std::string& getText();
		const std::string& getText() const;
		void setText(const std::string& text);

		const Type& getType() const override;
	};
}
