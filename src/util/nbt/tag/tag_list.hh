#pragma once
#include "util/nbt/tag.hh"

#include <memory>

namespace acp::nbt
{
	class TagList : public Tag
	{
		std::vector<std::unique_ptr<Tag>> arr;

	public:
		TagList() = default;
		explicit TagList(std::vector<std::unique_ptr<Tag>>&& elements);

		void read(ByteBuf& buf) override;
		void write(ByteBuf& buf) override;

		std::vector<std::unique_ptr<Tag>>& get();
		const std::vector<std::unique_ptr<Tag>>& get() const;
		void set(std::vector<std::unique_ptr<Tag>>&& arr);

		TagType getType() const override;

		std::string toString() const override;
	};
}
