#pragma once
#include "component.hh"

namespace acp::text
{
	class TranslatableComponent : public Component
	{
		std::string key;
		std::vector<std::unique_ptr<Component>> with;

	public:
		TranslatableComponent() = default;
		explicit TranslatableComponent(const std::string& key);
		TranslatableComponent(TranslatableComponent& component);

		void serialize(std::unique_ptr<nbt::Tag>& v) override;
		void deserialize(std::unique_ptr<nbt::Tag>& v) override;

		std::unique_ptr<Component> copy() override;

		const std::string& getKey() const;
		void setKey(const std::string& key);

		std::vector<std::unique_ptr<Component>>& getWith();
		const std::vector<std::unique_ptr<Component>>& getWith() const;
		void setWith(std::vector<std::unique_ptr<Component>>&& with);

		const Type& getType() const override;
	};
}
