#pragma once
#include "util/nbt/tag.hh"

#include <memory>
#include <string>

namespace acp::text
{
	struct ClickEvent
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

			static const Action OPEN_URL;
			static const Action RUN_COMMAND;
			static const Action SUGGEST_COMMAND;
			static const Action CHANGE_PAGE;
			static const Action COPY_TO_CLIPBOARD;
		};

		const Action* action = &Action::COPY_TO_CLIPBOARD;
		std::string value;

		ClickEvent() = default;
		ClickEvent(const Action& action, const std::string& value);

		void serialize(std::unique_ptr<nbt::Tag>& v);
		void deserialize(std::unique_ptr<nbt::Tag>& v);
	};
}
