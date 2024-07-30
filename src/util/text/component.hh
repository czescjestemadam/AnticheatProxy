#pragma once
#include "type.hh"
#include "style/style.hh"
#include "util/nbt/tag/tag_compound.hh"

#include <vector>
#include <memory>

namespace acp::text
{
	class Component : ISerializable<std::unique_ptr<nbt::TagCompound>>
	{
	protected:
		Style style;
		std::vector<std::unique_ptr<Component>> extra;

	public:
		std::unique_ptr<nbt::TagCompound> serialize() override;

		Style& getStyle();
		const Style& getStyle() const;
		void setStyle(const Style& style);

		std::vector<std::unique_ptr<Component>>& getExtra();
		const std::vector<std::unique_ptr<Component>>& getExtra() const;
		void setExtra(std::vector<std::unique_ptr<Component>>&& extra);

		virtual const Type* getType() = 0;
	};
}
