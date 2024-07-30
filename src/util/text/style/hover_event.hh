#pragma once
#include "util/io/i_serializable.hh"
#include "util/nbt/tag/tag_compound.hh"

#include <memory>
#include <string>

namespace acp::text
{
	struct HoverEvent : ISerializable<std::unique_ptr<nbt::TagCompound>>
	{
		class Action
		{
			int id;
			std::string name;

		public:
			Action(int id, const std::string& name);

			const std::string& getName() const;

			bool operator==(const Action& rhs) const;
			bool operator!=(const Action& rhs) const;


			static Action* byName(const std::string& name);

			static const Action SHOW_TEXT;
			static const Action SHOW_ITEM;
			static const Action SHOW_ENTITY;
		};

		const Action* action;
		std::string contents;

		HoverEvent(const Action& action, const std::string& contents);

		std::unique_ptr<nbt::TagCompound> serialize() override;
	};
}
