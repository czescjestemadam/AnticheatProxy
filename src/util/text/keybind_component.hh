#pragma once
#include "component.hh"

namespace acp::text
{
	class KeybindComponent : public Component
	{
		std::string keybind;

	public:
		explicit KeybindComponent(const std::string& keybind);

		std::unique_ptr<nbt::TagCompound> serialize() override;

		const std::string& getKeybind() const;
		void setKeybind(const std::string& keybind);

		const Type* getType() override;
	};
}
