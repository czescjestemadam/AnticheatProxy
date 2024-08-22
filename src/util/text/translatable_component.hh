#pragma once
#include "component.hh"
#include "text_component.hh"

namespace acp::text
{
	class TranslatableComponent : public Component
	{
		std::string key;
		std::vector<std::unique_ptr<TextComponent>> with;

	public:
		explicit TranslatableComponent(const std::string& key);
		TranslatableComponent(TranslatableComponent& component);

		std::unique_ptr<nbt::TagCompound> serialize() override;

		std::unique_ptr<Component> copy() override;

		const std::string& getKey() const;
		void setKey(const std::string& key);

		std::vector<std::unique_ptr<TextComponent>>& getWith();
		const std::vector<std::unique_ptr<TextComponent>>& getWith() const;
		void setWith(std::vector<std::unique_ptr<TextComponent>>&& with);

		const Type& getType() const override;
	};
}
