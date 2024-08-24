#pragma once
#include "util/nbt/tag.hh"

namespace acp::nbt
{
	class TagEnd : public Tag
	{
	public:
		void read(ByteBuf& buf) override;
		void write(ByteBuf& buf) override;

		std::unique_ptr<Tag> copy() override;

		TagType getType() const override;

		std::string toString() const override;
	};
}
