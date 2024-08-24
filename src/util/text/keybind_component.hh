#pragma once
#include "component.hh"

namespace acp::text
{
	class KeybindComponent : public Component
	{
		std::string keybind;

	public:
		KeybindComponent() = default;
		explicit KeybindComponent(const std::string& keybind);
		KeybindComponent(KeybindComponent& component);

		void serialize(std::unique_ptr<nbt::Tag>& v) override;
		void deserialize(std::unique_ptr<nbt::Tag>& v) override;

		std::unique_ptr<Component> copy() override;

		const std::string& getKeybind() const;
		void setKeybind(const std::string& keybind);

		const Type& getType() const override;
	};
}
