#pragma once
#include "util/nbt/tag.hh"

#include <memory>
#include <unordered_map>

namespace acp::nbt
{
	class TagCompound : public Tag
	{
		std::unordered_map<std::string, std::unique_ptr<Tag>> tags;

	public:
		TagCompound() = default;
		explicit TagCompound(std::unordered_map<std::string, std::unique_ptr<Tag>>&& tags);

		void read(ByteBuf& buf) override;
		void write(ByteBuf& buf) override;

		std::unordered_map<std::string, std::unique_ptr<Tag>>& get();
		const std::unordered_map<std::string, std::unique_ptr<Tag>>& get() const;
		void set(std::unordered_map<std::string, std::unique_ptr<Tag>>&& tags);

		TagType getType() const override;

		std::string toString() const override;
	};
}
