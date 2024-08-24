#pragma once
#include "util/nbt/tag.hh"

#include <memory>
#include <string>

namespace acp::text
{
	struct HoverEvent
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

		const Action* action = &Action::SHOW_TEXT;
		std::string contents;

		HoverEvent() = default;
		HoverEvent(const Action& action, const std::string& contents);

		void serialize(std::unique_ptr<nbt::Tag>& v);
		void deserialize(std::unique_ptr<nbt::Tag>& v);
	};
}
