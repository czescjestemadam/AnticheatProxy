#pragma once
#include "component.hh"

namespace acp::text
{
	class KeybindComponent : public Component
	{
		std::string keybind;

	public:
		explicit KeybindComponent(const std::string& keybind);
		KeybindComponent(KeybindComponent& component);

		std::unique_ptr<nbt::TagCompound> serialize() override;

		std::unique_ptr<Component> copy() override;

		const std::string& getKeybind() const;
		void setKeybind(const std::string& keybind);

		const Type* getType() override;
	};
}
