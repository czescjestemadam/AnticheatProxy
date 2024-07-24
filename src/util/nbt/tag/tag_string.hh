#pragma once
#include "util/nbt/tag.hh"

namespace acp::nbt
{
	class TagString : public Tag
	{
		std::string val;

	public:
		TagString() = default;
		explicit TagString(const std::string& val);

		void read(ByteBuf& buf) override;
		void write(ByteBuf& buf) override;

		std::string get() const;
		void set(const std::string& val);

		TagType getType() const override;

		std::string toString() const override;
	};
}
